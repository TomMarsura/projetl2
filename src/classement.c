/**
 * @file classement.c
 * @brief Génération et affichage du classement par points des joueurs
 * @authors Ayoub LAARIBI,Tom MARSURA,Thibaut GASNIER
 * @version 1.0
*/

#include <stdio.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_ttf.h"

#include "../lib/sdl.h"
#include "../lib/menu.h"

/**
 * @brief Fonction main : fonction de création du classement par points
 * @author Tom Marsura
 * @return int
*/
extern void classement()
{
    int i, j;
    int maxIndex;

    for (i = 0; i < nbProfils; i++) {
        maxIndex = i;
        for (j = i+1; j < nbProfils; j++) {
            if (pointsProfils[j] > pointsProfils[maxIndex]) {
                maxIndex = j;
            }
        }
        // Échange des éléments à l'indice i et maxIndex pour tous les tableaux
        int tmpPoints = pointsProfils[i];
        pointsProfils[i] = pointsProfils[maxIndex];
        pointsProfils[maxIndex] = tmpPoints;

        char tmpNom[SIZE_NAME];
        strcpy(tmpNom, nomProfils[i]);
        strcpy(nomProfils[i], nomProfils[maxIndex]);
        strcpy(nomProfils[maxIndex], tmpNom);

        int tmpNum = numProfils[i];
        numProfils[i] = numProfils[maxIndex];
        numProfils[maxIndex] = tmpNum;

        int tmpNbParties = nbPartiesProfils[i];
        nbPartiesProfils[i] = nbPartiesProfils[maxIndex];
        nbPartiesProfils[maxIndex] = tmpNbParties;
    }
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
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
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
extern void afficherTableau(SDL_Window* window, SDL_Renderer* renderer)
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

    TTF_Font* fontFooter = TTF_OpenFont("../fonts/police.TTF", 10);

    if (fontFooter == NULL) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s", TTF_GetError());
        return ;
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
    int y2;
    if(nbProfils > 18){
        y2 = 50 + 30 * 18;
    }
    else{
        y2 = 50 + 30 * nbProfils;
    }
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

    int affichageNbProfils;
    if(nbProfils > 18){
        affichageNbProfils = 18;
    }
    else{
        affichageNbProfils = nbProfils;
    }

    for (int i = 0; i < affichageNbProfils; i++)
        {



            // Créer une surface à partir de la chaîne de caractères
            SDL_Surface* place = TTF_RenderText_Blended(police, iTab[i], couleur);
            SDL_Surface* name = TTF_RenderText_Blended(police, nomProfils[i], couleur);
            SDL_Surface* points = TTF_RenderText_Blended(police, pointsTab[i], couleur);
            SDL_Surface* parties = TTF_RenderText_Blended(police, partiesTab[i], couleur);
            SDL_Surface* escape = TTF_RenderText_Blended(fontFooter, "Touche echap pour revenir au menu principal", couleur);
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
            SDL_Texture* textureEscape = SDL_CreateTextureFromSurface(renderer, escape);
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
            SDL_Rect rectEscape = {(SCREEN_WIDTH - escape->w) / 2, SCREEN_HEIGHT - 50, escape->w, escape->h};

            // Afficher la texture
            SDL_RenderCopy(renderer, texturePlace, NULL, &rectI);
            SDL_RenderCopy(renderer, textureName, NULL, &rectName);
            SDL_RenderCopy(renderer, texturePoints, NULL, &rectPoints);
            SDL_RenderCopy(renderer, textureParties, NULL, &rectParties);
            SDL_RenderCopy(renderer, textureEscape, NULL, &rectEscape);

            // Libérer la surface et la texture
            SDL_FreeSurface(place);
            SDL_FreeSurface(name);
            SDL_FreeSurface(points);
            SDL_FreeSurface(parties);
            SDL_FreeSurface(escape);
            SDL_DestroyTexture(texturePlace);
            SDL_DestroyTexture(textureName);
            SDL_DestroyTexture(texturePoints);
            SDL_DestroyTexture(textureParties);
            SDL_DestroyTexture(textureEscape);

            //Réinitialisation des pointeurs
            place = NULL;
            name = NULL;
            points = NULL;
            parties = NULL;
            escape = NULL;
            texturePlace = NULL;
            textureName = NULL;
            texturePoints = NULL;
            textureParties = NULL;
            textureEscape = NULL;
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

        //Réinitialisation des pointeurs
        surfaceFond = NULL;
        placeColonne = NULL;
        nameColonne = NULL;
        pointsColonne = NULL;
        partiesColonne = NULL;
        textureFond = NULL;
        texturePlaceColonne = NULL;
        textureNomColonne = NULL;
        texturePointsColonne = NULL;
        texturePartiesColonne = NULL;

        // Libérer la police
        police = NULL;
        TTF_CloseFont(police);

        attenteClassement();
}