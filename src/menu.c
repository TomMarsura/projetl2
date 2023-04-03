#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../lib/game.h"
#include "../lib/menu.h"




int pointsProfils[MAX_PROFILS] = {}; // Points des 50 profils
char nomProfils[MAX_PROFILS][SIZE_NAME] = {}; // Noms des 50 profils (20 caractères max)
int numProfils[MAX_PROFILS] = {}; // Numéros des 50 profils
int nbProfils = 0; // Nombre de profils
int nbPartiesProfils[MAX_PROFILS] = {}; //nombre de partie joué


int route [HAUTEUR][LARGEUR];
int score;
int cpt_distance;

int profilCourant;

/**
 * @brief Fonction initGame : fonction qui initialise la partie
 * @author Tom Marsura
 * @return void
*/
extern void initGame(){
    int i, j;
    
    /* Initialisation de la matrice à 0 */
    for(i = 0; i < HAUTEUR; i++){
        for(j = 0; j < LARGEUR; j++){
            route[i][j] = 0;
        }
    }

    /* Placement de la voiture au milieu de la dernière ligne */
    route[4][1] = 1;
    score = 0;
    cpt_distance = 0;
}

extern void cleanProfiles(){
    for(int i = 0; i < MAX_PROFILS; i++){
        pointsProfils[i] = 0;
        nbPartiesProfils[i] = 0;
        numProfils[i] = 0;
        strcpy(nomProfils[i], "");
    }
    nbProfils = 0;
}

/**
 * @brief Fonction readProfiles : Lecture des profiles
 * @author Tom Marsura
 * @return void
*/
extern void readProfiles(){
    /* Fonction qui récupère les données dans un fichier save.csv et les inscrit dans des tableaux*/
    /* Format du fichier : numeroProfil;score;pseudo;nombreDeParties */
    /* numeroProfils -> numProfils; score -> pointsProfils; pseudo -> nomProfils; */
    FILE * fichier = fopen("../save/save.csv", "r");
    int i = 0;

    cleanProfiles();

    if (fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
    }
    else{   
        /*Lecture dans le fichier et assignation des valeurs dans les tableaux*/
        while(fscanf(fichier, "%d %d %s %d ", &numProfils[i], &pointsProfils[i], nomProfils[i], &nbPartiesProfils[i]) != EOF){
            i++;
            nbProfils++;
        }
    }
    fclose(fichier);
}

/**
 * @brief Fonction saveGame : Sauvegarde les profils dans un fichier save.csv
 * @author Tom Marsura
 * @return void
*/
extern void saveGame(){
    FILE * fichier = fopen("../save/save.csv", "w");
    if(fichier != NULL){
        for(int i = 0; i < nbProfils; i++){
            fprintf(fichier, "%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }
    }
    fclose(fichier);
}

/**
 * @brief Fonction createProfile : Créer un profil et l'ajoute dans le tableau des profils
 * @author Tom Marsura
 * @return void
*/
extern void createProfile(char nomProfil[SIZE_NAME]){
    numProfils[nbProfils] = nbProfils;
    pointsProfils[nbProfils] = 0;
    strcpy(nomProfils[nbProfils], nomProfil);
    nbPartiesProfils[nbProfils] = 0;

    nbProfils++;

    saveGame(); // Sauvegarde les profils dans le fichier save.csv
}

/**
 * @brief deleteProfil : Supprime un profil du tableau des profils
 * @author Tom Marsura
 * @return void
*/
extern void deleteProfil(int idProfil){

    printf("nbProfils : %d\n\n", nbProfils);

    if(idProfil == nbProfils - 1){
        nbProfils--;
    } else {
        for(int i = idProfil; i < nbProfils - 1; i++){
            numProfils[i] = numProfils[i+1];
            pointsProfils[i] = pointsProfils[i+1];
            strcpy(nomProfils[i], nomProfils[i+1]);
            nbPartiesProfils[i] = nbPartiesProfils[i+1];
        }
        nbProfils--;
    }

    printf("nbProfils : %d\n\n", nbProfils);
    saveGame(); // Sauvegarde les profils dans le fichier save.csv
    readProfiles(); // Met à jour les profils
}

/**
 * @brief Nettoie les données du jeu, sauvegarde le profil une fois que le jeu est terminé 
 * @author Ayoub Laaribi
 * @return void 
*/
void cleanupGame(){
    int i,j;
/*Sauvegarde des données*/
    saveGame();

    //Nettoyage de la route
/*Parcours de la route et met toutes les valeurs a NULL*/
    for(i = 0 ; i< HAUTEUR ;i++){
        for(j = 0; j<LARGEUR;j++){
            route[i][j] = 0;
        }
    }
    score = 0;
    cpt_distance = 0;
}