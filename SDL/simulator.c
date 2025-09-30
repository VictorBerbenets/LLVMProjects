#include "sim.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define FRAME_DELAY_MS 250

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 LastFrameTime = 0;

void simInit() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SIM_X_SIZE, SIM_Y_SIZE, 0, &Window, &Renderer);
  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  SDL_RenderClear(Renderer);
  srand(time(NULL));
  simFlush();
}

void simExit() {
  SDL_Event event;
  while (1) {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;
  }
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void simFlush() {
  SDL_PumpEvents();
  assert(SDL_TRUE != SDL_HasEvent(SDL_QUIT) && "User-requested quit");
  
  Uint32 current_time = SDL_GetTicks() - LastFrameTime;
  if (current_time < FRAME_DELAY_MS) {
    SDL_Delay(FRAME_DELAY_MS - current_time);
  }
  SDL_RenderPresent(Renderer);
}

void FillFigure(int x, int y, int width, int height, int argb) {
  assert(0 <= x && x < SIM_X_SIZE && "X coordinate out of range");
  assert(0 <= y && y < SIM_Y_SIZE && "Y coordinate out of range");

  SDL_Rect rect = {x, y, width, height};
  Uint8 alpha = argb >> 24;
  Uint8 red = (argb >> 16) & 0xFF;
  Uint8 green = (argb >> 8) & 0xFF;
  Uint8 blue = argb & 0xFF;
  SDL_SetRenderDrawColor(Renderer, red, green, blue, alpha);

  SDL_RenderFillRect(Renderer, &rect);
  LastFrameTime = SDL_GetTicks();
}

int simRand() { return rand(); }
