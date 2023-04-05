/**
 * @file affichageMenu.c
 * @brief Fonctions d'affichage du menu
 * @authors Ayoub LAARIBI,Tom MARSURA, Thibaut GASNIER
 * @version 1.0
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/menu.h"
#include "../lib/sdl.h"
#include "../lib/game.h"
#include "../lib/gestionProfils.h"

extern void choice_difficult(SDL_Window* window, SDL_Renderer* renderer){
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
    
    /*Creation du texte*/

    SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", TextColor);
    SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
    SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };


    SDL_Surface *TextEasy = TTF_RenderText_Solid(police, "Easy", TextColor);
    if (TextEasy == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistEasy = {90, 300, TextEasy->w, TextEasy->h};

        SDL_Texture *textTextureEasy = SDL_CreateTextureFromSurface(renderer, TextEasy);

        SDL_FreeSurface(TextEasy);

        if (textTextureEasy == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }

/*.....................................................................................................................................*/



SDL_Surface *TextMedium = TTF_RenderText_Solid(police, "Medium", TextColor);
    if (TextMedium == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistMedium = {90, 350, TextMedium->w, TextMedium->h};

        SDL_Texture *textTextureMedium = SDL_CreateTextureFromSurface(renderer, TextMedium);

        SDL_FreeSurface(TextMedium);

        if (textTextureMedium == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }
/*-------------------------------------------------------------------------------------------------------------------------------------*/



SDL_Surface *TextHard = TTF_RenderText_Solid(police, "Hard", TextColor);
    if (TextHard == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistHard = {90, 400, TextHard->w, TextHard->h};

        SDL_Texture *textTextureHard = SDL_CreateTextureFromSurface(renderer, TextHard);

        SDL_FreeSurface(TextHard);

        if (textTextureHard == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }



/*------------------------------------------------------------------------------------------------------------------------------------*/



SDL_Surface *TextRetour = TTF_RenderText_Solid(police, "Retour", TextColor);
    if (TextRetour == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistRetour = {90, 450, TextRetour->w, TextRetour->h};

        SDL_Texture *textTextureRetour = SDL_CreateTextureFromSurface(renderer, TextRetour);

        SDL_FreeSurface(TextRetour);

        if (textTextureRetour == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }



/*------------------------------------------------------------------------------------------------------------------------------------*/

    time = SDL_GetTicks();
    int VisibleEasy = 1;
    int VisibleMedium = 1;
    int VisibleHard = 1;
    int VisibleRetour = 1;
    int position = 0;

    int quit = 0;

    while(!quit && program_launched){
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
                                    easyGame(window, renderer);
                                    quit = 1;
                                } else if (position == 1) {
                                    MediumGame(window, renderer);
                                    quit = 1;
                                }
                                else if (position == 2){
                                    HardGame(window, renderer);
                                    quit = 1;
                                }
                                else if (position == 3){
                                    quit = 1;
                                }
                            break;



                        case SDLK_DOWN:
                            position++;

                            if (position > 3){
                                position = 0;
                            }
                        break;

                        case SDLK_UP:
                            position--;

                            if (position < 0){
                                position = 3;
                            }

                        break;
                    }


            }
        }

        if (position == 0)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleEasy = !VisibleEasy;
                int alpha = VisibleEasy ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureEasy, alpha);
            }
        }
        else
        {

            VisibleEasy = 1;
            int alpha = VisibleEasy ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureEasy, alpha);
        }

        if( position == 1)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleMedium = !VisibleMedium;
                int alpha = VisibleMedium ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureMedium, alpha);
            }
        }
        else
        {

            VisibleMedium = 1;
            int alpha = VisibleMedium ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureMedium, alpha);
        }

        if( position == 2)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleHard = !VisibleHard;
                int alpha = VisibleHard ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureHard, alpha);
            }
        }
        else
        {

            VisibleHard = 1;
            int alpha = VisibleHard ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureHard, alpha);
        }

        if (position == 3)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleRetour = !VisibleRetour;
                int alpha = VisibleRetour ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureRetour, alpha);
            }
        }
        else
        {

            VisibleRetour = 1;
            int alpha = VisibleRetour ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureRetour, alpha);
        }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderCopy(renderer, textTextureRetour, NULL, &DistRetour);
    SDL_RenderCopy(renderer, textTextureHard, NULL, &DistHard);
    SDL_RenderCopy(renderer, textTextureMedium, NULL, &DistMedium);
    SDL_RenderCopy(renderer, textTextureEasy, NULL, &DistEasy);
    SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);

    SDL_RenderPresent(renderer);
    }


    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textTextureEasy);
    SDL_DestroyTexture(textTextureMedium);
    SDL_DestroyTexture(textTextureHard);
    SDL_DestroyTexture(textTextureRetour);
    SDL_DestroyTexture(textureCarGame);
    
    SDL_FreeSurface(carGame);

    TTF_CloseFont(police);
    TTF_CloseFont(fontLogo);

    //Réinitialisation des pointeurs
    texture = NULL;
    textTextureEasy = NULL;
    textTextureMedium = NULL;
    textTextureHard = NULL;
    textTextureRetour = NULL;
    textureCarGame = NULL;
    TextEasy = NULL;
    TextMedium = NULL;
    TextHard = NULL;
    TextRetour = NULL;
    carGame = NULL;
    police = NULL;
    fontLogo = NULL;
}

