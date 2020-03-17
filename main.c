#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "cercle.h"
#include "SDL_manager.h"
#include "tileset.h"

int init_SDL_window(SDL_Window* p_window, SDL_Renderer* p_renderer);
int loop_index(int current_value, int max_value, int increment_value);
double SDL_GetDelta(Uint32 current_tick);

int main(int argc, char *argv[])
{
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

    // Definit les variables necesaires a la boucle principale
    int loop_i = 0;
    int prog_finished = 0;
    SDL_Event evenement;
    Uint32 current_tick;
    float delta;

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

        current_tick = SDL_GetTicks();
        delta =  SDL_GetDelta(current_tick);
        printf("%lf", delta);

        loop_i = loop_index(loop_i, 7, 1);


        // Déssine le sprite donné a la position du rect
        DrawSpriteFromTileset(p_SDL_manager, &tileset_wayne, loop_i, &rect);

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

// Compute the delta time between two frames
double SDL_GetDelta(Uint32 current_tick){
    Uint32 new_tick = SDL_GetTicks();
    return new_tick - current_tick;
}


// Increment a value and wrap it if it's over the given max_value
int loop_index(int current_value, int max_value, int increment_value){
    current_value += increment_value;
    if(current_value > max_value){
        current_value = 0;
    }
    return current_value;
}
