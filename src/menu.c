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
    FILE * fichier = fopen("../save/save.csv", "r");
    
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