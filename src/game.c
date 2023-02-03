/**
 * @file game.c
 * @brief Bibliotheque Game.c
 * @author Ayoub LAARIBI,Tom MARSURA,Thibaut
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "../lib/game.h"

/*Include pour la fonction deplacement*/
#include <termios.h>
#include <unistd.h>


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
  /*on retourne 0 quand il n'y a pas de crash*/
  return 0;

}


/**
 * @brief Fonction deplacement : Cette fonction permet de deplacer la voiture si le joueur appuie sur la flèche de gauche ou sur la flèche de droite de son clavier
 * @return void
*/
void deplacement(){

  /*La fonction clavier retourne le code ASCII de la touche du clavier sur la laquelle appuie le joueur */
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
  c = clavier();

  for (i=0;i<LARGEUR-1;i++){
    /*Trouver la postion de la voiture sur la ligne*/
    if (route[HAUTEUR-1][i] == 1){
      /*La variable x correspond à la ligne de la position de la voiture*/
      x = HAUTEUR-1;
      /*La variable y correspond à la colonne de la position de la voiture*/
      y = i;
    }
  }

  /*Si le joueur appuie sur la flèche de droite code ASCII=67*/
  if (c == 67){
    /*Verifier si la limite de la route sur la droite est dépassée*/
    if (!(y == LARGEUR)){
      /*On modifie la position de la voiture dans la matrice*/
      route[x][y] = 0;
      route[x][y+1] = 1;
    }
  }

  /*Si le joueur appuie sur la flèche de gauche code ASCII=68*/
  if (c == 68){
    /*Verifier si la limite de la route sur la gauche est dépassée*/
    if (!(y == 0)){
      /*On modifie la position de la voiture dans la matrice*/
      route[x][y] = 0;
      route[x][y-1] = 1;
    }
  }
}

int main(){

  return 0;
}
