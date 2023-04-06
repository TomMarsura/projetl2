/**
 * @file gestionProfils.c
 * @brief Affichage des menu de gestion de profils
 * @authors Ayoub LAARIBI,Tom MARSURA,Thibaut GASNIER
 * @version 1.0
*/

#include <stdio.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_ttf.h"

#include "../lib/menu.h"
#include "../lib/sdl.h"

/**
 * @brief Fonction choixProfil : Fonction qui permet l'affichage du choix de profil
 * @param window : fenêtre SDL
 * @param renderer : rendu SDL
 * @return int : 0 si tout s'est bien passé, 1 s'il y a une erreur (chargement de SDL)
*/
extern int choixProfil(SDL_Window* window, SDL_Renderer* renderer){
    //Effacer l'écran
    SDL_RenderClear(renderer);
 
    /* -------------------------------------------------------------------------------- */
    /* ------------------------- Initialisation des variables ------------------------- */
    /* -------------------------------------------------------------------------------- */

    int position = 0;
    TTF_Font *font = NULL;
    TTF_Font *fontLogo = NULL;
    TTF_Font *fontFooter = NULL;
    SDL_Event event;
    int quit = 0;
    int font_size = 30;

    /* ---------------------------------------------------------------------------- */
    /* ------------------------- Initialisation de la SDL ------------------------- */
    /* ---------------------------------------------------------------------------- */

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
 
    /* ------------------------------------------------------------------------- */
    /* ------------------------- Création des couleurs ------------------------- */
    /* ------------------------------------------------------------------------- */

    // Création de la texture du texte
    SDL_Color white = {255, 255, 255, 255};
 
    /* ---------------------------------------------------------------------- */
    /* ------------------------- Boucle d'affichage ------------------------- */
    /* ---------------------------------------------------------------------- */
    // Boucle principale
    while (!quit && program_launched) {
        
        /* -------------------------------------------------------------------------- */
        /* ------------------------- Gestion des évènements ------------------------- */
        /* -------------------------------------------------------------------------- */
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                program_launched = SDL_FALSE;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT){
                    position++;
                    if(position >= nbProfils){
                        position = 0;
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT){
                    position--;
                    if(position < 0){
                        position = nbProfils - 1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN){
                    profilCourant = position;
                    quit = 1;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }
 
        /* ----------------------------------------------------------------------- */
        /* ------------------------- Création des rendus ------------------------- */
        /* ----------------------------------------------------------------------- */

        // Dessine le fond gris
        SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
        SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRect(renderer, &background);
 
        SDL_Surface* text_surface = TTF_RenderText_Blended(font, nomProfils[position], white);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect text_rect = {(SCREEN_WIDTH - text_surface->w) / 2, SCREEN_HEIGHT / 2, text_surface->w, text_surface->h };
 
        // Création du rectangle autour du texte
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect text_back = {(SCREEN_WIDTH - 350) / 2, (SCREEN_HEIGHT - 15) / 2, 350, 50};
        SDL_RenderDrawRect(renderer, &text_back);
 
        //Affichage textes
        SDL_Surface* choixProfil = TTF_RenderText_Blended(font, "Choisissez votre profil", white);
        SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", white);
        SDL_Surface* escape = TTF_RenderText_Blended(fontFooter, "Touche echap pour revenir au menu principal", white);
 
        // Créer une texture à partir de la surface
        SDL_Texture* texturechoixProfil = SDL_CreateTextureFromSurface(renderer, choixProfil);
        SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
        SDL_Texture* textureEscape = SDL_CreateTextureFromSurface(renderer, escape);
 
        // Créer un rectangle pour la texture
        SDL_Rect rectchoixProfil = {(SCREEN_WIDTH - choixProfil->w) / 2, SCREEN_HEIGHT / 2 - 100, choixProfil->w, choixProfil->h };
        SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };
        SDL_Rect rectEscape = {(SCREEN_WIDTH - escape->w) / 2, SCREEN_HEIGHT - 50, escape->w, escape->h};

        
        /* ------------------------------------------------------------------------ */
        /* ------------------------- Affichage des rendus ------------------------- */
        /* ------------------------------------------------------------------------ */
 
        // Afficher la texture
        SDL_RenderCopy(renderer, texturechoixProfil, NULL, &rectchoixProfil);
        SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);
        SDL_RenderCopy(renderer, textureEscape, NULL, &rectEscape);
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
 
        // Rafraîchissement de l'écran
        SDL_RenderPresent(renderer);


        /* ------------------------------------------------------------------------------------ */
        /* ------------------------- Liberation des textures/surfaces ------------------------- */
        /* ------------------------------------------------------------------------------------ */

        // Libération des surfaces et textures
        SDL_DestroyTexture(texturechoixProfil);
        SDL_DestroyTexture(textureCarGame);
        SDL_DestroyTexture(textureEscape);
        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
        SDL_FreeSurface(escape);
        SDL_FreeSurface(carGame);
        SDL_FreeSurface(choixProfil);

        // Réinitialisation des pointeurs
        text_surface = NULL;
        text_texture = NULL;
        texturechoixProfil = NULL;
        textureCarGame = NULL;
        textureEscape = NULL;
        text_texture = NULL;
        escape = NULL;
        carGame = NULL;
        choixProfil = NULL;
    }
 
    /* --------------------------------------------------------------- */
    /* ------------------------- Destruction ------------------------- */
    /* --------------------------------------------------------------- */
    TTF_CloseFont(font);
    TTF_CloseFont(fontLogo);
    TTF_CloseFont(fontFooter);

    // Réinitialisation des pointeurs
    font = NULL;
    fontLogo = NULL;
    fontFooter = NULL;
    return 0;
}

