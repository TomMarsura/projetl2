#define HAUTEUR 5
#define LARGEUR 3


/* Variables globales */
int route[HAUTEUR][LARGEUR] = {{0,5,0}, {6,0,0}, {0,0,7}, {0,8,0}, {0,1,0}};
int score = 0;
int cpt_distance = 0;


/* Prototype des fonctions */
void obstacle(int mat[HAUTEUR][LARGEUR]);
int crash();
void deplacement();
int calcul_score();
