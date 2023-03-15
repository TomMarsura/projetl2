
#ifndef _GAME_H_
#define _GAME_H_

#define HAUTEUR 5
#define LARGEUR 3

#define VITESSE_MAX 0.1


/* Variables globales */
/* Variables globales */
extern int route[HAUTEUR][LARGEUR];
extern int score;
extern int cpt_distance;





/* Prototype des fonctions */
extern void affichae_mat();
extern void obstacle();
extern int calcul_score();
extern int crash();
extern int clavier();
extern void deplacement(float vitesse);
extern void decalage();
extern void easyGame(int profil);




#endif
