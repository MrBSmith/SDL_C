#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "cercle.h"
#include "SDL_manager.h"
#include "tileset.h"
#include "animation.h"
#include "delta.h"
#include "map.h"

int main(int argc, char *argv[])
{
    // The frames per second
    const int FPS = 20;

    SDL_manager* p_SDL_manager = SDL_InitManager();

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

    // Charge le tileset de la map
    SDL_tileset* p_tileset_map = SDL_CreateTilesetFromPNG("MapTileset.png", 1, 6);

    // Charge le tileset de l'animation
    SDL_tileset* p_tileset_wayne = SDL_CreateTilesetFromPNG("Wayne.png", 1, 8);

    // Inititialise l'animation
    SDL_animation* p_anim_wayne = SDL_InitAnimation(p_tileset_wayne, 0, 8);


    // Crée une map a partir d'un fichier texte
    SDL_map* p_map = SDL_CreateMapFromFile("Map.txt");
    printf("width: %d, height: %d\n", p_map -> w, p_map -> h);
    SDL_print_map_char(p_map);

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

        // Calcule le delta entre deux frames
        Uint32 current_tick = SDL_GetTicks();
        double delta = SDL_GetDelta(current_tick);

        // Attend la bonne quantité de temps pour que le frame rate soit régulier
        SDL_regulate_FPS(FPS, delta);

        // Vide la surface avant de redéssiner dedans
        SDL_FillRect(p_SDL_manager -> p_surface, NULL, SDL_MapRGB(p_SDL_manager -> p_surface -> format, 0, 0, 0));

        // Dessine la map
        SDL_DrawMap(p_SDL_manager, p_map, p_tileset_map);

        // Déssine le sprite donné a la position du rect
        SDL_DrawAnimation(p_SDL_manager, p_anim_wayne, &rect);

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
