/**
 * @file game.c
 * @brief Bibliotheque Game.c
 * @authors Ayoub LAARIBI,Tom MARSURA,Thibaut
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "../lib/game.h"
#include "../lib/menu.h"

/* Include pour la fonction deplacement */
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


/* Include pour gérer le temps */
#include <time.h>



/**
*@brief Affiche le contenu d'une matrice
*@author Ayoub Laaribi
*@param[in] mat matrice de type int
*@return void
*/
void affichae_mat(){
  /*initialisation*/
    int i,j;
    system("clear");


    for (i = 0;i< 5;i++){

        for(j = 0;j<3;j++){
            printf("%d",route[i][j]);
        }
        printf("\n");
    }



}


/**
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles
 * @author Ayoub Laaribi
 * @param[in] mat matrice de type int
 * @return void
*/
void obstacle(){

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
    affichae_mat();
}


/**
 * @author Ayoub Laaribi
 * @brief formule qui calcule le score
 * @return int
*/
int calcul_score(){
  int point=11;
  int dist=5;

  return (point * cpt_distance)/dist;
}


/**
 * @brief Fonction crash : Cette fonction permet de savoir si la joueur a touché un obstacle, si oui cela renvoie 1
 * @author Thibaut Gasnier
 * @return int
*/
int crash(){

  int i;

  for (i=0; i<LARGEUR-1 ; i++){
    /*Verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] == 2)){
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
 * @brief Fonction clavier : Cette fonction permet de renvoyer le code ASCII de la touche renntré au clavier de manière non bloquante
 * @author Thibaut Gasnier
 * @return int
*/
int clavier() {

    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


/**
 * @brief Fonction deplacement : Cette fonction permet de deplacer la voiture si le joueur appuie sur la flèche de gauche ou sur la flèche de droite de son clavier
 * @author Thibaut Gasnier
 * @return void
*/
void deplacement(){

  time_t start_time = time(NULL);

  while ((time(NULL) - start_time) < 1) {

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

    if (clavier()){
      /* Si le joueur appuie sur la flèche de droite code ASCII=67 et verifier si la limite de la route sur la droite est dépassée */
      c = getchar();
      if ((c == 67) && (!(y == LARGEUR-1))){
        /* On modifie la position de la voiture dans la matrice */
        route[x][y] = 0;
        route[x][y+1] = 1;
        affichae_mat();
      }

      /* Si le joueur appuie sur la flèche de gauche code ASCII=68 et verifier si la limite de la route sur la gauche est dépassée */
      else if ((c == 68) && (!(y == 0))){
        /* On modifie la position de la voiture dans la matrice */
        route[x][y] = 0;
        route[x][y-1] = 1;
        affichae_mat();
      }
    }
  }
}


/**
 * @brief Fonction decalage : Cette fonction permet de décaler tout le contenu de la matrice une ligne plus bas
 * @author Thibaut Gasnier
 * @return void
*/
void decalage(){

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

  for (j = 0 ; j < LARGEUR ; j++){
    route[HAUTEUR-1][j] = 0;
  }

  /* On met la voiture a lligne du dessus */
  route[x][y] = 1;
  affichae_mat();
}


/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu en appelant les autres fonctions
 * @return void
*/
void easyGame(){

  affichae_mat();

  while(1){

    deplacement();

    if (crash() == 1){
      printf("CRASH !!\n");
      break;
    }
    else{
      decalage();
    }
  }
}



int main(){

  easyGame();
  return 0;
}
