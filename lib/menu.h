
#ifndef _MENU_H_
#define _MENU_H_


#define MAX_PROFILS 50

int pointsProfils[MAX_PROFILS] = {}; // Points des 50 profils
char nomProfils[MAX_PROFILS][20] = {}; // Noms des 50 profils (20 caractères max)
int numProfils[MAX_PROFILS] = {}; // Numéros des 50 profils
int nbProfils = 0; // Nombre de profils
int nbPartiesProfils[MAX_PROFILS] = {}; //nombre de partie joué

/*PROTOTYPE FONCTIONS*/

void cleanupGame(); 
void initGame();
void readProfiles();
void addScore(int profil);
void saveGame();

#endif