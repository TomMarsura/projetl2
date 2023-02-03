#include <stdio.h>
#include "../lib/game.h"



void initGame(){
    int i, j;
    /* Initialisation de la matrice à 0 */
    for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){
            route[i][j] = 0;
        }
    }

    /* Placement de la voiture au milieu de la dernière ligne */
    route[4][1] = 1;
    score = 0;
}

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

int main(){
    initGame();
    /* Affichage de la matrice */
    int i, j;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}