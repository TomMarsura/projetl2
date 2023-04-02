#include <stdio.h>
#include "../lib/menu.h"

void affichage_classement(){
    int i;
    for(i = 0; i < nbProfils; i++){
        printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
    }
}

int main(){
    initGame();
    int i, choix = 0;

    do{
        printf("MENU DEBUG\n 1 - Affichage sauvegardes / Classement\n 2 - Création profil\n");
        scanf("%d", &choix);
    }while(choix < 1 || choix > 3);

    if(choix == 1){
        /* Affichage du fichier save */
        printf("Affichage save : \n");
        readProfiles();
        for(i = 0; i < nbProfils; i++){
            printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }

        /* Affichage des tableaux de données */
        printf("Affichage des tableaux de données : \n");
        for(i = 0; i < nbProfils; i++){
            printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }

        /* Test de tri de tableau */
        printf("Test de tri de tableau : \n");
        classement();
        for(i = 0; i < nbProfils; i++){
            printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }
    }
    else if(choix == 2){
        /* Affichage des tableaux de données */
        readProfiles();
        printf("Affichage des tableaux de données AVANT : \n");
        for(i = 0; i < nbProfils; i++){
            printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }
        readProfiles();
        char nom[20];
        printf("Saisir un nom de profil : ");
        scanf("%s", nom);
        createProfile(nom);
        
        /* Affichage des tableaux de données */
        printf("Affichage des tableaux de données APRES : \n");
        for(i = 0; i < nbProfils; i++){
            printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }
    }
    else{
        printf("Erreur de saisie\n");
    }
}