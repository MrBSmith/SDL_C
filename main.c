#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "cercle.h"
#include "SDL_manager.h"
#include "tileset.h"
#include "animation.h"
#include "delta.h"
#include "camera.h"
#include "map.h"
#include "inputkey.h"
#include "SDL_event.h"

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

    // Cr�e une map a partir d'un fichier texte
    SDL_map* p_map = SDL_CreateMapFromFile("Map.txt");

    // Cr�e une camera
    SDL_camera* p_camera = SDL_CreateCamera(0.0, 0.0, 640.0, 480.0);

    // Definit les variables necessaires a la boucle principale
    int prog_finished = 0;
    input_manager* p_input_manager = SDL_CreateInputManager();

    // Boucle principale du programme
    while(prog_finished != 1)
    {
        // Verifie qu'un evenement a eu lieu, si l'evenement est quit, sort du programme
        if(events_manager(p_input_manager) == 1){
            return EXIT_SUCCESS;
        }

        // Calcule le delta entre deux frames
        Uint32 current_tick = SDL_GetTicks();
        double delta = SDL_GetDelta(current_tick);

        // Attend la bonne quantit� de temps pour que le frame rate soit r�gulier
        SDL_regulate_FPS(FPS, delta);

        // Vide la surface avant de red�ssiner dedans
        SDL_FillRect(p_SDL_manager -> p_surface, NULL, SDL_MapRGB(p_SDL_manager -> p_surface -> format, 0, 0, 0));

        // Scroll horizontalement la map
        vector2 dest = {640.0, 0.0};
        p_camera -> position = linear_interpolate(p_camera -> position, dest, 0.05);

        // Dessine la map
        SDL_DrawMap(p_SDL_manager, p_map, p_tileset_map, p_camera);

        // D�place le personnage en fonction des inputs du joueur
        move_character(p_input_manager, &rect, 20);

        // D�ssine le sprite donn� a la position du rect
        SDL_DrawAnimation(p_SDL_manager, p_anim_wayne, &rect);

        // Rendu
        SDL_ManagerRender(p_SDL_manager);
    }

    // Lib�re de la m�moire tous les �l�ments du manager (Fen�tre, renderer, texture)
    SDL_FreeManager(p_SDL_manager);

    // On quitte la SDL avant de quitter le programme
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
