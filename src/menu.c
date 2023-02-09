#include <stdio.h>
#include <time.h>

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
    /* Fonction qui récupère les données dans un fichier save.csv et les inscrit dans des tableaux*/
    /* Format du fichier : numeroProfil;score;pseudo;nombreDeParties */
    /* numeroProfils -> numProfils; score -> pointsProfils; pseudo -> nomProfils; */
    FILE * fichier = fopen("../save/save.csv", "r");
    if(fichier != NULL){
        for(int i = 0; i < MAX_PROFILS; i++){
            fscanf(fichier, "%d %d %s %d", &numProfils[i], &pointsProfils[i], nomProfils[i], &nbPartiesProfils[i]);
        }
    }
    fclose(fichier);
}

/**
* @brief Fonction addScore : Change le score du profil au file de la distance
* @param[in] profile int
* @author Ayoub Laaribi
* @return void
*/
void addScore(int profil){

/*initialisation*/
    int score_dist;
    /*Recup du score*/
    score_dist = calcul_score();
    /*modification de la case score*/
    pointsProfils[profil] = pointsProfils[profil] + score_dist;

}

/**
 * @brief Nettoie les données du jeu, sauvegarde le profil une fois que le jeu est terminé 
 * @author Ayoub Laaribi
 * @return void 
*/
void cleanupGame(){
    int i,j;
/*Sauvegarde des données*/
    //saveGame();

    //Nettoyage de la route
/*Parcours de la route et met toutes les valeurs a NULL*/
    for(i = 0 ; i< HAUTEUR ;i++){
        for(j = 0; j<LARGEUR;j++){
            route[i][j] = NULL;
        }
    }

<<<<<<< HEAD
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
        addScore(id_profil);
    }
    fclose(fichier);
=======
>>>>>>> refs/remotes/origin/main
}

/**
 * @brief Fonction saveGame : Sauvegarde les profils dans un fichier save.csv
 * @author Tom Marsura
 * @return void
*/
void saveGame(){
    FILE * fichier = fopen("../save/save.csv", "w");
    if(fichier != NULL){
        for(int i = 0; i < MAX_PROFILS; i++){
            fprintf(fichier, "%d %d %s %d", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
        }
    }
}

/**
 * @brief Fonction main : fonction principale du programme, permet de tester les fonctions du menu.c
 * @author Tom Marsura
 * @return int
*/
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

    /* Affichage du fichier save */
    printf("Affichage save : \n");
    readProfiles();
    for(i = 0; i < 5; i++){
        printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
    }

    /* Affichage des tableaux de données */
    printf("Affichage des tableaux de données : \n");
    for(i = 0; i < 5; i++){
        printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
    }

    /* Test de sauvegarde */
    printf("Test de sauvegarde : \n");
    saveGame();
    readProfiles();
    printf("Affichage save : \n");
    for(i = 0; i < 5; i++){
        printf("%d %d %s %d \n", numProfils[i], pointsProfils[i], nomProfils[i], nbPartiesProfils[i]);
    }
    return 0;
}