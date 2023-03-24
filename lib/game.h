
#ifndef _GAME_H_
#define _GAME_H_

#define HAUTEUR 5
#define LARGEUR 3

#define VITESSE_MAX 0.1


/* Variables globales */
/* Variables globales */
int route[HAUTEUR][LARGEUR]= {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,1,0}};
int score;
int cpt_distance;





/* Prototype des fonctions */
extern void affichae_mat();
extern void obstacle();
extern int calcul_score();
extern int crash();
extern void deplacement(int touche);
extern void decalage();
extern void easyGame(int profil);




#endif
