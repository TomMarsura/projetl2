#define HAUTEUR 5
#define LARGEUR 3


/* Variables globales */
int route[HAUTEUR][LARGEUR] = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
int score = 0;



/* Prototype des fonctions */
void obstacle(int mat[HAUTEUR][LARGEUR]);
int crash();
void deplacement();
