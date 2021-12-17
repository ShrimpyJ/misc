#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static uint8_t font[] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0,
  0x20, 0x60, 0x20, 0x20, 0x70,
  0xF0, 0x10, 0xF0, 0x80, 0xF0,
  0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0xA0, 0xA0, 0xF0, 0x20, 0x20,
  0xF0, 0x80, 0xF0, 0x10, 0xF0,
  0xF0, 0x80, 0xF0, 0x90, 0xF0,
  0xF0, 0x10, 0x20, 0x40, 0x40,
  0xF0, 0x90, 0xF0, 0x90, 0xF0,
  0xF0, 0x90, 0xF0, 0x10, 0xF0,
  0xF0, 0x90, 0xF0, 0x90, 0x90,
  0xE0, 0x90, 0xE0, 0x90, 0xE0,
  0xF0, 0x80, 0x80, 0x80, 0xF0,
  0xE0, 0x90, 0x90, 0x90, 0xE0,
  0xF0, 0x80, 0xF0, 0x80, 0xF0,
  0xF0, 0x80, 0xF0, 0x80, 0x80,
};

struct chip8_vm *chip8_init()
{
  int i;
  chip8_vm *vm;

  vm = malloc(sizeof(chip8_vm));

  // Clear the vm
  memset(vm, 0, sizeof(chip8_vm));

  vm->pc     = 0x200;
  vm->opcode = 0;
  vm->I      = 0;
  vm->sp     = 0;

  // Load fonts into first 80 bytes of memory
  for (i = 0; i < 80; i++){
    vm->memory[i] = font[i];
  }

  return vm;
}

void chip8_load(struct chip8_vm *vm, const char* game)
{
  FILE *f;
  size_t size;
  void *buf;

  // Open game file
  if ((f = fopen(game, "rb")) == NULL){
    fprintf(stderr, "error: could not open game '%s'\n", game);
    exit(1);
  }

  // Load game into memory starting at pc 0x200
  printf("Loading %s...\n", game);
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);
  buf = malloc(size);
  if (fread(buf, 1, size, f) != size){
    fprintf(stderr, "error: fread failed\n");
    exit(1);
  }
  fclose(f);
  memcpy(vm->memory+0x200, buf, size);
}

int chip8_getPixel(struct chip8_vm *vm, int x, int y)
{
  int index = y * WIDTH + x;
  int byte_index = index / 8;
  int offset = index % 8;
  return vm->gfx[byte_index] & (0x80 >> offset);
}

void set_pixel(chip8_vm *vm, int x, int y, int on)
{
  int index = y * WIDTH + x;
  int byte_index = index / 8;
  int offset = index % 8;
  uint8_t byte = vm->gfx[byte_index];
  if (on) byte = byte | (0x80 >> offset);
  else byte = byte & (~(0x80 >> offset));
  vm->gfx[byte_index] = byte;
}

//void draw_sprite(struct chip8_vm *vm, int startX, int startY, int endX, int endY)
//{
//  int x, y;
//
//  for (y = startY; y < endY; y++){
//    uint8_t spriteByte = vm->memory[vm->I + (y - startY)];
//    for (x = startX; x < endX; x++){
//      int spritePixel = spriteByte & (0x80 >> (x - startX));
//      int screenPixel = chip8_getPixel(vm, x, y);
//
//      if (spritePixel){
//        if (screenPixel){
//          vm->V[0xF] = 1;
//        }
//        set_pixel(vm, x, y, screenPixel == 0 ? 1 : 0);
//      }
//    }
//  }
//}

void draw_sprite(struct chip8_vm *vm)
{
  uint8_t x = vm->V[(vm->opcode >> 8) & 0xF];
  uint8_t y = vm->V[(vm->opcode >> 4) & 0xF];
  uint8_t n = vm->opcode & 0xF;
  uint8_t bytes[n];

  int index = 0;
  for (int i = 0; i < n*2; i+=2){
    bytes[index] = (vm->memory[vm->I+i] << 8 | vm->memory[vm->I+i+1]) & 0xFF;
    index++;
  }

  for (int i = 0; i < n; i++) printf("0x%X\n", bytes[i]);
  
  index = 0;
  for (int i = y; i < y+n; i++){
    for (int j = x; j < x+8; j++){
      int pixel = bytes[index] & (0x80 >> j-x);
      printf("at %d: %d ", (i)*HEIGHT+(j), pixel);
      if(pixel){
        //vm->gfx[i*HEIGHT+j] = 1;
        vm->gfx[i*HEIGHT+j] = 255;
        //set_pixel(vm, j, i, pixel == 0 ? 1 : 0);
        printf("DRAWING");
      }
      printf("\n");
    }
    printf("\n");
    index++;
  }
}

