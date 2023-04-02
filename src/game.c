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
#include "../lib/affichageMenu.h"

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
extern void easyGame(SDL_Window* window, SDL_Renderer* renderer){

  srand(time(NULL));

  initGame();

  SDL_Surface* car = IMG_Load("../img/car.png");
  SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

  SDL_Surface * img_obstacle_dog = IMG_Load("../img/dog.png");
  SDL_Texture * texture_obstacle_dog = SDL_CreateTextureFromSurface(renderer,img_obstacle_dog);

  SDL_Surface * img_obstacle_kid = IMG_Load("../img/kid.png");
  SDL_Texture * texture_obstacle_kid = SDL_CreateTextureFromSurface(renderer,img_obstacle_kid);

  SDL_Surface * img_obstacle_mamie = IMG_Load("../img/mamie.png");
  SDL_Texture * texture_obstacle_mamie = SDL_CreateTextureFromSurface(renderer,img_obstacle_mamie);

  SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
  SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

  SDL_Surface* fond = IMG_Load("../img/route.png");
  SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

  SDL_Color TextColor;
  TextColor.r = 255;
  TextColor.g = 255;
  TextColor.b = 255;

  char scoreText[50];
  sprintf(scoreText, "Score: %d", score);
  TTF_Font *police = TTF_OpenFont("../fonts/police.TTF", 20);
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(police, scoreText, TextColor);
  SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect scoreRect = { 10, 40, surfaceMessage->w, surfaceMessage->h };



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
  int score = 0;
  float a = 0;


  int vitesse = VITESSE_DEPART;

  affiche_mat();

  while (quit) {

    if (fin == 1){
      quit = 0;
      printf("CRASH\n");
      CrashMessage(window,renderer,score, 0);
      break;
    }

    if (fin > 1){
      quit = 0;
      printf("CRASH COTE\n");
      CrashMessage(window,renderer,score, 0);
      break;
    }

    else{

      int start_time = SDL_GetTicks();
      float increment_a = 1.2; // Initialisation de l'incrément
      int time_interval = vitesse / 90; // Temps entre chaque incrémentation
      a = 0;

      while ((SDL_GetTicks() - start_time) < vitesse) {

        if ((SDL_GetTicks() - start_time) % time_interval == 0) {
          a += increment_a;
        }

        while (SDL_PollEvent(&event)) {

          if (event.type == SDL_QUIT) {
            quit = 0;
          }

          if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

              case SDLK_RIGHT:
                if (crash_cote == 0){
                  position_voiture++;

                  if (route[HAUTEUR-1][position_voiture] > 1){
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

                  if (route[HAUTEUR-1][position_voiture] > 1){
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
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
              }
              if (route[i][j] == 3) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_dog, NULL, &rectangle);
              }
              if (route[i][j] == 4) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_kid, NULL, &rectangle);
              }
              if (route[i][j] == 5) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_mamie, NULL, &rectangle);
              }
            }
          }
          // Convertir le score en une chaîne de caractères
          sprintf(scoreText, "Score: %d", score);
          surfaceMessage = TTF_RenderText_Solid(police, scoreText, TextColor);
          scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
          SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

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

      score++;



    }
  }

  // Libérer la mémoire allouée pour l'image et la fenêtre SDL
  SDL_FreeSurface(car);
  car = NULL;
  SDL_FreeSurface(fond);
  fond = NULL;
  SDL_FreeSurface(img_obstacle);
  img_obstacle = NULL;
  SDL_FreeSurface(surfaceMessage);
  surfaceMessage = NULL;


  SDL_DestroyTexture(texture_voiture);
  texture_voiture = NULL;
  SDL_DestroyTexture(texture_route);
  texture_route = NULL;
  SDL_DestroyTexture(texture_obstacle);
  texture_obstacle = NULL;
  SDL_DestroyTexture(scoreTexture);
  scoreTexture = NULL;

  IMG_Quit();
}




/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu au niveau Medium
 * @return void
