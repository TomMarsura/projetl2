/**
 * @file fonctions_game.c
 * @brief Fonctions utilisée dans game.c
 * @authors Ayoub LAARIBI,Tom MARSURA,Thibaut GASNIER
 * @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
/*#include "../lib/game.h"*/
/*#include "../lib/menu.h"*/

/* Include pour la fonction deplacement */
#include "../lib/game.h"
#include "../lib/menu.h"
#include "../lib/sdl.h"
#include "../lib/fonctions_game.h"

/* Include pour gérer le temps */
#include <time.h>

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_ttf.h"

int lignes_succesives = 0;
int double_obs_succ = 0;


/**
*@brief Affiche le contenu d'une matrice
*@author Thibaut GASNIER
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
*@author Thibaut GASNIER
*@return int
*/
extern int nb_obstacle(){

  int nb = 0;
  int i;

  for (i=0;i< LARGEUR ;i++){
    if (route[1][i] > 1){
      nb++;
    }
  }

  return nb;
}



/**
  affichae_mat();
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles pour HardGame.
 * @author Tom MARSURA / Thibaut Gasnier
 * @return void
*/
extern void obstacle_hard(){

  int position1;

  int position2;

  int apparition;
  apparition = rand() % 100; /*genere un pourcentage pour décider si on ajoute un obsatcle*/

  if ((apparition > 40) && (lignes_succesives < 2)){
      int nbObstacle = nb_obstacle();

      if (nbObstacle == 0){ /*La ligne précédente comporte 0 obstacle*/
            int tirage1 = rand()%4 + 2;
            int tirage2 = rand()%4 + 2;
            int tirageNbObstacle = rand()%2 + 1;
            if(tirageNbObstacle == 1){
              position1 = rand() % LARGEUR;
              route[0][position1] = tirage1;
              lignes_succesives++;
            }

            else{
              position1 = rand() % LARGEUR;
              position2 = rand() % LARGEUR;

              while(position1 == position2){
                position2 = rand() % LARGEUR;
              }

              route[0][position1] = tirage1;
              route[0][position2] = tirage2;
              lignes_succesives++;
              double_obs_succ ++;
            }
      }

      else if (nb_obstacle() == 1){ /* La ligne précédente comport 1 obstacle */
        int tirageNbObstacle = rand()%2 + 1;

        if(tirageNbObstacle == 1){
          position1 = rand() % LARGEUR;
          int tirage = rand()%4 + 2;
          route[0][position1] = tirage;
          lignes_succesives++;
        }

        else if (tirageNbObstacle == 2){
          int positionObstacle;
          for (int i = 0; i < LARGEUR; i++){ /*On récupère la position de l'obstacle à la ligne précédente*/
            if (route[1][i] > 1){
              positionObstacle = i;
            }
          }
          position1 = rand() % LARGEUR;
          while (position1 == positionObstacle){
            position1 = rand() % LARGEUR;
          }
          int tirage1 = rand()%4 + 2;
          int tirage2 = rand()%4 + 2;
          route[0][position1] = tirage1;
          route[0][positionObstacle] = tirage2;
          lignes_succesives++;
        }
      }
    }
  else{
    lignes_succesives = 0;
    double_obs_succ = 0;
  }
}



/**
  affichae_mat();
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles pour easyGame.
 * @author Thibaut Gasnier
 * @return void
*/
extern void obstacle_easy(){

  int position;
  position = rand() % LARGEUR; /*genenere aléatoirement la position de l'obstacle*/

  int apparition;
  apparition = rand() % 100; /*genere un pourcentage pour décider si on ajoute un obsatcle*/

  if ((apparition > 40) && (lignes_succesives < 2)){
    int tirage = rand()%4 + 2;
    route[0][position] = tirage;
    lignes_succesives++;
  }
  else if (apparition < 20){
    route[0][position] = 9;
    }
  else{
    lignes_succesives = 0;
  }
}

/**
 * @brief Fonction obstacle : Cette fonction a pour but de generer aleatoirement des obstacles pour HardGame.
 * @author Tom MARSURA / Thibaut Gasnier
 * @return void
*/
extern void obstacle_piece(){

  int position1;

  int apparition;
  apparition = rand() % 100; /*genere un pourcentage pour décider si on ajoute un obsatcle*/

  if ((apparition > 60)){
      position1 = rand() % LARGEUR;
      route[0][position1] = 6;
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
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] > 1) && (route[HAUTEUR-2][i] != 9)){
      /* On retourne 1 pour signnfier le crash */
      return 1;
    }
  }
  /* On retourne 0 quand il n'y a pas de crash */
  return 0;
}


extern int bonus_pris(){

  int i;

  for (i=0; i<LARGEUR ; i++){
    /*Verifie si la ligne actuelle contient la voiture et si la la ligne supérieur est un obstacle*/
    if ((route[HAUTEUR-1][i] == 1) && (route[HAUTEUR-2][i] == 9)){
      /* On retourne 1 pour signnfier le crash */
      return 1;
    }
  }
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
  }

  /* Si le joueur appuie sur la flèche de gauche et verifier si la limite de la route sur la gauche est dépassée */
  if ((touche == 2) && (!(y == 0))){
  /* On modifie la position de la voiture dans la matrice */
    route[x][y] = 0;
    route[x][y-1] = 1;
  }
}



/**
 * @brief Fonction decalage : Cette fonction permet de décaler tout le contenu de la matrice une ligne plus bas
 * @author Thibaut Gasnier
 * @return void
*/
extern void decalage(){


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
}


