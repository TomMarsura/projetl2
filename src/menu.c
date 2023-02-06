#include <stdio.h>
#include "../lib/game.h"
#include "../lib/menu.h"

/**
 * @brief Fonction initGame : fonction qui initialise la partie
 * @author Tom Marsura
 * @return void
*/
void initGame(){
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
}

/**
 * @brief Fonction readProfiles : Lecture des profiles
 * @author Tom Marsura
 * @return void
*/
void readProfiles(){
    /* Format du fichier : numeroProfil;score;pseudo;nombreDeParties */
    /* numeroProfils -> numProfils; score -> pointsProfils; pseudo -> nomProfils; */
    FILE * fichier = fopen("../save/save.csv", "r");
    if(fichier != NULL){
        char ligne[100];
        int i = 0;
        while(fgets(ligne, 100, fichier) != NULL){
            char * pch;
            pch = strtok(ligne, ";");
            while(pch != NULL){
                if(i == 0){
                    numProfils[i] = atoi(pch);
                }else if(i == 1){
                    pointsProfils[i] = atoi(pch);
                }else if(i == 2){
                    strcpy(nomProfils[i], pch);
                }else if(i == 3){
                    nbPartiesProfils[i] = atoi(pch);
                }
                pch = strtok(NULL, ";");
            }
            i++;
        }
        fclose(fichier);
    }
}

/**
* @brief Fonction addScore : Change le score du profil
* @param[in] profile int
* @author Ayoub Laaribi
* @return void
*/
void addScore(int profil){
    /*Ouverture du fichier*/
    FILE * fichier = fopen("../save/save.csv","r");
    char ligne[100];
    char * pch;
    /*Recherche du profil a modifier*/
    pch = strtok(ligne,";");
    while(fgets(100,ligne,fichier) != NULL){
    /*Si l'element est egal a l'id du profile alors c'est le bon,on peut donc le modifier*/
        if(atoi(pch) == profil){
        /*modif point*/
        }else{
        /*Passage a la ligne suivante*/
            while(fgetc(fichier) != '\n'); //passage a la ligne suivante
        }
    }
    fclose(fichier);
    /*Recherche du score et modif*/
}

/**
 * @brief Nettoie les données du jeu, sauvegarde le profil une fois que le jeu est terminé 
 * @author Ayoub Laaribi
 * @return void 
*/
void cleanupGame(){
    int i,j;
/*Parcours de la route et met toutes les valeurs a NULL*/
    for(i = 0 ; i< HAUTEUR ;i++){
        for(j = 0; j<LARGEUR;j++){
            route[i][j] = NULL;
        }
    }

    /*Sauvegarde du profil*/
    FILE * fichier = fopen("../save/save.csv","r");
    char ligne[100];
    char* id; /*numero de profil*/
    int id_profil;
    if (fichier != NULL){

        while(fgets(ligne,100,fichier) != NULL){
            id = strtok(ligne,";"); /*Numero de profil*/
            id_profil = atoi(id); /*conversion en int*/
        }

    /*Modification du score*/
        add(id_profil);
    }





    fclose(fichier);

    addScore()
}


int main(){
    initGame();
    /* Affichage de la matrice */
    int i, j;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){
            printf("%d ", route[i][j]);
        }
        printf("\n");
    }
    return 0;
}