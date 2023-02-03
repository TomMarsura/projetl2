/**
 * @file game.c
 * @brief Bibliotheque Game.c
 * @author Ayoub LAARIBI,Tom MARSURA,Thibaut
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "../lib/game.h"

/**
*@brief Affiche le contenu d'une matrice
*@param[in] mat matrice de type int
*@return void
*/
void affichae_mat(int mat[HAUTEUR][LARGEUR]){
  /*initialisation*/
    int i,j;

    for (i = 0;i< 5;i++){

        for(j = 0;j<3;j++){
            printf("%d",mat[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles
 * @param[in] mat matrice de type int
 * @return void
*/
void obstacle(int mat[HAUTEUR][LARGEUR]){

    /*initialisation*/
    int obstacle;
    int nb_obstacle;
    int cpt = 0;
    /*genere position
    nb obstacle
    */
/*genere le nombre d'obstacle soit 1 ou 2*/
    nb_obstacle = rand() % 2 +1;

    while( cpt != nb_obstacle){
/*genere un nombre entre 0 et 3 , qui represente l'endroit ou l'obstacle va etre positionner*/
        obstacle = rand() % 3 +1;
        mat[0][obstacle] = 2;
        cpt++;
    }
    affichae_mat(mat);
}

/**
 * @brief Fonction crash : Cette fonction permet de savoir si la joueur a touché un obstacle, si oui cela renvoie 1
 * @return int
*/
int crash(){
  int i;
  for (i=0;i<LARGEUR-1;i++){
    /*verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] == 2)){
      /*on retourne 1 pour signnfier le crash*/
      return 1;
    }
  }
  return 0;

}
