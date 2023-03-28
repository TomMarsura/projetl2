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



/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu au niveau Easy.
 * @return void
*/
extern void easyGame(SDL_Window* window, SDL_Renderer* renderer, int profil){

  srand(time(NULL));

  initGame();

  // Initialiser SDL
  SDL_Init(SDL_INIT_VIDEO);

  IMG_Init(IMG_INIT_JPG);

  SDL_Surface* car = IMG_Load("../img/car.png");
  SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

  SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
  SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

  SDL_Surface* fond = IMG_Load("../img/route.png");
  SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

  SDL_Rect rectangle;

  rectangle.w = rectangle.h = 90; // Taille de chaque case de la matrice

  // Calculer la position de départ du rectangle pour centrer la matrice
  int startX = (800 - LARGEUR * 135) / 2;
  int startY = (800 - HAUTEUR * 100) / 2;

  SDL_RenderCopy(renderer, texture_route, NULL, NULL); // Dessiner l'image de fond


  SDL_Event event;
  int quit = 1;
  int crash_cote = 0;
  int position_voiture = 1;
  int fin = 0;

  int vitesse = VITESSE_DEPART;

  affiche_mat();

  while (quit) {

    if (fin == 1){
      quit = 0;
      printf("CRASH\n");
      break;
    }

    if (fin == 2){
      quit = 0;
      printf("CRASH COTE\n");
      break;
    }

    else{

      int start_time = SDL_GetTicks();

      while ((SDL_GetTicks() - start_time) < vitesse) {

        while (SDL_PollEvent(&event)) {

          if (event.type == SDL_QUIT) {
            quit = 0;
          }

          if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

              case SDLK_RIGHT:
                if (crash_cote == 0){
                  position_voiture++;

                  if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                  }
                  printf(" Crash cote = %d\n",crash_cote);
                  if (crash_cote == 0){
                    deplacement(1);
                  }
                  break;
                }

              case SDLK_LEFT:
                if (crash_cote == 0){
                  position_voiture--;

                  if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                  }
                  printf(" Crash cote = %d\n",crash_cote);
                  if (crash_cote == 0){
                    deplacement(2);
                  }
                  break;
                }

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
                  rectangle.y = startY + i * 100; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
              }
            }
          }
          SDL_RenderPresent(renderer);
      }

      if (crash() == 1){
        fin = 1;
      }

      if (crash_cote == 1){
        fin = 2;
      }
      decalage();
      obstacle_easy();

      if (vitesse > VITESSE_MAX_EASY){
        vitesse = vitesse - 10;
        printf("Vitesse = %d\n",vitesse);
      }



    }
  }

  // Libérer la mémoire allouée pour l'image et la fenêtre SDL
  SDL_FreeSurface(car);
  car = NULL;
  SDL_FreeSurface(fond);
  fond = NULL;
  SDL_FreeSurface(img_obstacle);
  img_obstacle = NULL;

  SDL_DestroyTexture(texture_voiture);
  texture_voiture = NULL;
  SDL_DestroyTexture(texture_route);
  texture_route = NULL;
  SDL_DestroyTexture(texture_obstacle);
  texture_obstacle = NULL;

  IMG_Quit();
}




/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu au niveau Medium
 * @return void
