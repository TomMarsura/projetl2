
#ifndef _GAME_H_
#define _GAME_H_

#define HAUTEUR 5
#define LARGEUR 3

#define VITESSE_MAX 0.1


/* Variables globales */
int route[HAUTEUR][LARGEUR] = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,1,0}};
int score = 0;
int cpt_distance = 0;


/* Prototype des fonctions */
void affichae_mat();
void obstacle();
int calcul_score();
int crash();
int clavier();
void deplacement(float vitesse);
void decalage();
void easyGame();




#endif
