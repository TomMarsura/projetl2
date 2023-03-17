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

/*FONCTION CREATION DE PROFIL*/
int creationProfil(SDL_Window* window, SDL_Renderer* renderer){
    //Effacer l'écran
    SDL_RenderClear(renderer);

    // Afficher la texture de fond

    SDL_Surface *text_surface = NULL;
    SDL_Texture *text_texture = NULL;
    TTF_Font *font = NULL;
    SDL_Rect text_rect = {0};
    SDL_Event event;
    int quit = 0;
    char text_input[SIZE_NAME] = {0};
    int text_input_length = 0;

    // Initialisation de la SDL_ttf
    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        return 1;
    }

    // Chargement de la police de caractères
    font = TTF_OpenFont("../fonts/police.TTF", 28);
    if (font == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return 1;
    }

    // Boucle principale
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_TEXTINPUT) {
                if (text_input_length < SIZE_NAME) {
                    text_input[text_input_length] = event.text.text[0];
                    text_input_length++;
                    text_input[text_input_length] = '\0';

                    int font_size = 20;
                    font = TTF_OpenFont("../fonts/police.TTF", font_size);

                    // Création de la texture du texte
                    SDL_Color white = {255, 255, 255, 255};
                    //Création d'un rectangle pour le texte de taille 640x480
                    text_rect.w = 200;
                    text_rect.h = 100;
                    text_surface = TTF_RenderUTF8_Blended_Wrapped(font, text_input, white, text_rect.w);
                    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && text_input_length > 0) {
                    text_input_length--;
                    text_input[text_input_length] = '\0';

                    int font_size = 20;
                    font = TTF_OpenFont("../fonts/police.TTF", font_size);

                    // Création de la texture du texte
                    SDL_Color white = {255, 255, 255, 255};
                    //Création d'un rectangle pour le texte
                    text_rect.w = 200;
                    text_rect.h = 100;  
                    text_surface = TTF_RenderUTF8_Blended_Wrapped(font, text_input, white, text_rect.w);
                    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    createProfile(text_input);
                    quit = 1;
                }
            }
        }
        // Effacement de l'écran
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);

        // Affichage du texte
        if (text_texture != NULL) {
            SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
            text_rect.x = (640 - text_rect.w) / 2;
            text_rect.y = (480 - text_rect.h) / 2;
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        }

        // Rafraîchissement de l'écran
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return 0;
}


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

void afficherTableau(SDL_Window* window, SDL_Renderer* renderer)
{
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
    SDL_Surface* ChooseProfile = TTF_RenderText_Solid(police, "Choose Profile", TextColor);
    if (ChooseProfile == NULL)
    {
        TTF_CloseFont(police);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithMessage("Le texte sur la surface a echouee");
    }

    SDL_Rect DistChooseProfile = {90, 150, ChooseProfile->w, ChooseProfile->h};

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

                case SDL_SCANCODE_RETURN:
                    if (position == 0) {
                        // appeler la fonction de lancement de jeu
                        printf("Lancement du jeu...\n");
                    } else if (position == 1) {
                        // imprimer un message à l'écran
                        creationProfil(window, renderer);
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

