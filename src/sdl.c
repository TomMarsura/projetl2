#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../lib/sdl.h"
#include "../lib/menu.h"

#define PROFILS 10


SDL_bool program_launched = SDL_TRUE ;

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


/**
 * @brief Cette Fonction permet de creer,choisir ou supprimer un profil
 * @author Ayoub LAARIBI
 * @return void
*/
void choice_profile(SDL_Window* window, SDL_Renderer* renderer){
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


    SDL_Surface *TextCree = TTF_RenderText_Solid(police, "Cree", TextColor);
    if (TextCree == NULL)
    {
        TTF_CloseFont(police);
        // SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

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
                                if (position == 0) {
                                    // appeler la fonction easy
                                    printf("EASY MODE\n");
                                } else if (position == 1) {
                                    // imprimer un message à l'écran
                                    printf("MEDIUM MODE\n");
                                }
                                else if (position == 2){
                                    // imprimer un message à l'écran
                                    printf("HARD MODE\n");
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

    SDL_RenderPresent(renderer);
    }

    /*Destruction*/

    SDL_DestroyTexture(textTextureRetour);
    SDL_DestroyTexture(textTextureSupr);
    SDL_DestroyTexture(textTextureChoisir);
    SDL_DestroyTexture(textTextureCree);

    TTF_CloseFont(police);
}


/**
 * @brief Cette fonction permet a l'utilisateur de choisir sa diffculter
 * @author Ayoub Laaribi
 * @return void
*/
void choice_difficult(SDL_Window* window, SDL_Renderer* renderer){
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
                                if (position == 0) {
                                    // appeler la fonction easy
                                    printf("EASY MODE\n");
                                } else if (position == 1) {
                                    // imprimer un message à l'écran
                                    printf("AVERAGE MODE\n");
                                }
                                else if (position == 2){
                                    // imprimer un message à l'écran
                                    printf("HARD MODE\n");
                                }
                               
                            break;



                        case SDLK_DOWN:
                            position++;
                            
                            if (position > 3){
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

    SDL_RenderPresent(renderer);
    }
}












/**
 * @author Tom Marsura
 * @brief Cette fonction permet a l'utilisateur de creer un profil
 * @return int
*/

/*FONCTION CREATION DE PROFIL*/
int creationProfil(SDL_Window* window, SDL_Renderer* renderer){
    //Effacer l'écran
    SDL_RenderClear(renderer);

    SDL_Surface *text_surface = NULL;
    SDL_Texture *text_texture = NULL;
    TTF_Font *font = NULL;
    TTF_Font *fontLogo = NULL;
    TTF_Font *fontFooter = NULL;
    SDL_Rect text_rect = {0};
    SDL_Event event;
    int quit = 0;
    char text_input[SIZE_NAME] = {0};
    int text_input_length = 0;
    int font_size = 30;
    bool_t nomExist = FAUX;
    SDL_Texture* textureErreurActuelle = NULL; // Initialiser la texture d'erreur actuelle à NULL

    // Initialisation de la SDL_ttf
    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        return 1;
    }


    // Chargement de la police de caractères
    font = TTF_OpenFont("../fonts/police.TTF", font_size);

    if (font == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return 1;
    }

    fontLogo = TTF_OpenFont("../fonts/police.TTF", font_size + 20);

    if (font == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return 1;
    }

    fontFooter = TTF_OpenFont("../fonts/police.TTF", font_size - 20);

    if (font == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return 1;
    }

    // Création de la texture du texte
    SDL_Color white = {255, 255, 255, 255};

    // Création des textes d'erreur
    SDL_Surface* erreurNomExist = TTF_RenderText_Blended(font, "Pseudo deja existant", white);
    SDL_Surface* erreurNomVide = TTF_RenderText_Blended(font, "Veuillez saisir un nom", white);

    // Créer une texture à partir de la surface
    SDL_Texture* textureErreurNomExist = SDL_CreateTextureFromSurface(renderer, erreurNomExist);
    SDL_Texture* textureErreurNomVide = SDL_CreateTextureFromSurface(renderer, erreurNomVide);

    // Boucle principale
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_TEXTINPUT) {
                if (text_input_length < SIZE_NAME - 1) {
                    text_input[text_input_length] = event.text.text[0];
                    text_input_length++;
                    text_input[text_input_length] = '\0';

                    //Création d'un rectangle pour le texte de taille 640x480
                    text_rect.w = 300;
                    text_rect.h = 100;
                    text_surface = TTF_RenderUTF8_Blended_Wrapped(font, text_input, white, text_rect.w);
                    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && text_input_length > 0) {
                    text_input_length--;
                    text_input[text_input_length] = '\0';

                    //Création d'un rectangle pour le texte
                    text_rect.w = 300;
                    text_rect.h = 100;  
                    text_surface = TTF_RenderUTF8_Blended_Wrapped(font, text_input, white, text_rect.w);
                    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    //Verification si le nom existe déjà
                    for (int i = 0; i < nbProfils; i++){
                        if (strcmp(text_input, nomProfils[i]) == 0){
                            nomExist = VRAI;
                        }
                    }

                    printf("\n%d\n", text_input_length);
                    // Afficher l'erreur de nom vide si nécessaire
                    if (text_input_length == 0 && nomExist == FAUX) {
                        textureErreurActuelle = textureErreurNomVide;
                    }

                    // Si le nom est valide, créer le profil et quitter
                    else if (text_input_length > 0 && nomExist == FAUX) {
                        createProfile(text_input);
                        quit = 1;
                    }

                    // Afficher l'erreur de nom existant si nécessaire
                    if (nomExist == VRAI) {
                        textureErreurActuelle = textureErreurNomExist;
                        nomExist = FAUX;
                    }

                    
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }
        // Effacement de l'écran
        SDL_RenderClear(renderer);

        // Dessine le fond gris
        SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
        SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRect(renderer, &background);

        // Création du rectangle autour du texte
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect text_back = {(SCREEN_WIDTH - 350) / 2, (SCREEN_HEIGHT - 15) / 2, 350, 50};
        SDL_RenderDrawRect(renderer, &text_back);

        //Affichage textes
        SDL_Surface* createProfil = TTF_RenderText_Blended(font, "Ecrivez votre pseudo", white);
        SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", white);
        SDL_Surface* escape = TTF_RenderText_Blended(fontFooter, "Touche echap pour revenir au menu principal", white);

        // Créer une texture à partir de la surface
        SDL_Texture* textureCreateProfil = SDL_CreateTextureFromSurface(renderer, createProfil);
        SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
        SDL_Texture* textureEscape = SDL_CreateTextureFromSurface(renderer, escape);
        
        // Créer un rectangle pour la texture
        SDL_Rect rectCreateProfil = {(SCREEN_WIDTH - createProfil->w) / 2, SCREEN_HEIGHT / 2 - 100, createProfil->w, createProfil->h };
        SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };
        SDL_Rect rectEscape = {(SCREEN_WIDTH - escape->w) / 2, SCREEN_HEIGHT - 50, escape->w, escape->h};

        // Afficher la texture
        SDL_RenderCopy(renderer, textureCreateProfil, NULL, &rectCreateProfil);
        SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);
        SDL_RenderCopy(renderer, textureEscape, NULL, &rectEscape);

        // Si une erreur est en cours d'affichage, afficher la texture correspondante
        if (textureErreurActuelle != NULL) {
            SDL_Rect rectErreur = {(SCREEN_WIDTH - erreurNomVide->w) / 2, SCREEN_HEIGHT - 200, erreurNomVide->w, erreurNomVide->h };
            SDL_RenderCopy(renderer, textureErreurActuelle, NULL, &rectErreur);
        }

        // Affichage du texte
        if (text_texture != NULL) {
            SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
            text_rect.x = (SCREEN_WIDTH - text_rect.w) / 2;
            text_rect.y = (SCREEN_HEIGHT) / 2;
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        }

        // Rafraîchissement de l'écran
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(textureCreateProfil);
        SDL_DestroyTexture(textureCarGame);
        SDL_DestroyTexture(textureEscape);
        SDL_FreeSurface(escape);
        SDL_FreeSurface(carGame);
        SDL_FreeSurface(createProfil);
    }

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    TTF_CloseFont(fontLogo);

    //Destruction messages d'erreur
    SDL_DestroyTexture(textureErreurActuelle);
    SDL_DestroyTexture(textureErreurNomExist);
    SDL_DestroyTexture(textureErreurNomVide);

    SDL_FreeSurface(erreurNomExist);
    SDL_FreeSurface(erreurNomVide);
    return 0;
}

