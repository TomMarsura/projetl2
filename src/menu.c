#include <stdio.h>
#include <stdlib.h>
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


/*
ALGORITHME






*/
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
            route[i][j] = NULL;
        }
    }
    score = 0;
    cpt_distance = 0;
}


void reverse(char source[20],char dest[20]){
    int i,j;

    for(i = 0; i < 20;i++);
    for(j = 0;j < 20;j++,i--)
    {
        dest[j] = source[i];
    }
}



int cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


/**
 * @author Ayoub LAARIBI
 * @brief Fonction create_ranking
 * @return void
*/


/*ALGORITHME

OUVERTURE DU FICHIER
PARCOUR DES PROFILS AFIN DE COPIER LES POINTS DES PROFILS
    COPIE DES VALEURS POINTPROFILS DANS LA TABLEAU POINTSORT
TRIE TU TABLEAU POINT SORT : PAR ORDRE CROISSANT
    REVERSE

ECRITURE DES POINTS DANS LE FICHIER
    RECUPERATION DU NOM DU PROFIL

    SI L'ELEMENT DE NOTRE TABLEAU SORT EST EGAL A L'ELEMENT DE POINT PROFIL
        ON AFFECTE DANS nomP Le nomProfils A L'INDICE DONNER
*/

void create_ranking(){ /*Fonction pas terminé*/
    FILE * fichier = fopen("rank.csv","w");

    int Point_sort[MAX_PROFILS];
    int PointS[MAX_PROFILS];
    int i;
    char nomP[20];

    /*Copie du tableau de score*/
    for (i = 0; i < MAX_PROFILS;i++){
        PointS[i] = pointsProfils[i];
    }

    /*tri des score*/

    /*void qsort( void * array, size_t elementCount, size_t elementSize,
            int (*compareFunction)( const void*, const void* ) );*/
    qsort(PointS,MAX_PROFILS,sizeof(int),cmpfunc);

    /*inversement du tableau pour etre decroissant*/
    reverse(PointS,Point_sort);
    /*Ecriture dans le fichier*/
    for (i = 0 ;i< MAX_PROFILS;i++){

        /*Si l'element de notre tableau est egal a l'indice de pointProfil
        alors on peut affecter le nom du joueurs*/
        if (Point_sort[i] == pointsProfils[i])
        {
            nomP[20] = nomProfils[i][20]; 

            /*ecriture FORMAT : NOM : POINTS*/
            fprintf("%s : %d\n",nomP,Point_sort[i]);
        }
    }
    fclose(fichier);
}

/**
 * @author Ayoub Laaribi
 * @brief fonction affiche le classement des joueur avec leur score
 * @return void
*/
void print_rank(){
    FILE * f = fopen("rank.csv","r");
        fprintf(f,);
    fclose(f);
}

/**
 * @author Ayoub LAARIBI
 * @brief Cette fonction a pour but d'afficher le menu
 * @return void
*/
void menu(){
    if(){
        create_ranking();
    }else if(){

    }else if(){

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