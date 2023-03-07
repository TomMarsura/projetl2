#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>


#include "../lib/game.h"
#include "../lib/menu.h"



/*Commande pour compiler : gcc -o sdl sdl.c -L:/usr/include -lSDL2main -lSDL2 -lSDL2_image

                                ou
gcc -o sdl sdl.c -lSDL2main -lSDL2 -lSDL2_image                     
*/

#define TAILLE_BLOCK 34


enum {GAUCHE,MILIEU,DROITE};
enum{VOITURE,OBSTACLE};


SDL_Rect position, positionJoueur;

void play(SDL_Window *window, SDL_Renderer *renderer)
{
    
    
   /* SDL_Surface *deplacement[3] = NULL;
    SDL_Surface *PosVoiture = NULL;


    /*telechargement image
    deplacement[MILIEU] = IMG_Load("../img/pixel_car.png");
    PosVoiture = deplacement(MILIEU);

    positionJoueur.x = 3;
    positionJoueur.y = 3;*/






    SDL_Event event;
    int continuer = 1;

    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            break;

             case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                break;
                }

            default:
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        //position.x = positionJoueur.x *TAILLE_BLOCK;
        //position.x = positionJoueur.y *TAILLE_BLOCK;

        //SDL_BlitSurface(PosVoiture,NULL,window,&position);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }


    /*for (int i = 0;i<4;i++){
        SDL_FreeSurface(deplacement[i]);
    }*/
}

/*FONCTION MENU*/

/***************************************************************************************
Cette fonction permet:
                        - Classement
                        - choix du profil
                        - Creation profil
                        -Lancement du jeu
                        - shop
*****************************************************************************************/
void menu (SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Event event;
    int continuer = 1;

    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            break;

             case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                break;
                }
                case SDLK_1:
                    /*select profile*/
                break;

                case SDLK_2:
                    /*create profil*/
                break;

                case SDLK_3:
                    /*Lancement_du_jeu();*/
                break;

            default:
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

}




/*FONCTION LANCEMENT DU JEU*/

/***************************************************************************************
Cette fonction permet d'ouvrir une fenetre et d'afficher le jeu en action avec lechoix de 
difficulté
*****************************************************************************************/
void Lancement_du_jeu(SDL_Window *window, SDL_Renderer *renderer)
{

}
/*
int main(int argc, char* argv[]){
    
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* menu = NULL;
    int continuer = 1;
    SDL_Rect positionMenu;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Car GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 730, 442, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetWindowIcon(window, IMG_Load("../img/voiture.gif"));

    menu = IMG_Load("../img/voiture.gif");
    SDL_Texture* textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
    positionMenu.x = 0;
    positionMenu.y = 0;
    positionMenu.w = menu->w;
    positionMenu.h = menu->h;
    SDL_FreeSurface(menu);

    while(continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                    break;

                    case SDLK_1:
                        play(window,renderer);
                    break;
                    default:
                        break;
                }
                break;
        }

        SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureMenu);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
    }*/


int main(int argc, char* argv[])
{
    int continuer = 1;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* surface = IMG_Load("../img/voiture.gif");
    SDL_Window* window = SDL_CreateWindow("Car GAME", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          surface->w, 
                                          surface->h, 
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while(continuer)
    {

        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDLK_ESCAPE:
            continuer = 0;
            break;
        default:
            break;
        }
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


