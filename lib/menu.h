
#ifndef _MENU_H_
#define _MENU_H_


#define MAX_PROFILS 50
#define SIZE_NAME 20

int pointsProfils[MAX_PROFILS] = {}; // Points des 50 profils
char nomProfils[MAX_PROFILS][SIZE_NAME] = {}; // Noms des 50 profils (20 caractères max)
int numProfils[MAX_PROFILS] = {}; // Numéros des 50 profils
int nbProfils = 0; // Nombre de profils
int nbPartiesProfils[MAX_PROFILS] = {}; //nombre de partie joué

/*PROTOTYPE FONCTIONS*/

void cleanupGame(); 
void initGame();
void readProfiles();
void addScore(int profil);
void saveGame();
void menu();
void create_ranking();
void print_rank();

#endif