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

void play(SDL_Window *window, SDL_Renderer *renderer)
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

            default:
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}


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

    SDL_SetWindowIcon(window, IMG_Load("voiture_menu.png"));

    menu = IMG_Load("voiture_menu.png");
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
}