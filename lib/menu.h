
#ifndef _MENU_H_
#define _MENU_H_


#define MAX_PROFILS 50
#define SIZE_NAME 20

extern int pointsProfils[MAX_PROFILS] = {}; // Points des 50 profils
extern char nomProfils[MAX_PROFILS][SIZE_NAME] = {}; // Noms des 50 profils (20 caractères max)
extern int numProfils[MAX_PROFILS] = {}; // Numéros des 50 profils
extern int nbProfils = 0; // Nombre de profils
extern int nbPartiesProfils[MAX_PROFILS] = {}; //nombre de partie joué

/*PROTOTYPE FONCTIONS*/

extern void initGame();
extern void readProfiles();
extern void createProfile();
extern void saveGame();
extern void cleanupGame();
extern void classement();
extern void affichage_classement();
extern void menu();

#endif