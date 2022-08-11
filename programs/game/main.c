#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <time.h>

#define TITLE "My Game"
#define WIDTH 680
#define HEIGHT 680

#define ERROR_EXIT(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
#define KEY key.keysym.sym

const int TICKRATE = 1000 / 60;

typedef struct {
  SDL_Window *win;
  SDL_Renderer *renderer;
  SDL_Texture *screen;
  SDL_AudioDeviceID audioDevice;
  unsigned int audioSampleCount;
  void *audioBuf;
  unsigned int audioBufLength;
} sdl_handle;

typedef struct {
  int r, g, b;
} Color;

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

Color *color_init(int r, int g, int b)
{
  Color *c = calloc(1, sizeof(Color));
  c->r = r;
  c->b = b;
  c->g = g;
  if (c->r < 0) c->r = 0;
  if (c->r > 255) c->r = 255;
  if (c->g < 0) c->g = 0;
  if (c->g > 255) c->g = 255;
  if (c->b < 0) c->b = 0;
  if (c->b > 255) c->b = 255;
  return c;
}

void color_incR(Color *c, int n)
{
  c->r += n;
  if (c->r > 255) c->r = 255;
}

void color_incG(Color *c, int n)
{
  c->g += n;
  if (c->g > 255) c->g = 255;
}

void color_incB(Color *c, int n)
{
  c->b += n;
  if (c->b > 255) c->b = 255;
}

void color_decR(Color *c, int n)
{
  c->r -= n;
  if (c->r < 0) c->r = 0;
}

void color_decG(Color *c, int n)
{
  c->g -= n;
  if (c->g < 0) c->g = 0;
}

void color_decB(Color *c, int n)
{
  c->b -= n;
  if (c->b < 0) c->b = 0;
}

int main(int argc, char **argv)
{
  /* Initialize SDL */
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) ERROR_EXIT(SDL_GetError());

  /* Window */
  SDL_Window *win = SDL_CreateWindow(TITLE,
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 0);
  if (win == NULL) ERROR_EXIT(SDL_GetError());

  /* Renderer */
  uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, flags);
  if (!renderer) ERROR_EXIT(SDL_GetError());

  /* Texture */
  SDL_Texture *texture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_RGBA8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           WIDTH, HEIGHT);
  if(!texture) ERROR_EXIT(SDL_GetError());

  gSDL.win = win;
  gSDL.renderer = renderer;
  gSDL.screen = texture;

  int open = 1;

  srand(time(NULL));

  uint32_t renderTick = 0;
  uint32_t renderInterval = TICKRATE;
  uint32_t timerTick = SDL_GetTicks();
  uint32_t timerInterval = TICKRATE;

  printf("init\n");
  Color *color = color_init(0, 0, 0);
  printf("%d, %d, %d\n", color->r, color->g, color->b);

  int key;
  while(open){
    if (SDL_GetTicks() - timerTick >= timerInterval){
      timerTick = SDL_GetTicks();
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)){
      switch(e.type){
        case SDL_QUIT:
          open = 0;
          break;

        case SDL_KEYDOWN:
          if (e.KEY == SDLK_ESCAPE) open = 0;

          if (e.KEY == SDLK_u) color_incR(color, 5);
          if (e.KEY == SDLK_y) color_decR(color, 5);

          if (e.KEY == SDLK_j) color_incG(color, 5);
          if (e.KEY == SDLK_h) color_decG(color, 5);

          if (e.KEY == SDLK_m) color_incB(color, 5);
          if (e.KEY == SDLK_n) color_decB(color, 5);

          key = get_key(e.key.keysym.sym);
          break;

        case SDL_KEYUP:
          key = get_key(e.key.keysym.sym);
          break;
      }
    }

    /* Draw renderer */
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(TICKRATE);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
