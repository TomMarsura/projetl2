#include <stdio.h>


int crash(){
  int i;
  for (i=0;i<LARGEUR-1;i++){
    /*verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] == 2)){
      /*on retourne 1 pour signnfier le crash*/
      return 1;
    }
  }

