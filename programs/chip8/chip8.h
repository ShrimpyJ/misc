#include <stdint.h>

#define WIDTH  64
#define HEIGHT 32

struct chip8_vm;

extern struct chip8_vm *chip8_init();
extern void chip8_load(struct chip8_vm *vm, const char* game);
extern void chip8_tick(struct chip8_vm *vm);
extern int chip8_getPixel(struct chip8_vm *vm, int x, int y);

typedef struct chip8_vm {
  uint16_t     opcode;
  uint8_t      memory[4096];
  uint16_t     stack[16];
  uint16_t     sp;
  uint16_t     pc;
  uint8_t      V[16];
  uint16_t     I;
  uint8_t      delay_timer;
  uint8_t      sound_timer;
  uint8_t      key[16];
  uint8_t      gfx[2048];
  uint8_t      wait;
  uint8_t      waitreg;
} chip8_vm;