/**
 * @author Tom Marsura
 * @brief Fonction qui permet l'affichage du menu de création de profil
 * @param window : la fenêtre SDL
 * @param renderer : le rendu SDL
 * @return int
*/
extern int creationProfil(SDL_Window* window, SDL_Renderer* renderer){
    //Effacer l'écran
    SDL_RenderClear(renderer);
    
    /* -------------------------------------------------------------------------------- */
    /* ------------------------- Initialisation des variables ------------------------- */
    /* -------------------------------------------------------------------------------- */

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

    /* ---------------------------------------------------------------------------- */
    /* ------------------------- Initialisation de la SDL ------------------------- */
    /* ---------------------------------------------------------------------------- */
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

    if (fontLogo == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return 1;
    }

    fontFooter = TTF_OpenFont("../fonts/police.TTF", font_size - 20);

    if (fontFooter == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return 1;
    }

    /* ------------------------------------------------------------------------- */
    /* ------------------------- Création des couleurs ------------------------- */
    /* ------------------------------------------------------------------------- */

    // Création de la texture du texte
    SDL_Color white = {255, 255, 255, 255};

    /* ------------------------------------------------------------------------ */
    /* ------------------------- Création des erreurs ------------------------- */
    /* ------------------------------------------------------------------------ */

    // Création des textes d'erreur
    SDL_Surface* erreurNomExist = TTF_RenderText_Blended(font, "Pseudo deja existant", white);
    SDL_Surface* erreurNomVide = TTF_RenderText_Blended(font, "Veuillez saisir un nom", white);
    SDL_Surface* erreurNbProfils = TTF_RenderText_Blended(font, "Nombre de profils maximum atteint", white);

    // Créer une texture à partir de la surface
    SDL_Texture* textureErreurNomExist = SDL_CreateTextureFromSurface(renderer, erreurNomExist);
    SDL_Texture* textureErreurNomVide = SDL_CreateTextureFromSurface(renderer, erreurNomVide);
    SDL_Texture* textureErreurNbProfils = SDL_CreateTextureFromSurface(renderer, erreurNbProfils);

    /* ---------------------------------------------------------------------- */
    /* ------------------------- Boucle d'affichage ------------------------- */
    /* ---------------------------------------------------------------------- */

    while (!quit && program_launched) {
        
        /* -------------------------------------------------------------------------- */
        /* ------------------------- Gestion des évènements ------------------------- */
        /* -------------------------------------------------------------------------- */

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                program_launched = SDL_FALSE;
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

                    //Si le nombre maximum de profils est atteint
                    else if (nbProfils == MAX_PROFILS) {
                        textureErreurActuelle = textureErreurNbProfils;
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
        
        /* ---------------------------------------------------------------------- */
        /* ------------------------- Affichage du rendu ------------------------- */
        /* ---------------------------------------------------------------------- */
        
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
        
        /* -------------------------------------------------------------------------------------- */
        /* ------------------------- Gestion de l'affichage des erreurs ------------------------- */
        /* -------------------------------------------------------------------------------------- */

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
        
        /* ------------------------------------------------------------------------------------ */
        /* ------------------------- Libération des textures/surfaces ------------------------- */
        /* ------------------------------------------------------------------------------------ */

        SDL_DestroyTexture(textureCreateProfil);
        SDL_DestroyTexture(textureCarGame);
        SDL_DestroyTexture(textureEscape);
        SDL_FreeSurface(escape);
        SDL_FreeSurface(carGame);
        SDL_FreeSurface(createProfil);

        // Réinitialisation des pointeurs
        textureCreateProfil = NULL;
        textureCarGame = NULL;
        textureEscape = NULL;
        escape = NULL;
        carGame = NULL;
        createProfil = NULL;
    }

    /* --------------------------------------------------------------- */
    /* ------------------------- Destruction ------------------------- */
    /* --------------------------------------------------------------- */

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    TTF_CloseFont(fontLogo);
    TTF_CloseFont(fontFooter);

    //Destruction messages d'erreur
    SDL_DestroyTexture(textureErreurActuelle);
    SDL_DestroyTexture(textureErreurNomExist);
    SDL_DestroyTexture(textureErreurNomVide);

    SDL_FreeSurface(erreurNomExist);
    SDL_FreeSurface(erreurNomVide);

    //Réinitialisation des pointeurs
    text_texture = NULL;
    text_surface = NULL;
    textureErreurActuelle = NULL;
    textureErreurNomExist = NULL;
    textureErreurNomVide = NULL;
    erreurNomExist = NULL;
    erreurNomVide = NULL;
    font = NULL;
    fontLogo = NULL;
    fontFooter = NULL;

    return 0;
}

/**
 * @brief Fonction qui permet l'affichage du menu de suppression de profil
 * @param window : La fenêtre SDL
 * @param renderer : Le rendu SDL
 * @return 0 si tout s'est bien passé, 1 sinon
*/
extern int supprimeProfil(SDL_Window* window, SDL_Renderer* renderer){
    //Effacer l'écran
    SDL_RenderClear(renderer);

    
    /* -------------------------------------------------------------------------------- */
    /* ------------------------- Initialisation des variables ------------------------- */
    /* -------------------------------------------------------------------------------- */
 
    int position = 0;
    TTF_Font *font = NULL;
    TTF_Font *fontLogo = NULL;
    TTF_Font *fontFooter = NULL;
    SDL_Event event;
    int quit = 0;
    int font_size = 30;
 
 
    /* ---------------------------------------------------------------------------- */
    /* ------------------------- Initialisation de la SDL ------------------------- */
    /* ---------------------------------------------------------------------------- */

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
 
    /* ------------------------------------------------------------------------- */
    /* ------------------------- Création des couleurs ------------------------- */
    /* ------------------------------------------------------------------------- */

    // Création de la texture du texte
    SDL_Color white = {255, 255, 255, 255};
 
    /* ---------------------------------------------------------------------- */
    /* ------------------------- Boucle d'affichage ------------------------- */
    /* ---------------------------------------------------------------------- */
 
    // Boucle principale
    while (!quit && program_launched) {
        
        
        /* ---------------------------------------------------------------------------------- */
        /* ------------------------- Création des textures/surfaces ------------------------- */
        /* ---------------------------------------------------------------------------------- */
 
        // Dessine le fond gris
        SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
        SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRect(renderer, &background);
 
        SDL_Surface* text_surface = TTF_RenderText_Blended(font, nomProfils[position], white);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect text_rect = {(SCREEN_WIDTH - text_surface->w) / 2, SCREEN_HEIGHT / 2, text_surface->w, text_surface->h };
 
        // Création du rectangle autour du texte
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect text_back = {(SCREEN_WIDTH - 350) / 2, (SCREEN_HEIGHT - 15) / 2, 350, 50};
        SDL_RenderDrawRect(renderer, &text_back);
 
        //Affichage textes
        SDL_Surface* delProfil = TTF_RenderText_Blended(font, "Choisissez le profil a supprimer", white);
        SDL_Surface* carGame = TTF_RenderText_Blended(fontLogo, "CAR GAME", white);
        SDL_Surface* escape = TTF_RenderText_Blended(fontFooter, "Touche echap pour revenir au menu principal", white);
 
        // Créer une texture à partir de la surface
        SDL_Texture* texturedelProfil = SDL_CreateTextureFromSurface(renderer, delProfil);
        SDL_Texture* textureCarGame = SDL_CreateTextureFromSurface(renderer, carGame);
        SDL_Texture* textureEscape = SDL_CreateTextureFromSurface(renderer, escape);
 
        // Créer un rectangle pour la texture
        SDL_Rect rectdelProfil = {(SCREEN_WIDTH - delProfil->w) / 2, SCREEN_HEIGHT / 2 - 100, delProfil->w, delProfil->h };
        SDL_Rect rectCarGame = {(SCREEN_WIDTH - carGame->w) / 2, 100, carGame->w, carGame->h };
        SDL_Rect rectEscape = {(SCREEN_WIDTH - escape->w) / 2, SCREEN_HEIGHT - 50, escape->w, escape->h};
 
        /* -------------------------------------------------------------------------- */
        /* ------------------------- Gestion des évènements ------------------------- */
        /* -------------------------------------------------------------------------- */
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                program_launched = SDL_FALSE;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT){
                    position++;
                    if(position >= nbProfils){
                        position = 0;
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT){
                    position--;
                    if(position < 0){
                        position = nbProfils - 1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN){
                    deleteProfil(position);
                    if (position == profilCourant){
                        profilCourant = 0;
                    }
                    if(nbProfils == 0){
                        creationProfil(window, renderer);
                    }
                    quit = 1;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }
        
        /* -------------------------------------------------------------------------- */
        /* ------------------------- Affichage des textures ------------------------- */
        /* -------------------------------------------------------------------------- */

        // Afficher la texture
        SDL_RenderCopy(renderer, texturedelProfil, NULL, &rectdelProfil);
        SDL_RenderCopy(renderer, textureCarGame, NULL, &rectCarGame);
        SDL_RenderCopy(renderer, textureEscape, NULL, &rectEscape);
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
 
        // Rafraîchissement de l'écran
        SDL_RenderPresent(renderer);

        /* ----------------------------------------------------------------------------------- */
        /* ------------------------- Libération des textures/surfaces ------------------------ */
        /* ----------------------------------------------------------------------------------- */
        SDL_DestroyTexture(texturedelProfil);
        SDL_DestroyTexture(textureCarGame);
        SDL_DestroyTexture(textureEscape);
        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
        SDL_FreeSurface(escape);
        SDL_FreeSurface(carGame);
        SDL_FreeSurface(delProfil);

        // Réinitialisation des pointeurs
        text_surface = NULL;
        text_texture = NULL;
        texturedelProfil = NULL;
        textureCarGame = NULL;
        textureEscape = NULL;
        text_texture = NULL;
        escape = NULL;
        carGame = NULL;
        delProfil = NULL;
    }

    /* --------------------------------------------------------------- */
    /* ------------------------- Destruction ------------------------- */
    /* --------------------------------------------------------------- */
 
    TTF_CloseFont(font);
    TTF_CloseFont(fontLogo);
    TTF_CloseFont(fontFooter);

    // Réinitialisation des pointeurs
    font = NULL;
    fontLogo = NULL;
    fontFooter = NULL;

    return 0;
}