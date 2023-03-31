#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../lib/sdl.h"
#include "../lib/menu.h"


SDL_bool program_launched = SDL_TRUE ;


/*FONCTION SDL_ExitWithMessage*/

/*******************************************************
Cette fonction renvoie un message d'erreur et qui la SDL
********************************************************/

extern void SDL_ExitWithMessage(const char *message)
{
    SDL_Log("ERREUR : %s  \n", message);
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}
