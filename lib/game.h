#ifndef _GAME_H_
#define _GAME_H_

#define HAUTEUR 7
#define LARGEUR 3

#define VITESSE_DEPART_EASY 45
#define VITESSE_DEPART_MEDIUM 40
#define VITESSE_DEPART_HARD 35


#define VITESSE_MAX_HARD 10
#define VITESSE_MAX_EASY 20

/* Variables globales */
/* Variables globales */
extern int route[HAUTEUR][LARGEUR];
extern int score;
extern int cpt_distance;


#include <SDL2/SDL.h>
/* Prototype des fonctions */
extern void easyGame(SDL_Window* window, SDL_Renderer* renderer);
extern void MediumGame(SDL_Window* window, SDL_Renderer* renderer);
extern void HardGame(SDL_Window* window, SDL_Renderer* renderer);



#endif
