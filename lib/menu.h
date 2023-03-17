
#ifndef _MENU_H_
#define _MENU_H_


#define MAX_PROFILS 50
#define SIZE_NAME 12

 extern int pointsProfils[MAX_PROFILS] ;
 extern char nomProfils[MAX_PROFILS][SIZE_NAME];
 extern int numProfils[MAX_PROFILS] ;
 extern int nbProfils ;
 extern int nbPartiesProfils[MAX_PROFILS] ;

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