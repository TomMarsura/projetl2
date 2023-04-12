
#ifndef _MENU_H_
#define _MENU_H_


#define MAX_PROFILS 50
#define SIZE_NAME 12

extern int pointsProfils[MAX_PROFILS] ;
extern char nomProfils[MAX_PROFILS][SIZE_NAME];
extern int numProfils[MAX_PROFILS] ;
extern int nbPartiesProfils[MAX_PROFILS] ;
extern int nbProfils ;

extern int profilCourant;

/*PROTOTYPE FONCTIONS*/

extern void cleanProfils();
extern void initGame();
extern void readProfiles();
extern void createProfile(char nomProfil[SIZE_NAME]);
extern void saveGame();
extern void deleteProfil(int idProfil);

#endif