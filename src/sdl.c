/**
 * @file game.c
 * @brief Bibliotheque sdl.c
 * @authors Ayoub LAARIBI,Tom MARSURA,Thibaut GASNIER
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_ttf.h"

#include "../lib/sdl.h"
#include "../lib/menu.h"


SDL_bool program_launched = SDL_TRUE ;


/*FONCTION SDL_ExitWithMessage*/

/*******************************************************
Cette fonction renvoie un message d'erreur et qui la SDL
********************************************************/

/**
 * @brief Fonction SDL_ExitWithMessage : Fonction qui renvoie un message d'erreur et qui quitte la SDL
 * @param message : message d'erreur
 * @author Ayoub LAARIBI
 * @return void
*/
extern void SDL_ExitWithMessage(const char *message)
{
    SDL_Log("ERREUR : %s  \n", message);
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}
