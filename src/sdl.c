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

/*FONCTION AFFICHAGE CLASSEMENT*/
/**/

void tabToString (){
    
}

void attente(){SDL_Event event;
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

extern
void afficherTableau(SDL_Window* window, SDL_Renderer* renderer)
{
    // Effacer l'écran
    SDL_RenderClear(renderer);

    // Charger l'image de fond
    SDL_Surface* surfaceFond = IMG_Load("../img/voiture.gif");
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
    TTF_Font* police = TTF_OpenFont("../img/police.TTF", 20);
    if (!police)
    {
        printf("Erreur de chargement de la police d'écriture : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Couleur du texte
    SDL_Color couleur = {65, 255, 50 };
    
    readProfiles();
    classement();

    char pointsTab[MAX_PROFILS][SIZE_NAME];
    char iTab[MAX_PROFILS][SIZE_NAME];
    char partiesTab[MAX_PROFILS][SIZE_NAME];

    for (int i = 0; i < nbProfils; i++){
        sprintf(pointsTab[i], "%d", pointsProfils[i]);
        sprintf(iTab[i], "%d", i);
        sprintf(partiesTab[i], "%d", nbPartiesProfils[i]);
    }

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
            
            SDL_Rect rectI = { 0.5 * SCREEN_WIDTH / 4 - place->w, 50 + i * 30, place->w, place->h };
            SDL_Rect rectName = {2 * SCREEN_WIDTH / 4 - name->w, 50 + i * 30, name->w, name->h };
            SDL_Rect rectPoints = { 2.5 * SCREEN_WIDTH / 4 - points->w, 50 + i * 30, points->w, points->h };
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

        // Libérer la surface et la texture de fond
        SDL_FreeSurface(surfaceFond);
        SDL_DestroyTexture(textureFond);
        // Libérer la police
        TTF_CloseFont(police);

        attente();
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


/*---------------------------------------------------------------------------------------------------------------------------------------*/
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

    if (textTextureChoose == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Impossible de charger la texture du texte");
    }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

   SDL_Surface *Classement = TTF_RenderText_Solid(police, "Classement", TextColor);
    if (Classement == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistClassement = {90, 200, Classement->w, Classement->h};

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

    SDL_Rect DistQuit = {90, 250, Quit->w, Quit->h};

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

                case SDL_SCANCODE_KP_ENTER:
                    if (position == 0) {
                        // appeler la fonction de lancement de jeu
                        printf("Lancement du jeu...\n");
                    } else if (position == 1) {
                        // imprimer un message à l'écran
                        printf("Choix de profil...\n");
                    }
                    else if (position == 2){
                        // imprimer un message à l'écran
                        tabToString();
                        afficherTableau(window, renderer);
                    }
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

