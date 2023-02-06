/**
 * @file game.c
 * @brief Bibliotheque Game.c
 * @author Ayoub LAARIBI,Tom MARSURA,Thibaut
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "../lib/game.h"

/* Include pour la fonction deplacement */
#include <termios.h>
#include <unistd.h>

/* Include pour gérer le temps */
#include <time.h>



/**
*@brief Affiche le contenu d'une matrice
*@author Ayoub Laaribi
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
    printf("\n");
    printf("\n");
}


/**
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles
 * @author Ayoub Laaribi
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

  for (i=0; i<LARGEUR-1 ; i++){
    /*Verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-1][i] == 2)){
      /* On retourne 1 pour signnfier le crash */
      return 1;
    }
  }
  /* On retourne 0 quand il n'y a pas de crash */
  return 0;
}


/**
 * @brief Fonction deplacement : Cette fonction permet de deplacer la voiture si le joueur appuie sur la flèche de gauche ou sur la flèche de droite de son clavier
 * @return void
*/
void deplacement(){

  /* La fonction clavier retourne le code ASCII de la touche du clavier sur la laquelle appuie le joueur */
  int clavier(){
      struct termios oldattr, newattr;
      int ch;
      tcgetattr(STDIN_FILENO, &oldattr);
      newattr = oldattr;
      newattr.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
      ch = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
      return ch;
  }

    int c;
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

  /* Si le joueur appuie sur la flèche de droite code ASCII=67 et verifier si la limite de la route sur la droite est dépassée */
  c = clavier();
  if ((c == 67) && (!(y == LARGEUR-1))){
    /* On modifie la position de la voiture dans la matrice */
    route[x][y] = 0;
    route[x][y+1] = 1;
    affichae_mat(route);
  }

  /* Si le joueur appuie sur la flèche de gauche code ASCII=68 et verifier si la limite de la route sur la gauche est dépassée */
  else if ((c == 68) && (!(y == 0))){
    /* On modifie la position de la voiture dans la matrice */
    route[x][y] = 0;
    route[x][y-1] = 1;
    affichae_mat(route);
  }
}


/**
 * @brief Fonction decalage : Cette fonction permet de décaler tout le contenu de la matrice une ligne plus bas
 * @return void
*/
void decalage(){

  int i;
  int j;

  for (i=HAUTEUR-1 ; i>0 ; i--){
    for (j=0 ; j<LARGEUR-1 ; j++){
      route[i][j] = route[i-1][j];
    }
  }

  for (j = 0 ; j < LARGEUR ; j++){
    route[0][j] = 0;
  }
}


/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu en appelant les autres fonctions
 * @return void
*/
void easyGame(){

  /* Tant qu'il n'y a pas de crash */
  while (crash() == 0){
    affichae_mat(route);
    decalage();
    /* On attend 3 secondes entre chaque décalage */
    sleep(3);
  }
}



int main(){

  easyGame();
  return 0;
}