/**
 * @brief Cette Fonction permet de creer,choisir ou supprimer un profil
 * @author Ayoub LAARIBI
 * @return void
*/
extern void choice_profile(SDL_Window* window, SDL_Renderer* renderer){
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

    SDL_Surface *TextCree = TTF_RenderText_Solid(police, "Cree", TextColor);
    if (TextCree == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    /*Creation du texte*/

    SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", TextColor);
    SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
    SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };

    SDL_Rect DistCree = {90, 300, TextCree->w, TextCree->h};

    SDL_Texture *textTextureCree = SDL_CreateTextureFromSurface(renderer, TextCree);

    SDL_FreeSurface(TextCree);

    if (textTextureCree == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }

/*.....................................................................................................................................*/



SDL_Surface *TextChoisir = TTF_RenderText_Solid(police, "Choisir", TextColor);
    if (TextChoisir == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistChoisir = {90, 350, TextChoisir->w, TextChoisir->h};

        SDL_Texture *textTextureChoisir = SDL_CreateTextureFromSurface(renderer, TextChoisir);

        SDL_FreeSurface(TextChoisir);

        if (textTextureChoisir == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }
/*-------------------------------------------------------------------------------------------------------------------------------------*/



SDL_Surface *TextSupr = TTF_RenderText_Solid(police, "Supprimer", TextColor);
    if (TextSupr == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistSupr = {90, 400, TextSupr->w, TextSupr->h};

        SDL_Texture *textTextureSupr = SDL_CreateTextureFromSurface(renderer, TextSupr);

        SDL_FreeSurface(TextSupr);

        if (textTextureSupr == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }



/*------------------------------------------------------------------------------------------------------------------------------------*/

    SDL_Surface *TextRetour = TTF_RenderText_Solid(police, "Retour", TextColor);
    if (TextRetour == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistRetour = {90, 450, TextRetour->w, TextRetour->h};

        SDL_Texture *textTextureRetour = SDL_CreateTextureFromSurface(renderer, TextRetour);

        SDL_FreeSurface(TextRetour);

        if (textTextureRetour == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }


/*------------------------------------------------------------------------------------------------------------------------------------*/


    time = SDL_GetTicks();
    int VisibleCree = 1;
    int VisibleChoisir = 1;
    int VisibleSupr = 1;
    int VisibleRetour = 1;
    int position = 0;

    int quit = 0;

    while(!quit && program_launched){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){

                        case SDLK_RETURN:
                            if (position == 0) {
                                creationProfil(window, renderer);
                                quit = 1;
                            } else if (position == 1) {
                                choixProfil(window, renderer);
                                quit = 1;
                            }
                            else if (position == 2){
                                supprimeProfil(window, renderer);
                                quit = 1;
                            }
                            else {
                                quit = 1;
                            }
                        break;

                        case SDLK_DOWN:
                            position++;

                            if (position > 4){
                                position = 0;
                            }
                            printf("Vous avez appuye sur la touche right\n%d\n", position);
                        break;

                        case SDLK_UP:
                            position--;

                            if (position < 0){
                                position = 3;
                            }
                            printf("Vous avez appuye sur la touche left\n%d\n", position);

                        break;
                    }


            }
        }

        if (position == 0)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleCree = !VisibleCree;
                int alpha = VisibleCree ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureCree, alpha);
            }
        }
        else
        {

            VisibleCree = 1;
            int alpha = VisibleCree ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureCree, alpha);
        }

        if( position == 1)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleChoisir = !VisibleChoisir;
                int alpha = VisibleChoisir ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureChoisir, alpha);
            }
        }
        else
        {

            VisibleChoisir = 1;
            int alpha = VisibleChoisir ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureChoisir, alpha);
        }

        if( position == 2)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleSupr = !VisibleSupr;
                int alpha = VisibleSupr ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureSupr, alpha);
            }
        }
        else
        {

            VisibleSupr = 1;
            int alpha = VisibleSupr ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureSupr, alpha);
        }


        if( position == 3)
        {

            unsigned ActualTime = SDL_GetTicks();

            if (ActualTime > time + 500)
            {
                time = ActualTime;
                VisibleRetour = !VisibleRetour;
                int alpha = VisibleRetour ? 255 : 0;
                SDL_SetTextureAlphaMod(textTextureRetour, alpha);
            }
        }
        else
        {

            VisibleRetour = 1;
            int alpha = VisibleRetour ? 255 : 0;
            SDL_SetTextureAlphaMod(textTextureRetour, alpha);
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, textTextureRetour, NULL, &DistRetour);
        SDL_RenderCopy(renderer, textTextureSupr, NULL, &DistSupr);
        SDL_RenderCopy(renderer, textTextureChoisir, NULL, &DistChoisir);
        SDL_RenderCopy(renderer, textTextureCree, NULL, &DistCree);
        SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);

        SDL_RenderPresent(renderer);
    }

    /*Destruction*/

    SDL_DestroyTexture(textTextureRetour);
    SDL_DestroyTexture(textTextureSupr);
    SDL_DestroyTexture(textTextureChoisir);
    SDL_DestroyTexture(textTextureCree);
    SDL_DestroyTexture(textureCarGame);
    SDL_DestroyTexture(texture);
    
    SDL_FreeSurface(carGame);

    TTF_CloseFont(police);
    TTF_CloseFont(fontLogo);

    //Réinitialisation des pointeurs
    textTextureRetour = NULL;
    textTextureSupr = NULL;
    textTextureChoisir = NULL;
    textTextureCree = NULL;
    textureCarGame = NULL;
    texture = NULL;
    carGame = NULL;
    ImageStart = NULL;
    TextRetour = NULL;
    TextSupr = NULL;
    TextChoisir = NULL;
    TextCree = NULL;
    police = NULL;
    fontLogo = NULL;
}



