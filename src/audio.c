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
#include "../include/SDL2/SDL_mixer.h"

#include "../lib/sdl.h"
#include "../lib/menu.h"

Mix_Music *musique = NULL;


void initAudio() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());
    //return NULL;
  }

}


void jouerMusique(char source[20]) {
    musique = Mix_LoadMUS(source);

     Mix_PlayMusic(musique, -1);
}


void detruireAudio() {
  Mix_FreeMusic(musique);
  Mix_CloseAudio();
}