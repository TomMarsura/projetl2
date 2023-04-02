#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>


#ifndef _SDL_H_
#define _SDL_H_

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef enum bool_s {FAUX, VRAI} bool_t;

extern SDL_bool program_launched;

extern void SDL_ExitWithMessage(const char *message);
#endif
