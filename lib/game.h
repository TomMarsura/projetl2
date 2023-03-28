#ifndef _GAME_H_
#define _GAME_H_

#define HAUTEUR 5
#define LARGEUR 3

#define VITESSE_DEPART 800

#define VITESSE_MAX_HARD 200
#define VITESSE_MAX_EASY 400


/* Variables globales */
/* Variables globales */
extern int route[HAUTEUR][LARGEUR];
extern int score;
extern int cpt_distance;


#include <SDL2/SDL.h>
/* Prototype des fonctions */
extern void easyGame(SDL_Window* window, SDL_Renderer* renderer, int profil);
extern void MediumGame(SDL_Window* window, SDL_Renderer* renderer, int profil);
extern void HardGame(SDL_Window* window, SDL_Renderer* renderer, int profil);



#endif
