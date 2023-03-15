#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../lib/sdl.h"

/*gcc -o sdl sdl.c -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf*/

/*FONCTION SDL_ExitWithMessage*/

/*******************************************************
Cette fonction renvoie un message d'erreur et qui la SDL
********************************************************/
extern void SDL_ExitWithMessage(const char *message)
{
    SDL_Log("ERREUR : %s  \n", message);
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/*FONCTION LANCEMENT MENU*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Cette fonction lance le menu et permet:
                                    - PLAY
                                    - CHOIX PROFIL
                                    - CREATE PRPOFIL
                                    - CLASSEMENT
                                    - SHOP
                                    - QUIT
*************************************************************************/
extern void Lancement_menu(SDL_Window *window, SDL_Renderer *renderer)
{

    SDL_Color TextColor;
    TextColor.r = 30;
    TextColor.g = 29;
    TextColor.b = 34;
    //int choix = 0;
    int time;

    SDL_Surface *ImageStart = IMG_Load("../img/voiture.gif");
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
    TTF_Font *police = TTF_OpenFont("../img/police.TTF", 35);
    if (police == NULL)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Importation de la police a echouee");
    }

    SDL_Surface *TextPlay = TTF_RenderText_Solid(police, "PLAY", TextColor);
    if (TextPlay == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistR = {90, 100, TextPlay->w, TextPlay->h};

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, TextPlay);

    SDL_FreeSurface(TextPlay);

    if (textTexture == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }

    SDL_Surface *ChooseProfile = TTF_RenderText_Solid(police, "Choose Profile", TextColor);
    if (ChooseProfile == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistChooseProfile = {90, 150, ChooseProfile->w, ChooseProfile->h};

    SDL_Texture *textTextureChoose = SDL_CreateTextureFromSurface(renderer, ChooseProfile);

    SDL_FreeSurface(ChooseProfile);

    if (textTexture == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }

    // affichage des texte PLAY, CHOOSE PROFILE QUIT

    time = SDL_GetTicks();
    int VisiblePlay = 1;
    int VisibleChoose = 1;
    //choix = 0;
    int position = 0;
    while (program_launched)
    {
        SDL_Event event;
        // choix = choice_menu(event,textTexture);

        // choix = choice_menu(event);

        // int i = 0;

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

                case SDLK_ESCAPE:
                    program_launched = SDL_FALSE;
                    break;

                case SDL_SCANCODE_KP_ENTER:
                    printf("Vous avez appuye sur la touche ENTRER\n");
                    break;

                // BAS
                case SDL_SCANCODE_DOWN:
                    position = position + 1;
                    printf("Vous avez appuye sur la touche BAS\n%d\n", position);
                    // return position;

                    break;
                case SDL_SCANCODE_S:
                    position = position + 1;
                    printf("Vous avez appuye sur la touche BAS\n%d\n", position);

                    // return position;
                    break;

                // HAUT
                case SDL_SCANCODE_Z:
                    position = position + 1;
                    printf("Vous avez appuye sur la touche BAS\n%d\n", position);
                    // eturn position;
                    break;
                case SDL_SCANCODE_UP:
                    if (position > 0)
                    {
                        position = position - 1;
                        printf("Vous avez appuye sur la touche HAUT\n%d\n", position);
                        // return position;
                    }
                    else
                    {

                        position = 0;
                    }

                    break;

                default:
                    program_launched = SDL_FALSE;
                    break;
                }
            }
        }

        // Si la position est egal a 0 clignotement du message Play
        if (position == 0)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisiblePlay = !VisiblePlay;
                int alpha = VisiblePlay ? 255 : 0;
                SDL_SetTextureAlphaMod(textTexture, alpha);
            }
        }
        else
        {

            VisiblePlay = 1;
            int alpha = VisiblePlay ? 255 : 0;
            SDL_SetTextureAlphaMod(textTexture, alpha);
        }

        if (position == 1)
        {
            SDL_Log("test 1\n");
            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleChoose = !VisibleChoose;
                int alpha = VisibleChoose ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureChoose, alpha);
            }
        }
        else
        {

            VisibleChoose = 1;
            int alpha = VisibleChoose ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureChoose, alpha);
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, textTextureChoose, NULL, &DistChooseProfile);
        SDL_RenderCopy(renderer, textTexture, NULL, &DistR);
        SDL_RenderPresent(renderer);
    }
}

