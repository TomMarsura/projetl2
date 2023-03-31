/**
 * @file game.c
 * @brief Bibliotheque Game.c
 * @authors Ayoub LAARIBI,Tom MARSURA,Thibaut
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
/*#include "../lib/game.h"*/
/*#include "../lib/menu.h"*/

/* Include pour la fonction deplacement */
#include "../lib/game.h"
#include "../lib/menu.h"
#include "../lib/fonctions_game.h"

/* Include pour gérer le temps */
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

int lignes_succesives = 0;
int double_obs_succ = 0;


/**
*@brief Affiche le contenu d'une matrice
*@author Ayoub Laaribi
*@return void
*/
extern void affiche_mat(){
  /*initialisation*/
  int i,j;

  for (i=0;i< HAUTEUR;i++){
    for(j=0;j<LARGEUR;j++){
      printf("%d",route[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  printf("\n");
  printf("\n");
}


/**
*@brief Retoune le nombre d'obsatcle sur de l'avant dernière ligne
*@author Thibaut Gasnier
*@return int
*/
extern int nb_obstacle(){

  int nb = 0;
  int i;

  for (i=0;i< LARGEUR ;i++){
    if (route[1][i] == 2){
      nb++;
    }
  }

  return nb;
}

/**
*@brief Retoune la postion la case qui ne contient pas d'obstacle
*@author Thibaut Gasnier
*@return int
*/
extern int position_libre(){

  int pos;
  int i;

  for (i=0;i< LARGEUR-1 ;i++){
    if (route[1][i] != 2){
      pos = i;
    }
  }

  return pos;
}



/**
  affichae_mat();
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles pour HardGame.
 * @author Ayoub Laaribi / Thibaut Gasnier
 * @return void
*/
extern void obstacle_hard(){

  affiche_mat();

  int position1;
  position1 = rand() % LARGEUR; /*genenere aléatoirement la position du première obstacle*/

  int position2;
  position2 = rand() % LARGEUR; /*genenere aléatoirement la position du deuxième obstacle*/

  int apparition;
  apparition = rand() % 100; /*genere un pourcentage pour décider si on ajoute un obsatcle*/

  int nb_obstacle_ligne;
  nb_obstacle_ligne = rand() % 100; /*genere un pourcentage pour décider si on ajoute 1 ou 2 obsatcles à la ligne*/

  /* Vérifier que la position1 et position2 ne sont pas sur la même colonne pour éviter les obstacles superposés */
  while (position1 == position2) {
    position2 = rand() % LARGEUR;
  }

  if ((apparition > 50) && (lignes_succesives < 2)){

    /* On a un seul obbstacle a ajouter*/
    if(nb_obstacle_ligne>3){

      if (nb_obstacle() < 2){
        int tirage = rand()%4 + 2;
        route[0][position1] = tirage;
        lignes_succesives++;
      }

      else if (nb_obstacle() == 2){
        if (position1 != position_libre()){
          int tirage = rand()%4 + 2;
          route[0][position1] = tirage;
          lignes_succesives++;
        }
      }
      double_obs_succ = 0;
    }

    else{

      if (double_obs_succ == 0){

        if (nb_obstacle() == 0){
            route[0][position1] = 2;
            route[0][position2] = 2;
            lignes_succesives++;
            double_obs_succ ++;
        }

        else if (nb_obstacle() == 1){
          if ((position1 == position_libre() || (position2 == position_libre()))){
            int tirage = rand()%4 + 2;
            route[0][position1] = tirage;
            route[0][position2] = tirage;
            lignes_succesives++;
            double_obs_succ ++;
          }
        }

        else if (nb_obstacle() == 2){
          if ((position1 =! position_libre()) && (position2 =! position_libre())){
            int tirage = rand()%4 + 2;
            route[0][position1] = tirage;
            route[0][position2] = tirage;
            lignes_succesives++;
            double_obs_succ ++;
          }
        }
      }
    }
    printf("Lignes sucessive:%d\n",lignes_succesives);
  }
  else{
    lignes_succesives = 0;
    double_obs_succ = 0;
  }
}



/**
  affichae_mat();
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles pour easyGame.
 * @author Ayoub Laaribi / Thibaut Gasnier
 * @return void
*/
extern void obstacle_easy(){

  int position;
  position = rand() % LARGEUR; /*genenere aléatoirement la position de l'obstacle*/

  int apparition;
  apparition = rand() % 100; /*genere un pourcentage pour décider si on ajoute un obsatcle*/

  if ((apparition > 50) && (lignes_succesives < 2)){
    int tirage = rand()%4 + 2;
    route[0][position] = tirage;
    lignes_succesives++;
  }
  else{
    lignes_succesives = 0;
  }
}



/**
 * @brief Fonction crash : Cette fonction permet de savoir si la joueur a touché un obstacle, si oui cela renvoie 1
 * @author Thibaut Gasnier
 * @return int
*/
extern int crash(){

  int i;

  for (i=0; i<LARGEUR ; i++){
    /*Verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] > 1)){
      /* On retourne 1 pour signnfier le crash */
      return 1;
    }
  }

  /*modification du score*/
  /*addScore(profil);*/
  /* On retourne 0 quand il n'y a pas de crash */
  return 0;
}



/**
 * @brief Fonction deplacement : Cette fonction permet de deplacer la voiture si le joueur appuie sur la flèche de gauche ou sur la flèche de droite de son clavier
 * @author Thibaut Gasnier
 * @return void
*/
extern void deplacement(int touche){

  int i;
  int x;
  int y;

  for (i=0 ; i<LARGEUR ; i++){
    /* Trouver la postion de la voiture sur la ligne */
    if (route[HAUTEUR-1][i] == 1){
       /* La variable x correspond à la ligne de la position de la voiture */
       x = HAUTEUR-1;
      /* La variable y correspond à la colonne de la position de la voiture */
      y = i;
      break;
    }
  }

  /* Si le joueur appuie sur la flèche de gauche et verifier si la limite de la route sur la gauche est dépassée */
  if ((touche == 1) && (!(y == LARGEUR-1))){
    /* On modifie la position de la voiture dans la matrice */
    route[x][y] = 0;
    route[x][y+1] = 1;
    affiche_mat();
  }

  /* Si le joueur appuie sur la flèche de gauche et verifier si la limite de la route sur la gauche est dépassée */
  if ((touche == 2) && (!(y == 0))){
  /* On modifie la position de la voiture dans la matrice */
    route[x][y] = 0;
    route[x][y-1] = 1;
    affiche_mat();

  }
}



/**
 * @brief Fonction decalage : Cette fonction permet de décaler tout le contenu de la matrice une ligne plus bas
 * @author Thibaut Gasnier
 * @return void
*/
extern void decalage(){

  printf("DECALAGE \n");

  int i;
  int j;
  int x;
  int y;

  for (i=0 ; i<LARGEUR ; i++){
    /* Trouver la postion de la voiture sur la ligne */
    if (route[HAUTEUR-1][i] == 1){
      /* La variable x correspond à la ligne de la position de la voiture */
      x = HAUTEUR-1;
      /* La variable y correspond à la colonne de la position de la voiture */
      y = i;
      break;
    }
  }

  for (i=HAUTEUR-1 ; i>0 ; i--){
    for (j=0 ; j<LARGEUR ; j++){
      route[i][j] = route[i-1][j];
    }
  }

  for (j = 0 ; j < LARGEUR ; j++){
    route[0][j] = 0;
  }

  /* On met la voiture a lligne du dessus */
  route[x][y] = 1;
  affiche_mat();
}
