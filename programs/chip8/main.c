#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "chip8.h"

#define PIXEL_OFF 0x111d2bff
#define PIXEL_ON  0x8f9185ff
#define SCALE 15

const int TICKRATE = 1000 / 500;

typedef struct {
  SDL_Window *win;
  SDL_Renderer *renderer;
  SDL_Texture *screen;
  SDL_AudioDeviceID audioDevice;
  unsigned int audioSampleCount;
  void *audioBuf;
  unsigned int audioBufLength;
} sdl_handle;

sdl_handle gSDL;

int get_key(uint32_t key)
{
  switch(key){
    case SDLK_1: return 1;
    case SDLK_2: return 2;
    case SDLK_3: return 3;
    case SDLK_4: return 0xc;
    case SDLK_q: return 4;
    case SDLK_w: return 5;
    case SDLK_e: return 6;
    case SDLK_r: return 0xd;
    case SDLK_a: return 7;
    case SDLK_s: return 8;
    case SDLK_d: return 9;
    case SDLK_f: return 0xe;
    case SDLK_z: return 0xa;
    case SDLK_x: return 0;
    case SDLK_c: return 0xb;
    case SDLK_v: return 0xf;
    default: return -1;
  }
}

void draw(struct chip8_vm *vm)
{
  void *raw;
  int pitch;
  SDL_LockTexture(gSDL.screen, NULL, &raw, &pitch);

  uint32_t(*pixels)[pitch / 4] = raw;

  for (int y = 0; y < HEIGHT; y++){
    for (int x = 0; x < WIDTH; x++){
      int pixel = chip8_getPixel(vm, x, y);
      pixels[y][x] = pixel == 0 ? PIXEL_OFF : PIXEL_ON;
    }
  }
  SDL_UnlockTexture(gSDL.screen);
  SDL_RenderCopy(gSDL.renderer, gSDL.screen, NULL, NULL);
  SDL_RenderPresent(gSDL.renderer);
}

int main(int argc, char **argv)
{
  if (argc != 2){
    fprintf(stderr, "usage: chip8 game\n");
    exit(1);
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    fprintf(stderr, SDL_GetError());
    exit(1);
  }

  SDL_Window *win = SDL_CreateWindow("Chip8",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH*SCALE, HEIGHT*SCALE, 0);
  
  if (!win){
    fprintf(stderr, SDL_GetError());
    exit(1);
  }

  uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, flags);
  if (!renderer){
    fprintf(stderr, SDL_GetError());
    exit(1);
  }

  SDL_Texture *texture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_RGBA8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           WIDTH, HEIGHT);

  if(!texture){
    fprintf(stderr, SDL_GetError());
    exit(1);
  }

  gSDL.win = win;
  gSDL.renderer = renderer;
  gSDL.screen = texture;

  int open = 1;

  chip8_vm *vm;

  vm = chip8_init();
  chip8_load(vm, argv[1]);

  srand(time(NULL));

  uint32_t renderTick = 0;
  uint32_t renderInterval = TICKRATE;
  uint32_t timerTick = SDL_GetTicks();
  uint32_t timerInterval = TICKRATE;

  int key;
  while(open){
    if (SDL_GetTicks() - timerTick >= timerInterval){
      timerTick = SDL_GetTicks();
      if (vm->delay_timer > 0) vm->delay_timer--;
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)){
      switch(e.type){
        case SDL_QUIT:
          open = 0;
        break;

        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_ESCAPE) open = 0;

          key = get_key(e.key.keysym.sym);
          if (key != -1){
            vm->key[key] = 1;
            if (vm->wait){
              vm->wait = 0;
              vm->V[vm->waitreg] = key;
            }
          }
        break;

        case SDL_KEYUP:
          key = get_key(e.key.keysym.sym);
          if (key != -1){
            vm->key[key] = 0;
          }
        break;
      }
    }
    
    //for (int f = 0; f < 16; f++) printf("%d ", vm->key[f]);
    SDL_Delay(TICKRATE);

    chip8_tick(vm);
    draw(vm);
  }

  free(vm);
}