/**
 * @author Tom Marsura
 * @return void
*/
void attenteClassement(){
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        quit = 1;
                    }
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
        }

        SDL_Delay(10);    
    }
}

/*FONCTION AFFICHAGE CLASSEMENT*/
/**
 * @author Tom Marsura
 * @return void
*/
void afficherTableau(SDL_Window* window, SDL_Renderer* renderer)
{
    // *--------------------------------------* INITIALISATION *--------------------------------------*
    // Effacer l'écran
    SDL_RenderClear(renderer);

    // Charger l'image de fond
    SDL_Surface* surfaceFond = IMG_Load("../img/background.jpg");
    if (!surfaceFond)
    {
        printf("Erreur de chargement de l'image de fond : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Créer une texture à partir de l'image de fond
    SDL_Texture* textureFond = SDL_CreateTextureFromSurface(renderer, surfaceFond);
    if (!textureFond)
    {
        printf("Erreur de création de la texture de fond : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Afficher la texture de fond
    SDL_RenderCopy(renderer, textureFond, NULL, NULL);


    // Charger la police d'écriture
    TTF_Font* police = TTF_OpenFont("../fonts/police.TTF", 20);
    if (!police)
    {
        printf("Erreur de chargement de la police d'écriture : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Couleur du texte
    SDL_Color couleur = {255, 255, 255 };

    //Réalisation du classement
    classement();

    char pointsTab[MAX_PROFILS][SIZE_NAME];
    char iTab[MAX_PROFILS][SIZE_NAME];
    char partiesTab[MAX_PROFILS][SIZE_NAME];

    for (int i = 0; i < nbProfils; i++){
        sprintf(pointsTab[i], "%d", pointsProfils[i]);
        sprintf(iTab[i], "%d", i+1);
        sprintf(partiesTab[i], "%d", nbPartiesProfils[i]);
    }

    // *---------------------------------* NOMS DE COLONNES *---------------------------------*

    //Affichage des noms de colonnes [Place, Nom, Points, Parties]
    SDL_Surface* placeColonne = TTF_RenderText_Blended(police, "Place", couleur);
    SDL_Surface* nameColonne = TTF_RenderText_Blended(police, "Nom", couleur);
    SDL_Surface* pointsColonne = TTF_RenderText_Blended(police, "Points", couleur);
    SDL_Surface* partiesColonne = TTF_RenderText_Blended(police, "Parties", couleur);

    // Créer une texture à partir de la surface
    SDL_Texture* texturePlaceColonne = SDL_CreateTextureFromSurface(renderer, placeColonne);
    SDL_Texture* textureNomColonne = SDL_CreateTextureFromSurface(renderer, nameColonne);
    SDL_Texture* texturePointsColonne = SDL_CreateTextureFromSurface(renderer, pointsColonne);
    SDL_Texture* texturePartiesColonne = SDL_CreateTextureFromSurface(renderer, partiesColonne);

    // Créer un rectangle pour la texture
    SDL_Rect rectPlaceColonne = { 0.65 * SCREEN_WIDTH / 4 - placeColonne->w, 20, placeColonne->w, placeColonne->h };
    SDL_Rect rectNomColonne = { 1.5 * SCREEN_WIDTH / 4 - nameColonne->w, 20, nameColonne->w, nameColonne->h };
    SDL_Rect rectPointsColonne = { 2.75 * SCREEN_WIDTH / 4 - pointsColonne->w, 20, pointsColonne->w, pointsColonne->h };
    SDL_Rect rectPartiesColonne = { 3.75 * SCREEN_WIDTH / 4 - partiesColonne->w, 20, partiesColonne->w, partiesColonne->h };

    // Afficher la texture
    SDL_RenderCopy(renderer, texturePlaceColonne, NULL, &rectPlaceColonne);
    SDL_RenderCopy(renderer, textureNomColonne, NULL, &rectNomColonne);
    SDL_RenderCopy(renderer, texturePointsColonne, NULL, &rectPointsColonne);
    SDL_RenderCopy(renderer, texturePartiesColonne, NULL, &rectPartiesColonne);

    // *---------------------------------* LIGNES DE SEPARATION *---------------------------------*
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Couleur des lignes de séparation
    //Posisions des lignes de séparation
    int x1 = 0.75 * SCREEN_WIDTH / 4;
    int x2 = 2 * SCREEN_WIDTH / 4;
    int x3 = 3 * SCREEN_WIDTH / 4;
    int x4 = 4 * SCREEN_WIDTH / 4;
    int y1 = 10;
    int y2 = 50 + 30 * nbProfils;
    int epaisseur = 5;

    //Création des lignes de séparation
    SDL_Rect line1 = { x1, y1, epaisseur, y2 - y1 };
    SDL_Rect line2 = { x2, y1, epaisseur, y2 - y1 };
    SDL_Rect line3 = { x3, y1, epaisseur, y2 - y1 };
    SDL_Rect line4 = { x4, y1, epaisseur, y2 - y1 };

    //Affichage des lignes de séparation
    SDL_RenderFillRect(renderer, &line1);
    SDL_RenderFillRect(renderer, &line2);
    SDL_RenderFillRect(renderer, &line3);
    SDL_RenderFillRect(renderer, &line4);


    // *---------------------------------* BOUCLE D'AFFICHAGE *---------------------------------*
    //Affichage des profils

    for (int i = 0; i < nbProfils; i++)
        {



            // Créer une surface à partir de la chaîne de caractères
            SDL_Surface* place = TTF_RenderText_Blended(police, iTab[i], couleur);
            SDL_Surface* name = TTF_RenderText_Blended(police, nomProfils[i], couleur);
            SDL_Surface* points = TTF_RenderText_Blended(police, pointsTab[i], couleur);
            SDL_Surface* parties = TTF_RenderText_Blended(police, partiesTab[i], couleur);
            if (!name)
            {
                printf("Erreur de création de la surface : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }

            // Créer une texture à partir de la surface
            SDL_Texture* texturePlace = SDL_CreateTextureFromSurface(renderer, place);
            SDL_Texture* textureName = SDL_CreateTextureFromSurface(renderer, name);
            SDL_Texture* texturePoints = SDL_CreateTextureFromSurface(renderer, points);
            SDL_Texture* textureParties = SDL_CreateTextureFromSurface(renderer, parties);
            if (!textureName)
            {
                printf("Erreur de création de la texture : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
            if (!texturePoints)
            {
                printf("Erreur de création de la texture : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
            
            SDL_Rect rectI = { 0.65 * SCREEN_WIDTH / 4 - place->w, 50 + i * 30, place->w, place->h };
            SDL_Rect rectName = {0.90 * SCREEN_WIDTH / 4, 50 + i * 30, name->w, name->h};
            SDL_Rect rectPoints = { 2.60 * SCREEN_WIDTH / 4 - points->w, 50 + i * 30, points->w, points->h };
            SDL_Rect rectParties = { 3.5 * SCREEN_WIDTH / 4 - parties->w, 50 + i * 30, parties->w, parties->h };

            // Afficher la texture
            SDL_RenderCopy(renderer, texturePlace, NULL, &rectI);
            SDL_RenderCopy(renderer, textureName, NULL, &rectName);
            SDL_RenderCopy(renderer, texturePoints, NULL, &rectPoints);
            SDL_RenderCopy(renderer, textureParties, NULL, &rectParties);

            // Libérer la surface et la texture
            SDL_FreeSurface(place);
            SDL_FreeSurface(name);
            SDL_FreeSurface(points);
            SDL_FreeSurface(parties);
            SDL_DestroyTexture(texturePlace);
            SDL_DestroyTexture(textureName);
            SDL_DestroyTexture(texturePoints);
            SDL_DestroyTexture(textureParties);
        }

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);

        // Libération des surfaces
        SDL_FreeSurface(surfaceFond);
        SDL_FreeSurface(placeColonne);
        SDL_FreeSurface(nameColonne);
        SDL_FreeSurface(pointsColonne);
        SDL_FreeSurface(partiesColonne);

        //Destruction des textures
        SDL_DestroyTexture(textureFond);
        SDL_DestroyTexture(texturePlaceColonne);
        SDL_DestroyTexture(textureNomColonne);
        SDL_DestroyTexture(texturePointsColonne);
        SDL_DestroyTexture(texturePartiesColonne);

        // Libérer la police
        TTF_CloseFont(police);

        attenteClassement();
}






/*gcc -o sdl sdl.c -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf*/



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

    SDL_Surface *TextPlay = TTF_RenderText_Solid(police, "PLAY", TextColor);
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
    SDL_Surface* ChooseProfile = TTF_RenderText_Solid(police, "Choose Profile", TextColor);
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
                    printf("Vous avez appuye sur la touche BAS\n%d\n", position);

                    break;
                case SDL_SCANCODE_S:
                    position = position + 1;
                    if (position > 3){
                        position = 0;
                    }
                    printf("Vous avez appuye sur la touche BAS\n%d\n", position);
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
        SDL_RenderPresent(renderer);
    }
}


