#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "cercle.h"
#include "SDL_manager.h"
#include "tileset.h"
#include "animation.h"
#include "delta.h"

int main(int argc, char *argv[])
{
    // The frames per second
    const int FPS = 20; // In miliseconds

    SDL_manager SDL_manager1;
    SDL_manager* p_SDL_manager = &SDL_manager1;
    SDL_InitManager(p_SDL_manager);

    // Initialize the image loader
    // Enable the loading of png files
    int flag = IMG_INIT_PNG;
    int initted = IMG_Init(flag);

    if((initted & flag) != flag){ // handle error
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }

    // Initialisation des rects
    SDL_Rect rect = {140, 50, 20, 20};

    // Charge le tileset
    SDL_tileset tileset_wayne;
    SDL_CreateTilesetFromPNG(&tileset_wayne, "Wayne.png", 1, 8);

    // Inititialise l'animation
    SDL_animation anim_wayne;
    SDL_InitAnimation(&anim_wayne, &tileset_wayne, 0, 8);

    // Definit les variables necessaires a la boucle principale
    int prog_finished = 0;
    SDL_Event evenement;

    // Boucle principale du programme
    while(prog_finished != 1)
    {
        // Verifie qu'un evenement a eu lieu, si l'evenement est quit, sort du programme
        while(SDL_PollEvent(&evenement)){
            if(evenement.type == SDL_QUIT){
                prog_finished = 1;
                break;
            }
        }

        // Compute the delta time
        Uint32 current_tick = SDL_GetTicks();
        double delta = SDL_GetDelta(current_tick);

        // Wait the right time so the FPS is right
        SDL_regulate_FPS(FPS, delta);

        // Déssine le sprite donné a la position du rect
        SDL_DrawAnimation(p_SDL_manager, &anim_wayne, &rect);

        // Rendu
        SDL_ManagerRender(p_SDL_manager);
    }

    // Libère de la mémoire tous les éléments du manager (Fenètre, renderer, texture)
    SDL_FreeManager(p_SDL_manager);

    // On quitte la SDL avant de quitter le programme
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
