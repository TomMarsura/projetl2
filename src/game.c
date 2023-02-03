#include <stdio.h>




void affichae_mat(int mat[5][3]){

    int i,j;


    for (i = 0;i< 5;i++){

        for(j = 0;j<3;j++){
            printf("%d",mat[i][j]);
        }

        printf("\n");
    }
}

void obstacle(int mat[5][3]){

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

int crash(){
  int i;
  for (i=0;i<LARGEUR-1;i++){
    /*verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] == 2)){
      /*on retourne 1 pour signnfier le crash*/
      return 1;
    }
  }

