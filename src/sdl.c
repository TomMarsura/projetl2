#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../lib/sdl.h"
#include "../lib/menu.h"


SDL_bool program_launched = SDL_TRUE ;


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

/**
 * @brief Cette fonction permet de afficher un message lorsque le joueur perd
 * @author Ayoub Laaribi
 * @return void
*/
void CrashMessage(SDL_Window* window, SDL_Renderer* renderer,int profile){
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
    TTF_Font *police = TTF_OpenFont("../fonts/police.TTF", 55);
    if (police == NULL)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Importation de la police a echouee");
    }


    TTF_Font *policeChoix = TTF_OpenFont("../fonts/police.TTF", 35);
    if (policeChoix == NULL)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Importation de la police a echouee");
    }

    /*Initialisation d'un rectangle*/
    SDL_Rect rectangle = {100, 100, 50, 50};

/*****************************************************************************************************************/
    /*Message*/
    SDL_Surface *Message_crash = TTF_RenderText_Solid(police, "Game Over", TextColor);
    if (Message_crash == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistMessage = {190, 30, Message_crash->w, Message_crash->h};

        SDL_Texture *textTextureMessage = SDL_CreateTextureFromSurface(renderer, Message_crash);

        SDL_FreeSurface(Message_crash);

        if (textTextureMessage == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }
/*****************************************************************************************************************/
SDL_Surface *Rejouer = TTF_RenderText_Solid(policeChoix, "Rejouer", TextColor);
    if (Rejouer == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistRejouer = {70, 470, Rejouer->w, Rejouer->h};

        SDL_Texture *textTextureRejouer = SDL_CreateTextureFromSurface(renderer, Rejouer);

        SDL_FreeSurface(Rejouer);

        if (textTextureRejouer == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }



/*****************************************************************************************************************/
SDL_Surface *Quit = TTF_RenderText_Solid(policeChoix, "Quitter", TextColor);
    if (Quit == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistQuit = {510, 470, Quit->w, Quit->h};

        SDL_Texture *textTextureQuit = SDL_CreateTextureFromSurface(renderer, Quit);

        SDL_FreeSurface(Quit);

        if (textTextureQuit == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }

/*****************************************************************************************************************/


SDL_Surface *Score = TTF_RenderText_Solid(policeChoix, "Score :", TextColor);
    if (Score == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistScore = {510, 470, Score->w, Score->h};

        SDL_Texture *textTextureScore = SDL_CreateTextureFromSurface(renderer, Score);

        SDL_FreeSurface(Score);

        if (textTextureScore == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }

/*****************************************************************************************************************/

//SDL_Surface* points = TTF_RenderText_Blended(policeChoix, pointsTab[profile], TextColor);

/*****************************************************************************************************************/
        int time = SDL_GetTicks();
        int position = 0;
        int VisibleRejouer = 1;
        int VisibleQuit = 1;

        while(program_launched){
            SDL_Event event;

            while(SDL_PollEvent(&event)){
                switch(event.type){

                    case SDL_QUIT:
                        program_launched = SDL_FALSE;
                    break;


                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                program_launched = SDL_FALSE;
                            break;

                            case SDLK_RETURN:
                                if(position == 0){
                                    /*quitter*/
                                    printf("REJOUER\n");
                                }else if( position == 1){
                                    printf("QUITTER\n");
                                }
                            break;

                            case SDLK_RIGHT:
                                position++;

                                if(position > 1){
                                    position = 0;
                                }
                            break;
                            case SDLK_LEFT:
                                position--;

                                if(position < 0){
                                    position = 1;
                                }
                            break;
                        }

                }
            }

            if ( position == 0)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleRejouer = !VisibleRejouer;
                int alpha = VisibleRejouer ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureRejouer, alpha);
            }
        }
        else
        {

            VisibleRejouer = 1;
            int alpha = VisibleRejouer ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureRejouer, alpha);
        }




        if ( position == 1)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleQuit = !VisibleQuit;
                int alpha = VisibleQuit ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureQuit, alpha);
            }
        }
        else
        {

            VisibleQuit = 1;
            int alpha = VisibleQuit ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureQuit, alpha);
        }




        SDL_RenderCopy(renderer,texture,NULL,NULL);
        SDL_RenderCopy(renderer, textTextureScore, NULL, &DistScore);
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &DistQuit);
        SDL_RenderCopy(renderer, textTextureRejouer, NULL, &DistRejouer);
        SDL_RenderCopy(renderer, textTextureMessage, NULL, &DistMessage);
        SDL_RenderPresent(renderer);
        }




    /*Liberation des texture*/
        SDL_DestroyTexture(textTextureScore);
        SDL_DestroyTexture(textTextureQuit);
        SDL_DestroyTexture(textTextureRejouer);
        SDL_DestroyTexture(textTextureMessage);

        // Libérer la police
        TTF_CloseFont(police);
        TTF_CloseFont(policeChoix);

}

