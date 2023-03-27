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
/**
 * @brief Fonction creation d'un profil
 * @author Ayoub Laaribi
 * @return void
*/

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

    //Printf des noms
    for(int i = 0; i < nbProfils; i++){
        printf("%s", nomProfils[i]);
    }
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


/**
 * @brief Fonction main : fonction de création du classement par points
 * @author Tom Marsura
 * @return int
*/
extern void classement()
{
    int i, j;
    int maxIndex;

    for (i = 0; i < nbProfils; i++) {
        maxIndex = i;
        for (j = i+1; j < nbProfils; j++) {
            if (pointsProfils[j] > pointsProfils[maxIndex]) {
                maxIndex = j;
            }
        }
        // Échange des éléments à l'indice i et maxIndex pour tous les tableaux
        int tmpPoints = pointsProfils[i];
        pointsProfils[i] = pointsProfils[maxIndex];
        pointsProfils[maxIndex] = tmpPoints;

        char tmpNom[SIZE_NAME];
        strcpy(tmpNom, nomProfils[i]);
        strcpy(nomProfils[i], nomProfils[maxIndex]);
        strcpy(nomProfils[maxIndex], tmpNom);

        int tmpNum = numProfils[i];
        numProfils[i] = numProfils[maxIndex];
        numProfils[maxIndex] = tmpNum;

        int tmpNbParties = nbPartiesProfils[i];
        nbPartiesProfils[i] = nbPartiesProfils[maxIndex];
        nbPartiesProfils[maxIndex] = tmpNbParties;
    }
}

/**
 * @brief Fonction main : fonction d'affichage du classement par points
 * @author Tom Marsura
 * @return int
*/
extern void affichage_classement(){
    for(int i = 0; i < nbProfils; i++){
        printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
    }
}

/**
 * @author Ayoub LAARIBI
 * @brief Cette fonction a pour but d'afficher le menu
 * @return void
*/
extern void menu(){
    int rep = 0;

    do{
        printf("entrer l'option :\n");
        printf("1 : CLASSEMENT\n");
        printf("2 : FACILE\n");
        printf("3 : MOYEN\n");
        printf("4 : DIFFICILE\n");
        printf("CHOIX : ");
        scanf("%d",&rep);
    }while(rep < 1 || rep > 4);

    switch(rep)
    {
        case 1 : /*AFFICHAGE DU CLASSEMENT*/
            printf("Affichage du classement trié : \n");
            classement();
            affichage_classement();
            break;

        case 2 :/*LANCEMENT JEU FACILE*/
            printf("Lancement du jeu en mode facile\n");
            break;
        case 3: /*LANCEMENT JEU MOYEN*/
            printf("test\n");
            break;
         case 4: /*LANCEMENT JEU DIFFICILE*/
            printf("test\n");
            break;
    }
}