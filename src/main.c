#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../lib/sdl.h"
#include "../lib/game.h"
#include "../lib/menu.h"



/*FONCTION PRINCIPAL*/

int main(int argc, char *argv[])
{
    /*initialisation*/
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    TTF_Init();

    SDL_Event event;
    SDL_Color TextColor;
    TextColor.r = 30;
    TextColor.g = 29;
    TextColor.b = 34;

    unsigned int time;

    /*Verification de sdl_init*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithMessage("Initialisation de la SDL echouee");
    }

    SDL_Window *window = SDL_CreateWindow("Car GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
    {
        SDL_ExitWithMessage("Creation de fenetre echoue\n");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Creation rendu echouée");
    }

    /*Chargement de l'image du menu*/
    SDL_Surface *ImageStart = IMG_Load("../img/voiture.gif");
    if (ImageStart == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger l'image");
    }

    /*Creation de la texture*/
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
    TTF_Font *police = TTF_OpenFont("../img/police.TTF", 35);
    if (police == NULL)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Importation de la police a echouee");
    }

    SDL_Surface *TextSurface = TTF_RenderText_Solid(police, "PRESS ENTER !", TextColor);
    if (TextSurface == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistR = {190, 100, TextSurface->w, TextSurface->h};

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);

    SDL_FreeSurface(TextSurface);

    if (textTexture == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }

    time = SDL_GetTicks();
    int Visible = 1;

    while (program_launched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    program_launched = SDL_FALSE;
                    break;
                case SDL_SCANCODE_KP_ENTER:
                    Lancement_menu(window, renderer);
                    printf("Vous avez appuye sur la touche ENTRER\n");
                    break;

                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        unsigned ActualTime = SDL_GetTicks();

        if (ActualTime > time + 500)
        {
            time = ActualTime;
            Visible = !Visible;
            int alpha = Visible ? 255 : 0;
            SDL_SetTextureAlphaMod(textTexture, alpha);
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, textTexture, NULL, &DistR);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}