#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>


#ifndef _SDL_H_
#define _SDL_H_


SDL_bool program_launched = SDL_TRUE;

extern void SDL_ExitWithMessage(const char *message);
extern void Lancement_menu(SDL_Window *window, SDL_Renderer *renderer);

#endif
