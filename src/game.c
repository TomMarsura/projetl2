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

/* Include pour gérer le temps */
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>



/**
*@brief Affiche le contenu d'une matrice
*@author Ayoub Laaribi
*@param[in] mat matrice de type int
*@return void
*/
extern void affiche_mat(){
  /*initialisation*/
    int i,j;

    for (i = 0;i< HAUTEUR;i++){

        for(j = 0;j<LARGEUR;j++){
            printf("%d",route[i][j]);
        }
        printf("\n");
    }
      printf("\n");
      printf("\n");
      printf("\n");

}


/**
  affichae_mat();
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles
 * @author Ayoub Laaribi / Thibaut Gasnier
 * @return void
*/
extern void obstacle(){

    int position1;
    position1 = rand() % LARGEUR; /*genenere aléatoirement la position du première obstacle*/

    int position2;
    position2 = rand() % LARGEUR; /*genenere aléatoirement la position du deuxième obstacle*/

    int apparition;
    apparition = rand() % 100; /*genere un pourcentage pour décider si on ajoute un obsatcle*/

    int nb_obstacle_ligne;
    nb_obstacle_ligne = rand() % 100; /*genere un pourcentage pour décider si on ajoute 1 ou 2 obsatcles à la ligne*/

    // Vérifier que la position1 et position2 ne sont pas sur la même colonne pour éviter les obstacles superposés
    while (position1 == position2) {
        position2 = rand() % LARGEUR;
    }

    if (apparition > 50){
        if(nb_obstacle_ligne>33){
            if (route[1][position1] != 1 && route[1][position2] != 1) {
                route[0][position1] = 2;
            }
            else {
                route[0][position2] = 2;
            }
        }
        else{
            if (route[1][position1] != 1) {
                route[0][position1] = 2;
            }
            else if (route[1][position2] != 1) {
                route[0][position2] = 2;
            }
            else {
                // S'il y a un obstacle sur les deux colonnes, on ajoute un obstacle sur une colonne différente
                int position3 = rand() % LARGEUR;
                while (position3 == position1 || position3 == position2) {
                    position3 = rand() % LARGEUR;
                }
                route[0][position3] = 2;
            }
        }
    }
}



/**
 * @brief Fonction crash : Cette fonction permet de savoir si la joueur a touché un obstacle, si oui cela renvoie 1
 * @author Thibaut Gasnier
 * @return int
*/
extern int crash(){

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
 * @brief Fonction deplacement : Cette fonction permet de deplacer la voiture si le joueur appuie sur la flèche de gauche ou sur la flèche de droite de son clavier
 * @author Thibaut Gasnier
 * @return void
*/
extern void deplacement(int touche){

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


/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu en appelant les autres fonctions
 * @return void
*/
extern void easyGame(int profil){

  affiche_mat();

  int vitesse = 1;

  while(1){

    deplacement(vitesse);

    if (crash() == 1){
      printf("CRASH !!\n");
      printf("SCORE : %d \n",score);
      /*pointsProfils[profil] += score;*/
      break;
    }
    else{
      decalage();
      score = score + 1;
      obstacle();

      /*On verifie si la vitesse maximale est atteinte */
      if (vitesse >= VITESSE_MAX){
        vitesse = vitesse - 0.05;
      }
    }
  }
}


int main(int argc, char* argv[]) {
    // Initialiser SDL
    SDL_Init(SDL_INIT_VIDEO);

    IMG_Init(IMG_INIT_JPG);

    // Créer une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow("GAME CAR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);

    SDL_Surface* car = IMG_Load("../img/car.png");
    SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

    SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
    SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

    SDL_Surface* fond = IMG_Load("../img/route.png");
    SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

    SDL_Rect rectangle;

    rectangle.w = rectangle.h = 100; // Taille de chaque case de la matrice

    // Calculer la position de départ du rectangle pour centrer la matrice
    int startX = (800 - LARGEUR * 135) / 2;
    int startY = (800 - HAUTEUR * 100) / 2;

    SDL_RenderCopy(renderer, texture_route, NULL, NULL); // Dessiner l'image de fond


    SDL_Event event;
    int quit = 1;
    int crash_cote = 0;
    int position_voiture = 1;

    float vitesse = 0.1;

    affiche_mat();

    while (quit) {

      if (crash() == 1){
        quit = 0;
        printf("CRASH\n");
        break;
      }

      if (crash_cote == 1){
        quit = 0;
        printf("CRASH COTE\n");
        break;
      }

      else{

        time_t start_time = time(NULL);

        while ((time(NULL) - start_time) < 0.5) {

          while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
              quit = 0;
            }

            if (event.type == SDL_KEYDOWN) {
              switch (event.key.keysym.sym) {

                case SDLK_RIGHT:
                    position_voiture++;

                    if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                    }
                    deplacement(1);
                    break;

                    case SDLK_LEFT:
                      position_voiture--;

                      if (route[HAUTEUR-1][position_voiture] == 2){
                        crash_cote = 1;
                      }
                      deplacement(2);
                      break;

                      default:
                        break;
                }
              }
            }

            SDL_RenderCopy(renderer, texture_route, NULL, NULL);


            /* Dessiner l'image de la voiture pour chaque case de la matrice qui contient un 1 */
            for (int i = 0; i < HAUTEUR; i++) {
              for (int j = 0; j < LARGEUR; j++) {
                if (route[i][j] == 1) {
                    rectangle.x = startX + j * 160; // Position horizontale de la case
                    rectangle.y = startY + i * 100; // Position verticale de la case
                    SDL_RenderCopy(renderer, texture_voiture, NULL, &rectangle);
                }
                if (route[i][j] == 2) {
                    rectangle.x = startX + j * 160; // Position horizontale de la case
                    rectangle.y = startY + i * 150; // Position verticale de la case
                    SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
                }
              }
            }
            SDL_RenderPresent(renderer);
        }

      decalage();
      obstacle();
      vitesse = vitesse - 0.05;

    }
  }

    // Libérer la mémoire allouée pour l'image et la fenêtre SDL
    SDL_FreeSurface(car);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(img_obstacle);

    SDL_DestroyTexture(texture_voiture);
    SDL_DestroyTexture(texture_route);
    SDL_DestroyTexture(texture_obstacle);

    SDL_DestroyWindow(window);

    // Quitter SDL et SDL_image
    IMG_Quit();
    SDL_Quit();

    return 0;

}




//int main(){
//
//  easyGame(0);
//  return 0;
//}