/**
 * @brief Cette fonction permet de afficher un message lorsque le joueur perd
 * @author Ayoub Laaribi
 * @return void
*/
void CrashMessage(SDL_Window* window, SDL_Renderer* renderer, int score, int mode){
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

        SDL_Rect DistScore = {100, 200, Score->w, Score->h};

        SDL_Texture *textTextureScore = SDL_CreateTextureFromSurface(renderer, Score);


        if (textTextureScore == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }
/*****************************************************************************************************************/


SDL_Surface *nbPartie = TTF_RenderText_Solid(policeChoix, "Parties joue :", TextColor);
    if (Score == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

        SDL_Rect DistSPartie = {100, 250, nbPartie->w, nbPartie->h};

        SDL_Texture *textTexturePartieJ = SDL_CreateTextureFromSurface(renderer, nbPartie);


        if (textTexturePartieJ == NULL)
        {
            TTF_CloseFont(police);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithMessage("Impossible de charger la texture du texte");
        }




/*****************************************************************************************************************/
        char point[MAX_PROFILS][SIZE_NAME];
        pointsProfils[profilCourant] = pointsProfils[profilCourant] + score;
        sprintf(point[0],"%d",score);
        
         SDL_Surface* points = TTF_RenderText_Blended(policeChoix, point[0], TextColor);
         if (points == NULL)
            {
                printf("Erreur de création de la surface : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        
        SDL_Rect DistPts = {300,200,points->w,points->h};

         SDL_Texture* texturePts = SDL_CreateTextureFromSurface(renderer, points);
            if (!texturePts)
            {
                printf("Erreur de création de la texture : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }






/*****************************************************************************************************************/
        char partie[MAX_PROFILS][SIZE_NAME];
        nbPartiesProfils[profilCourant] = nbPartiesProfils[profilCourant] +1;
        sprintf(partie[0],"%d",nbPartiesProfils[profilCourant]);
        
         SDL_Surface* parties = TTF_RenderText_Blended(policeChoix, partie[0], TextColor);
         if (parties == NULL)
            {
                printf("Erreur de création de la surface : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        
        SDL_Rect DistParties = {500,250,parties->w,parties->h};

         SDL_Texture* textureParties = SDL_CreateTextureFromSurface(renderer, parties);
            if (!textureParties)
            {
                printf("Erreur de création de la texture : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }

/*****************************************************************************************************************/
   
        int time = SDL_GetTicks();
        int position = 0;
        int VisibleRejouer = 1;
        int VisibleQuit = 1;

        int quit = 0;

        while(!quit){
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
                                if(position == 0){
                                    /*quitter*/
                                    if(mode == 0){
                                        easyGame(window, renderer);
                                        quit = 1;
                                    }
                                    else if(mode == 1){
                                        MediumGame(window, renderer);
                                        quit = 1;
                                    }
                                    else if(mode == 2){
                                        HardGame(window, renderer);
                                        quit = 1;
                                    }
                                }else if( position == 1){
                                    quit = 1;
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


        saveGame();

        SDL_RenderCopy(renderer,texture,NULL,NULL);
        SDL_RenderCopy(renderer,textureParties, NULL, &DistParties);//nb partie
        SDL_RenderCopy(renderer, textTexturePartieJ, NULL, &DistSPartie);//Partie jouee
        SDL_RenderCopy(renderer, texturePts, NULL, &DistPts);//pts
        SDL_RenderCopy(renderer, textTextureScore, NULL, &DistScore);//text score
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &DistQuit);//quit
        SDL_RenderCopy(renderer, textTextureRejouer, NULL, &DistRejouer);//rejouer
        SDL_RenderCopy(renderer, textTextureMessage, NULL, &DistMessage);//Game over
        SDL_RenderPresent(renderer);
        }




    /*Liberation des texture*/
        SDL_FreeSurface(nbPartie);
        SDL_FreeSurface(Quit);
        SDL_FreeSurface(ImageStart); /*liberation de la memoire*/
        SDL_FreeSurface(Rejouer);
        SDL_FreeSurface(Score);
        SDL_FreeSurface(points);
        SDL_FreeSurface(parties);




        SDL_DestroyTexture(textTexturePartieJ);
        SDL_DestroyTexture(texturePts);
        SDL_DestroyTexture(textTextureScore);
        SDL_DestroyTexture(textTextureQuit);
        SDL_DestroyTexture(textTextureRejouer);
        SDL_DestroyTexture(textTextureMessage);

        // Libérer la police
        TTF_CloseFont(police);
        TTF_CloseFont(policeChoix);


        police=NULL;
        policeChoix = NULL;
        textTexturePartieJ = NULL;
        texturePts = NULL;
        textTextureScore = NULL;
        textTextureQuit = NULL;
        textTextureRejouer = NULL;
        textTextureMessage = NULL;
        nbPartie =NULL;
        Quit = NULL;
        ImageStart=NULL;; /*liberation de la memoire*/
        Rejouer=NULL;
        Score=NULL;
        points=NULL;
        parties=NULL;

}