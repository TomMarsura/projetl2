
#ifndef _FONCTIONS_GAME_H_
#define _FONCTIONS_GAME_H_

#define HAUTEUR 7
#define LARGEUR 3


/* Variables globales */
/* Variables globales */
extern int route[HAUTEUR][LARGEUR];
extern int score;
extern int cpt_distance;
extern int lignes_succesives;





/* Prototype des fonctions */
extern int nb_obstacle();
extern void affiche_mat();
extern void obstacle_easy();
extern void obstacle_hard();
extern int calcul_score();
extern int crash();
extern int bonus_pris();
extern void deplacement(int touche);
extern void decalage();
extern int pause(SDL_Window* window, SDL_Renderer* renderer);





#endif