*/
extern void MediumGame(SDL_Window* window, SDL_Renderer* renderer){

  srand(time(NULL));

  initGame();

  SDL_Surface* car = IMG_Load("../img/car.png");
  SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

  SDL_Surface * img_obstacle_dog = IMG_Load("../img/dog.png");
  SDL_Texture * texture_obstacle_dog = SDL_CreateTextureFromSurface(renderer,img_obstacle_dog);

  SDL_Surface * img_obstacle_kid = IMG_Load("../img/kid.png");
  SDL_Texture * texture_obstacle_kid = SDL_CreateTextureFromSurface(renderer,img_obstacle_kid);

  SDL_Surface * img_obstacle_mamie = IMG_Load("../img/mamie.png");
  SDL_Texture * texture_obstacle_mamie = SDL_CreateTextureFromSurface(renderer,img_obstacle_mamie);

  SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
  SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

  SDL_Surface* fond = IMG_Load("../img/route.png");
  SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

  SDL_Color TextColor;
  TextColor.r = 255;
  TextColor.g = 255;
  TextColor.b = 255;

  char scoreText[50];
  sprintf(scoreText, "Score: %d", score);
  TTF_Font *police = TTF_OpenFont("../fonts/police.TTF", 20);
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(police, scoreText, TextColor);
  SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect scoreRect = { 10, 40, surfaceMessage->w, surfaceMessage->h };



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
  int score = 0;
  float a = 0;


  int vitesse = VITESSE_DEPART;

  affiche_mat();

  while (quit) {

    if (fin == 1){
      quit = 0;
      printf("CRASH\n");
      CrashMessage(window,renderer,score, 1);
      break;
    }

    if (fin > 1){
      quit = 0;
      printf("CRASH COTE\n");
      CrashMessage(window,renderer,score, 1);
      break;
    }

    else{

      int start_time = SDL_GetTicks();
      float increment_a = 1.2; // Initialisation de l'incrément
      int time_interval = vitesse / 90; // Temps entre chaque incrémentation
      a = 0;

      while ((SDL_GetTicks() - start_time) < vitesse) {

        if ((SDL_GetTicks() - start_time) % time_interval == 0) {
          a += increment_a;
        }

        while (SDL_PollEvent(&event)) {

          if (event.type == SDL_QUIT) {
            quit = 0;
          }

          if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

              case SDLK_RIGHT:
                if (crash_cote == 0){
                  position_voiture++;

                  if (route[HAUTEUR-1][position_voiture] > 1){
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

                  if (route[HAUTEUR-1][position_voiture] > 1){
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
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
              }
              if (route[i][j] == 3) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_dog, NULL, &rectangle);
              }
              if (route[i][j] == 4) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_kid, NULL, &rectangle);
              }
              if (route[i][j] == 5) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_mamie, NULL, &rectangle);
              }
            }
          }
          // Convertir le score en une chaîne de caractères
          sprintf(scoreText, "Score: %d", score);
          surfaceMessage = TTF_RenderText_Solid(police, scoreText, TextColor);
          scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
          SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

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

      score++;



    }
  }

  // Libérer la mémoire allouée pour l'image et la fenêtre SDL
  SDL_FreeSurface(car);
  car = NULL;
  SDL_FreeSurface(fond);
  fond = NULL;
  SDL_FreeSurface(img_obstacle);
  img_obstacle = NULL;
  SDL_FreeSurface(surfaceMessage);
  surfaceMessage = NULL;


  SDL_DestroyTexture(texture_voiture);
  texture_voiture = NULL;
  SDL_DestroyTexture(texture_route);
  texture_route = NULL;
  SDL_DestroyTexture(texture_obstacle);
  texture_obstacle = NULL;
  SDL_DestroyTexture(scoreTexture);
  scoreTexture = NULL;

  IMG_Quit();
}




