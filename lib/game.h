
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





/* Prototype des fonctions */
extern int nb_obstacle();
extern void affichae_mat();
extern void obstacle_easy();
extern void obstacle_hard();
extern int calcul_score();
extern int crash();
extern void deplacement(int touche);
extern void decalage();
extern void easyGame(int profil);




#endif