*/
extern void MediumGame(SDL_Window* window, SDL_Renderer* renderer, int profil){

  srand(time(NULL));

  initGame();

  // Initialiser SDL
  SDL_Init(SDL_INIT_VIDEO);

  IMG_Init(IMG_INIT_JPG);

  SDL_Surface* car = IMG_Load("../img/car.png");
  SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

  SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
  SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

  SDL_Surface* fond = IMG_Load("../img/route.png");
  SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

  SDL_Rect rectangle;

  rectangle.w = rectangle.h = 90; // Taille de chaque case de la matrice

  // Calculer la position de départ du rectangle pour centrer la matrice
  int startX = (800 - LARGEUR * 135) / 2;
  int startY = (800 - HAUTEUR * 100) / 2;

  SDL_RenderCopy(renderer, texture_route, NULL, NULL); // Dessiner l'image de fond


  SDL_Event event;
  int quit = 1;
  int crash_cote = 0;
  int position_voiture = 1;
  int fin = 0;

  int vitesse = VITESSE_DEPART;

  affiche_mat();

  while (quit) {

    if (fin == 1){
      quit = 0;
      printf("CRASH\n");
      break;
    }

    if (fin == 2){
      quit = 0;
      printf("CRASH COTE\n");
      break;
    }

    else{

      int start_time = SDL_GetTicks();

      while ((SDL_GetTicks() - start_time) < vitesse) {

        while (SDL_PollEvent(&event)) {

          if (event.type == SDL_QUIT) {
            quit = 0;
          }

          if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

              case SDLK_RIGHT:
                if (crash_cote == 0){
                  position_voiture++;

                  if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                  }
                  printf(" Crash cote = %d\n",crash_cote);
                  if (crash_cote == 0){
                    deplacement(1);
                  }
                  break;
                }

              case SDLK_LEFT:
                if (crash_cote == 0){
                  position_voiture--;

                  if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                  }
                  printf(" Crash cote = %d\n",crash_cote);
                  if (crash_cote == 0){
                    deplacement(2);
                  }
                  break;
                }

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
                  rectangle.y = startY + i * 100; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
              }
            }
          }
          SDL_RenderPresent(renderer);
      }

      if (crash() == 1){
        fin = 1;
      }

      if (crash_cote == 1){
        fin = 2;
      }
      decalage();
      obstacle_hard();

      if (vitesse > VITESSE_MAX_EASY){
        vitesse = vitesse - 10;
        printf("Vitesse = %d\n",vitesse);
      }



    }
  }

  // Libérer la mémoire allouée pour l'image et la fenêtre SDL
  SDL_FreeSurface(car);
  car = NULL;
  SDL_FreeSurface(fond);
  fond = NULL;
  SDL_FreeSurface(img_obstacle);
  img_obstacle = NULL;

  SDL_DestroyTexture(texture_voiture);
  texture_voiture = NULL;
  SDL_DestroyTexture(texture_route);
  texture_route = NULL;
  SDL_DestroyTexture(texture_obstacle);
  texture_obstacle = NULL;

  IMG_Quit();
}




/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu au niveau Hard.
 * @return void
*/
extern void HardGame(SDL_Window* window, SDL_Renderer* renderer, int profil){

  srand(time(NULL));

  initGame();

  // Initialiser SDL
  SDL_Init(SDL_INIT_VIDEO);

  IMG_Init(IMG_INIT_JPG);

  SDL_Surface* car = IMG_Load("../img/car.png");
  SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

  SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
  SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

  SDL_Surface* fond = IMG_Load("../img/route.png");
  SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

  SDL_Rect rectangle;

  rectangle.w = rectangle.h = 90; // Taille de chaque case de la matrice

  // Calculer la position de départ du rectangle pour centrer la matrice
  int startX = (800 - LARGEUR * 135) / 2;
  int startY = (800 - HAUTEUR * 100) / 2;

  SDL_RenderCopy(renderer, texture_route, NULL, NULL); // Dessiner l'image de fond


  SDL_Event event;
  int quit = 1;
  int crash_cote = 0;
  int position_voiture = 1;
  int fin = 0;

  int vitesse = VITESSE_DEPART;

  affiche_mat();

  while (quit) {

    if (fin == 1){
      quit = 0;
      printf("CRASH\n");
      break;
    }

    if (fin == 2){
      quit = 0;
      printf("CRASH COTE\n");
      break;
    }

    else{

      int start_time = SDL_GetTicks();

      while ((SDL_GetTicks() - start_time) < vitesse) {

        while (SDL_PollEvent(&event)) {

          if (event.type == SDL_QUIT) {
            quit = 0;
          }

          if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

              case SDLK_RIGHT:
                if (crash_cote == 0){
                  position_voiture++;

                  if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                  }
                  printf(" Crash cote = %d\n",crash_cote);
                  if (crash_cote == 0){
                    deplacement(1);
                  }
                  break;
                }

              case SDLK_LEFT:
                if (crash_cote == 0){
                  position_voiture--;

                  if (route[HAUTEUR-1][position_voiture] == 2){
                    crash_cote = 1;
                  }
                  printf(" Crash cote = %d\n",crash_cote);
                  if (crash_cote == 0){
                    deplacement(2);
                  }
                  break;
                }

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
                  rectangle.y = startY + i * 100; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
              }
            }
          }
          SDL_RenderPresent(renderer);
      }

      if (crash() == 1){
        fin = 1;
      }

      if (crash_cote == 1){
        fin = 2;
      }
      decalage();
      obstacle_hard();

      if (vitesse > VITESSE_MAX_HARD){
        vitesse = vitesse - 15;
        printf("Vitesse = %d\n",vitesse);
      }



    }
  }

  // Libérer la mémoire allouée pour l'image et la fenêtre SDL
  SDL_FreeSurface(car);
  car = NULL;
  SDL_FreeSurface(fond);
  fond = NULL;
  SDL_FreeSurface(img_obstacle);
  img_obstacle = NULL;

  SDL_DestroyTexture(texture_voiture);
  texture_voiture = NULL;
  SDL_DestroyTexture(texture_route);
  texture_route = NULL;
  SDL_DestroyTexture(texture_obstacle);
  texture_obstacle = NULL;

  IMG_Quit();
}
