#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/affichageMenu.h"
#include "../lib/sdl.h"
#include "../lib/menu.h"
#include "../lib/classement.h"
#include "../lib/gestionProfils.h"

/*FONCTION LANCEMENT MENU*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Cette fonction lance le menu et permet:
                                    - PLAY
                                        - FACILE
                                        - MOYEN
                                        - DIFFICILE
                                    - CHOIX PROFIL
                                        - CHOIX PROFIL
                                        - CREER PROFIL
                                    - CLASSEMENT
                                    - QUIT
*************************************************************************/
extern void Lancement_menu(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Color TextColor;
    TextColor.r = 255;
    TextColor.g = 255;
    TextColor.b = 255;
    //int choix = 0;
    int time;

    readProfiles();

    if(nbProfils == 0){
        creationProfil(window, renderer);
    }

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

    /*Importation des polices*/
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

    /*Creation du texte*/

    SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", TextColor);
    SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
    SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };

    SDL_Surface *TextPlay = TTF_RenderText_Solid(police, "Play", TextColor);
    if (TextPlay == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistR = {90, 300, TextPlay->w, TextPlay->h};

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


/*---------------------------------------------------------------------------------------------------------------------------------------*/
    SDL_Surface* ChooseProfile = TTF_RenderText_Solid(police, "Profils", TextColor);
    if (ChooseProfile == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistChooseProfile = {90, 350, ChooseProfile->w, ChooseProfile->h};

    SDL_Texture* textTextureChoose = SDL_CreateTextureFromSurface(renderer, ChooseProfile);

    SDL_FreeSurface(ChooseProfile);

    if (textTextureChoose == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

   SDL_Surface* Classement = TTF_RenderText_Solid(police, "Classement", TextColor);
    if (Classement == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistClassement = {90, 400, Classement->w, Classement->h};

    SDL_Texture *textTextureClassement = SDL_CreateTextureFromSurface(renderer, Classement);

    SDL_FreeSurface(Classement);

    if (textTextureClassement == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/

    SDL_Surface *Quit = TTF_RenderText_Solid(police, "Quit", TextColor);
    if (Quit == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistQuit = {90, 450, Quit->w, Quit->h};

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

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    // affichage des texte PLAY, CHOOSE PROFILE QUIT

    time = SDL_GetTicks();
    int VisiblePlay = 1;
    int VisibleChoose = 1;
    int VisibleClassement = 1;
    int VisibleQuit = 1;
    //choix = 0;
    int position = 0;

    while (program_launched)
    {
        SDL_Event event;
        

        SDL_Surface* textProfilCourant = TTF_RenderText_Blended(police, "Profil actuel : ", TextColor);
        SDL_Surface* textProfilCourantName = TTF_RenderText_Blended(police, nomProfils[profilCourant], TextColor);
        int textWidth = textProfilCourant->w + textProfilCourantName->w;
        SDL_Texture* textureProfilCourant = SDL_CreateTextureFromSurface(renderer, textProfilCourant);
        SDL_Rect rectProfilCourant = {(SCREEN_WIDTH / 2) - (textWidth / 2), 170, textProfilCourant->w, textProfilCourant->h };
        SDL_Rect rectProfilCourantName = {rectProfilCourant.x + textProfilCourant->w, 170, textProfilCourantName->w, textProfilCourantName->h }; 
        SDL_Texture* textureProfilCourantName = SDL_CreateTextureFromSurface(renderer, textProfilCourantName);

        
        if(nbProfils == 0){
            creationProfil(window, renderer);
        }

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

                case SDL_SCANCODE_RETURN:
                    if (position == 0) {
                        choice_difficult(window,renderer);
                        //CrashMessage(window,renderer);
                        // appeler la fonction de lancement de jeu
                    } else if (position == 1) {
                        choice_profile(window,renderer);
                        // imprimer un message à l'écran
                        //creationProfil(window, renderer);
                    }
                    else if (position == 2){
                        // imprimer un message à l'écran
                        afficherTableau(window, renderer);
                    }
                    else if (position == 3){
                        program_launched = SDL_FALSE;

                    }
                    break;


                // BAS
                case SDL_SCANCODE_DOWN:
                    position = position + 1;
                    if (position > 3){
                        position = 0;
                    }
                    printf("Vous avez appuye sur la touche BAS\n");

                    break;
                case SDL_SCANCODE_S:
                    position = position + 1;
                    if (position > 3){
                        position = 0;
                    }
                    printf("Vous avez appuye sur la touche BAS\n");
                    break;

                // HAUT
                case SDL_SCANCODE_Z:
                    position = position - 1;
                    if (position < 0){
                        position = 3;
                    }
                    printf("Vous avez appuye sur la touche HAUT\n%d\n", position);
                    break;

                case SDL_SCANCODE_UP:
                    position = position - 1;
                    if (position < 0){
                        position = 3;
                    }
                    printf("Vous avez appuye sur la touche HAUT\n%d\n", position);

                    break;

                default:
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


        if (position == 2)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleClassement = !VisibleClassement;
                int alpha = VisibleClassement ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureClassement, alpha);
            }
        }
        else
        {

            VisibleClassement = 1;
            int alpha = VisibleClassement ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureClassement, alpha);
        }




        if (position == 3)
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

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &DistQuit);
        SDL_RenderCopy(renderer, textTextureClassement, NULL, &DistClassement);
        SDL_RenderCopy(renderer, textTextureChoose, NULL, &DistChooseProfile);
        SDL_RenderCopy(renderer, textTexture, NULL, &DistR);
        SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);
        SDL_RenderCopy(renderer, textureProfilCourant, NULL, &rectProfilCourant);
        SDL_RenderCopy(renderer, textureProfilCourantName, NULL, &rectProfilCourantName);
        SDL_RenderPresent(renderer);
        
        SDL_DestroyTexture(textureProfilCourant);
        SDL_DestroyTexture(textureProfilCourantName);
        SDL_FreeSurface(textProfilCourant);
        SDL_FreeSurface(textProfilCourantName);
        textureProfilCourant = NULL;
        textProfilCourant = NULL;
        textureProfilCourantName = NULL;
        textProfilCourantName = NULL;
    }

    TTF_CloseFont(police);
    TTF_CloseFont(fontLogo);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(textTextureChoose);
    SDL_DestroyTexture(textTextureClassement);
    SDL_DestroyTexture(textTextureQuit);
    SDL_DestroyTexture(textureCarGame);

    SDL_FreeSurface(carGame);

    //Réinitialisation des pointeurs
    texture = NULL;
    textTexture = NULL;
    textTextureChoose = NULL;
    textTextureClassement = NULL;
    textTextureQuit = NULL;
    carGame = NULL;
    textureCarGame = NULL;
    police = NULL;
    fontLogo = NULL;
}