/**
 * @brief Fonction easyGame : Cette fonction est la fonction principale qui permet de gerer le jeu au niveau Hard.
 * @return void
*/
extern void HardGame(SDL_Window* window, SDL_Renderer* renderer){

  srand(time(NULL));

  initGame();

  SDL_Surface* car = IMG_Load("../img/car.png");
  SDL_Texture * texture_voiture = SDL_CreateTextureFromSurface(renderer,car);

  SDL_Surface * img_obstacle_dog = IMG_Load("../img/dog.png");
  SDL_Texture * texture_obstacle_dog = SDL_CreateTextureFromSurface(renderer,img_obstacle_dog);

  SDL_Surface * img_obstacle_kid = IMG_Load("../img/kid.png");
  SDL_Texture * texture_obstacle_kid = SDL_CreateTextureFromSurface(renderer,img_obstacle_kid);

  SDL_Surface * img_obstacle_mamie = IMG_Load("../img/mamie.png");
  SDL_Texture * texture_obstacle_mamie = SDL_CreateTextureFromSurface(renderer,img_obstacle_mamie);

  SDL_Surface* img_obstacle = IMG_Load("../img/obstacle.png");
  SDL_Texture * texture_obstacle = SDL_CreateTextureFromSurface(renderer,img_obstacle);

  SDL_Surface* fond = IMG_Load("../img/route.png");
  SDL_Texture* texture_route = SDL_CreateTextureFromSurface(renderer,fond);

  SDL_Color TextColor;
  TextColor.r = 255;
  TextColor.g = 255;
  TextColor.b = 255;

  char scoreText[50];
  sprintf(scoreText, "Score: %d", score);
  TTF_Font *police = TTF_OpenFont("../fonts/police.TTF", 20);
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(police, scoreText, TextColor);
  SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect scoreRect = { 10, 40, surfaceMessage->w, surfaceMessage->h };



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
  int score = 0;
  float a = 0;


  int vitesse = VITESSE_DEPART;

  affiche_mat();

  while (quit) {

    if (fin == 1){
      quit = 0;
      printf("CRASH\n");
      CrashMessage(window,renderer,score, 2);
      break;
    }

    if (fin > 1){
      quit = 0;
      printf("CRASH COTE\n");
      CrashMessage(window,renderer,score, 2);
      break;
    }

    else{

      int start_time = SDL_GetTicks();
      float increment_a = 1.2; // Initialisation de l'incrément
      int time_interval = vitesse / 90; // Temps entre chaque incrémentation
      a = 0;

      while ((SDL_GetTicks() - start_time) < vitesse) {

        if ((SDL_GetTicks() - start_time) % time_interval == 0) {
          a += increment_a;
        }

        while (SDL_PollEvent(&event)) {

          if (event.type == SDL_QUIT) {
            quit = 0;
          }

          if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

              case SDLK_RIGHT:
                if (crash_cote == 0){
                  position_voiture++;

                  if (route[HAUTEUR-1][position_voiture] > 1){
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

                  if (route[HAUTEUR-1][position_voiture] > 1){
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
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle, NULL, &rectangle);
              }
              if (route[i][j] == 3) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_dog, NULL, &rectangle);
              }
              if (route[i][j] == 4) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_kid, NULL, &rectangle);
              }
              if (route[i][j] == 5) {
                  rectangle.x = startX + j * 160; // Position horizontale de la case
                  rectangle.y = startY + i * 100 + a; // Position verticale de la case
                  SDL_RenderCopy(renderer, texture_obstacle_mamie, NULL, &rectangle);
              }
            }
          }
          // Convertir le score en une chaîne de caractères
          sprintf(scoreText, "Score: %d", score);
          surfaceMessage = TTF_RenderText_Solid(police, scoreText, TextColor);
          scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
          SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

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
        vitesse = vitesse - 10;
        printf("Vitesse = %d\n",vitesse);
      }

      score++;



    }
  }

  // Libérer la mémoire allouée pour l'image et la fenêtre SDL
  SDL_FreeSurface(car);
  car = NULL;
  SDL_FreeSurface(fond);
  fond = NULL;
  SDL_FreeSurface(img_obstacle);
  img_obstacle = NULL;
  SDL_FreeSurface(surfaceMessage);
  surfaceMessage = NULL;


  SDL_DestroyTexture(texture_voiture);
  texture_voiture = NULL;
  SDL_DestroyTexture(texture_route);
  texture_route = NULL;
  SDL_DestroyTexture(texture_obstacle);
  texture_obstacle = NULL;
  SDL_DestroyTexture(scoreTexture);
  scoreTexture = NULL;

  IMG_Quit();
}
