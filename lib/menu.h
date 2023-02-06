int pointsProfils[50] = {}; // Points des 50 profils
char nomProfils[50][20] = {}; // Noms des 50 profils (20 caractères max)
int numProfils[50] = {}; // Numéros des 50 profils
int nbProfils = 0; // Nombre de profils
int nbPartiesProfils[] = {}; //nombre de partie joué






/*PROTOTYPE FONCTIONS*/

void cleanupGame(); 
void initGame();
void readProfiles();
void addScore(int profil);