/**
 * @author Ayoub LAARIBI
 * @brief Cette fonction permet a l'utilisateur de mettre pause
 * @return int
*/
extern int pause(SDL_Window* window, SDL_Renderer* renderer){

  int time;
  SDL_Color TextColor;
  TextColor.r = 255;
  TextColor.g = 255;
  TextColor.b = 255;

  SDL_Surface *ImageStart = IMG_Load("../img/background.jpg");
  if (ImageStart == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger l'image");
    }


  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, ImageStart);
  SDL_FreeSurface(ImageStart); /*liberation de la memoire*/

  if (texture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture");
    }

    /*Verification TTF_init*/
  if (TTF_Init() == -1)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Initialisation de TTF_Init a echoue");
    }

    /*Importation de la police*/
  TTF_Font *police = TTF_OpenFont("../fonts/police.TTF", 35);
  if (police == NULL)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Importation de la police a echouee");
    }

  TTF_Font *fontLogo = TTF_OpenFont("../fonts/police.TTF", 50);
  if (fontLogo == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Importation de la police a echouee");
    }

/* -------------------------------------------------------------------------- */
/* ------------------------- Creation des surface ------------------------- */
/* -------------------------------------------------------------------------- */

  SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", TextColor);
  SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
  SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };



  SDL_Surface *TextContinue = TTF_RenderText_Solid(police, "Continuer", TextColor);
  if (TextContinue == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

  SDL_Rect DistContinue = {70, 470, TextContinue->w, TextContinue->h};
  SDL_Texture *textTextureContinue = SDL_CreateTextureFromSurface(renderer, TextContinue);


  if (textTextureContinue == NULL)
    {
      TTF_CloseFont(police);
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }

/*.....................................................................................................................................*/

  SDL_Surface *TextQuitter = TTF_RenderText_Solid(police, "Quitter", TextColor);
    if (TextQuitter == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistQuitter = {510, 470, TextQuitter->w, TextQuitter->h};

    SDL_Texture *textTextureQuitter = SDL_CreateTextureFromSurface(renderer, TextQuitter);



    if (textTextureQuitter == NULL)
    {
      TTF_CloseFont(police);
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }
/*-------------------------------------------------------------------------------------------------------------------------------------*/

    time = SDL_GetTicks();
    int VisibleContinue = 1;
    int VisibleQuitter = 1;
    int position = 0;


    int quit = 0;
    while(!quit){

/* -------------------------------------------------------------------------- */
/* ------------------------- Gestion des évènements ------------------------- */
/* -------------------------------------------------------------------------- */
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){

                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){

                        case SDLK_ESCAPE:
                            quit = 1;
                        break;


                            case SDLK_RETURN:
                                if (position == 0) {
                                  /*Destruction de la fenetre pour revenir au jeu*/
                                  SDL_DestroyTexture(texture);
                                  SDL_DestroyTexture(textTextureContinue);
                                  SDL_DestroyTexture(textTextureQuitter);
                                  SDL_DestroyTexture(textureCarGame);
                                  TTF_CloseFont(police);

                                  SDL_FreeSurface(carGame);
                                  SDL_FreeSurface(TextContinue);
                                  SDL_FreeSurface(TextQuitter);

                                  texture = NULL;
                                  textTextureContinue = NULL;
                                  textTextureQuitter = NULL;
                                  police = NULL;
                                  carGame = NULL;
                                  TextContinue = NULL;
                                  TextQuitter = NULL;
                                  textureCarGame = NULL;
                                   return 0;

                                } else if (position == 1) {
                                  /*Destruction de la fenetre pour revenirau jeu*/
                                    SDL_DestroyTexture(texture);
                                    SDL_DestroyTexture(textTextureContinue);
                                    SDL_DestroyTexture(textTextureQuitter);
                                    SDL_DestroyTexture(textureCarGame);
                                    TTF_CloseFont(police);


                                    SDL_FreeSurface(carGame);
                                    SDL_FreeSurface(TextContinue);
                                    SDL_FreeSurface(TextQuitter);

                                    texture = NULL;
                                    textTextureContinue = NULL;
                                    textTextureQuitter = NULL;
                                    police = NULL;
                                    carGame = NULL;
                                    TextContinue = NULL;
                                    TextQuitter = NULL;
                                    textureCarGame = NULL;

                                    return 1;

                                }

                            break;

                  /*Incrementation des positions*/

                        case SDLK_RIGHT:
                            position++;

                            if (position > 1){
                                position = 0;
                            }
                        break;

                        case SDLK_LEFT:
                            position--;

                            if (position < 0){
                                position = 1;
                            }

                        break;
                    }
            }
        }

/* -------------------------------------------------------------------------- */
/* ------------------------- Gestion des clignotement ------------------------- */
/* -------------------------------------------------------------------------- */
        if ( position == 0)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleContinue = !VisibleContinue;
                int alpha = VisibleContinue ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureContinue, alpha);
            }
        }
        else
        {
            VisibleContinue = 1;
            int alpha = VisibleContinue ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureContinue, alpha);
        }


        if ( position == 1)
        {
            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleQuitter = !VisibleQuitter;
                int alpha = VisibleQuitter ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureQuitter, alpha);
            }
        }
        else
        {

            VisibleQuitter = 1;
            int alpha = VisibleQuitter ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureQuitter, alpha);
        }

/* ---------------------------------------------------------------- */
/* ------------------------- RENDU ------------------------- */
/* -----------------------------------------------------------------*/
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);
        SDL_RenderCopy(renderer, textTextureQuitter, NULL, &DistQuitter);
        SDL_RenderCopy(renderer, textTextureContinue, NULL, &DistContinue);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