void chip8_tick(struct chip8_vm *vm)
{
  int x, y, i;
  uint8_t vx, vy;
  int startX, startY, endX, endY, n;

  // Merge the two bytes at pc and pc+1 into one opcode
  vm->opcode = vm->memory[vm->pc] << 8 | vm->memory[vm->pc+1];
  vm->pc += 2;

  //printf("opcode: 0x%04X\n", vm->opcode);

  // Decode and execute
  switch (vm->opcode & 0xF000){
    // 0x0
    case 0x0000:
      switch (vm->opcode & 0x000F){
        case 0x0000:  // 00E0: Clears the screen
          for (i = 0; i < 256; i++)
            vm->gfx[i] = 0;
        break;

        case 0x000E:  // 00EE: Return from subroutine
          vm->pc = vm->stack[--vm->sp];
        break;

        default:
          vm->pc = vm->opcode;
      }
    break;

    // 0x1
    case 0x1000:  // 1NNN: Jump to address NNN
      vm->pc = vm->opcode & 0x0FFF;
    break;

    // 0x2
    case 0x2000:  // 2NNN: Calls subroutine at NNN
      vm->stack[vm->sp++] = vm->pc;
      vm->pc = vm->opcode & 0x0FFF;
    break;

    // 0x3
    case 0x3000:  // 3XNN: Skips next instr if VX equals NN
      if (vm->V[(vm->opcode >> 8) & 0xF] == (vm->opcode & 0xFF))
        vm->pc += 2;
    break;

    // 0x4
    case 0x4000:  // 4XNN: Skips next instr if VX does not equal NN
      if (vm->V[(vm->opcode >> 8) & 0xF] != (vm->opcode & 0xFF))
        vm->pc += 2;
    break;

    // 0x5
    case 0x5000:  // 5XY0: Skips next instr if VX equals VY
      if (vm->V[(vm->opcode >> 8) & 0xF] == (vm->V[(vm->opcode >> 4)] & 0xF))
        vm->pc += 2;
    break;

    // 0x6
    case 0x6000:  // 6XNN: Sets VX to NN
      vm->V[(vm->opcode >> 8) & 0xF] = (vm->opcode & 0xFF);
    break;

    // 0x7
    case 0x7000:  // 7XNN: Adds NN to VX
      vm->V[(vm->opcode >> 8) & 0xF] += (vm->opcode & 0xFF);
    break;

    // 0x8
    case 0x8000:
      x = (vm->opcode >> 8) & 0xF;
      y = (vm->opcode >> 4) & 0xF;
      switch(vm->opcode & 0xF){
        case 0x0000:  // 8XY0: Sets VX to value of VY
          vm->V[x] = vm->V[y];
        break;

        case 0x0001:  // 8XY1: Sets VX to VX or VY
          vm->V[x] = vm->V[x] | vm->V[y];
        break;

        case 0x0002:  // 8XY2: Sets VX to VX and VY
          vm->V[x] = vm->V[x] & vm->V[y];
        break;

        case 0x0003:  // 8XY3: Sets VX to VX xor VY
          vm->V[x] = vm->V[x] ^ vm->V[y];
        break;

        case 0x0004:  // 8XY4: Adds VY to VX
          vx = vm->V[x];
          vy = vm->V[y];
          vm->V[x] = vx + vy;
          vm->V[0xF] = ((uint16_t)vx + (uint16_t)vy) > 255 ? 0x01 : 0x00;
        break;

        case 0x0005:  // 8XY5: VY subtracted from VX
          vx = vm->V[x];
          vy = vm->V[y];
          vm->V[x] = vx - vy;
          vm->V[0xF] = vx < vy ? 0x00 : 0x01;
        break;

        case 0x0006:  // 8XY6: Stores least sig bit of VX in VF. Shifts VX right by 1
          vm->V[0xF] = vm->V[x] & 0x1;
          vm->V[x] = vm->V[y] >> 1;
        break;

        case 0x0007:  // 8XY7: Sets VX to VY minus VX
          vx = vm->V[x];
          vy = vm->V[y];
          vm->V[x] = vy - vx;
          vm->V[0xF] = vy < vx ? 0x00 : 0x01;
        break;

        case 0x000E:  // 8XYE: Stores most sig bit of VX in VF. Shifts VX left by 1.
          vm->V[0xF] = (vm->V[x] >> 7) & 0x1;
          vm->V[x] = vm->V[y] << 1;
        break;

        default:
          fprintf(stderr, "unknown opcode: 0x%04X\n", vm->opcode);
      }
    break;

    // 0x9
    case 0x9000:  // 9XY0: Skips next instr if VX does not equal VY
      if (vm->V[(vm->opcode >> 8) & 0xF] != (vm->V[(vm->opcode >> 4) & 0xF]))
        vm->pc += 2;
    break;

    // 0xA
    case 0xA000:  // ANNN: Sets I to the address NNN
      vm->I = vm->opcode & 0xFFF;
    break;

    // 0xB
    case 0xB000:  // BNNN: Jumps to address NNN plus V0
      vm->pc = (vm->opcode & 0xFFF) + vm->V[0];
    break;

    // 0xC
    case 0xC000:  // CXNN: Sets VX to result of a bitop on random number(0-255) and NN
      vm->V[(vm->opcode >> 8) & 0xF] = ((rand() % 256) & (vm->opcode & 0xFF));
    break;

    // 0xD
    case 0xD000:  // DXYN: Draws sprite at coordinate (VX, VY) with width=8 height=N
//      startX = vm->V[(vm->opcode >> 8) & 0xF];
//      startY = vm->V[(vm->opcode >> 4) & 0xF];
//      n = vm->opcode & 0xF;
//
//      if (startX >= WIDTH)
//        startX = startX % WIDTH;
//      if (startY >= HEIGHT)
//        startY = startY % HEIGHT;
//
//      endX = startX+8 < WIDTH ? startX+8 : WIDTH;
//      endY = startY+n < HEIGHT ? startX+n : HEIGHT;
//
//      vm->V[0xF] = 0;

//      draw_sprite(vm, startX, startY, endX, endY);
      draw_sprite(vm);
    break;

    // 0xE
    case 0xE000:
      vx = vm->V[(vm->opcode >> 8) & 0xF];
      switch (vm->opcode & 0x000F){

        case 0x000E:  // EX9E: Skips next instr if key stored in VX is pressed
          if (vm->key[vx])
            vm->pc += 2;
        break;

        case 0x0001:  // EXA1: Skips next instr if key stored in VX is not pressed
          if (!vm->key[vx])
            vm->pc += 2;
        break;

        default:
          fprintf(stderr, "unknown opcode: 0x%04X\n", vm->opcode);
      }
    break;

    // 0xF
    case 0xF000:
      x = (vm->opcode >> 8) & 0xf;
      switch (vm->opcode & 0x00FF){

        case 0x0007:  // FX07: Sets VX to value of delay timer
          vm->V[x] = vm->delay_timer;
        break;

        case 0x000A:  // FX0A: Key press awaited then stored in VX (blocking)
          vm->wait = 1;
          vm->wait = (vm->opcode >> 8) & 0xF;
        break;

        case 0x0015:  // FX15: Sets delay timer to VX
          vm->delay_timer = vm->V[x];
        break;

        case 0x0018:  // FX18: Sets sound timer to VX
          vm->sound_timer = vm->V[x];
        break;

        case 0x001E:  // FX1E: Adds VX to I. VF not affected
          vm->I += vm->V[x];
        break;

        case 0x0029:  // FX29: Sets I to location of sprite for charater in VX
          vm->I = vm->V[x] * 5;
        break;

        case 0x0033:  // FX33: Stores binary-coded decimal value of VX
          vx = vm->V[x];
          vm->memory[vm->I] = vx / 100;
          vm->memory[vm->I+1] = (vx / 10) % 10;
          vm->memory[vm->I+2] = vx % 10;
        break;

        case 0x0055:  // FX55: Stores from V0 to VX inclusive in memory starting at I
          for (i = 0; i <= x; i++)
            vm->memory[vm->I+i] = vm->V[i];
        break;

        case 0x0065:  // FX65: Fills from V0 to VX inclusive with values from memory starting at I
          for (i = 0; i <= x; i++)
            vm->V[i] = vm->memory[vm->I+i];
        break;
      }
    break;

    default:
      fprintf(stderr, "unknown opcode: 0x%04X\n", vm->opcode);
  }
}
