#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "cercle.h"
#include "SDL_manager.h"

int init_SDL_window(SDL_Window* p_window, SDL_Renderer* p_renderer);
void DrawSpriteFromTileset(SDL_manager* p_SDL_manager, SDL_Surface* p_tileset, int nb_column, int nb_row, int frame_id, SDL_Rect* p_screen_pos);

int main(int argc, char *argv[])
{
    SDL_manager SDL_manager1;
    SDL_manager* p_SDL_manager = &SDL_manager1;
    SDL_init_manager(p_SDL_manager);

    // Initialize the image loader
    // Enable the loading of png files
    int flag = IMG_INIT_PNG;
    int initted = IMG_Init(flag);

    if((initted & flag) != flag){ // handle error
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }

    // Initialisation des rects
    SDL_Rect rect1 = {40, 50, 20, 20};
    SDL_Rect rect2 = {140, 50, 20, 20};
    SDL_Rect rect3 = {200, 50, 20, 20};

    // Charge le tileset
    SDL_Surface* p_surface_wayne = IMG_Load("Wayne.png");

    //
    DrawSpriteFromTileset(p_SDL_manager, p_surface_wayne, 8, 1, 0, &rect2);

    // Crée une texture a partir de la surface
    p_SDL_manager -> p_texture = SDL_CreateTextureFromSurface(p_SDL_manager -> p_renderer, p_SDL_manager -> p_surface);

    Uint32 format = 0;
    int access = 0;
    int width = 0;
    int height = 0;

    if(SDL_QueryTexture(p_SDL_manager -> p_texture, &format, &access, &width, &height) != 0){
        return EXIT_FAILURE;
    } else {
        printf("La texture fait %d par %d", width, height);
    }

    // Definit les variables necesaires a la boucle principale
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

        // Rafraichit l'affichage
        SDL_RenderClear(p_SDL_manager -> p_renderer);

        // Définit la texture comme cible du renderer
        SDL_SetRenderTarget(p_SDL_manager -> p_renderer, p_SDL_manager -> p_texture);

        // Déssine la texture
        SDL_RenderCopy(p_SDL_manager -> p_renderer, p_SDL_manager -> p_texture, NULL, NULL);
        SDL_RenderPresent(p_SDL_manager -> p_renderer);
    }

    // Détruit la fenêtre et le renderer avant de quitter le programme
    SDL_DestroyRenderer(p_SDL_manager -> p_renderer);
    SDL_DestroyWindow(p_SDL_manager -> p_window);

    // Libere l'espace en memoire attribué a la surface
    SDL_FreeSurface(p_surface_wayne);

    // On quitte la SDL avant de quitter le programme
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}


// Dessine un sprite a partir d'un tileset, du nombre de rangés et de lignes dans ce tile set et de sa position dans celui-ci
// Stock le dit sprite dans la surface du SDL_Manager
void DrawSpriteFromTileset(SDL_manager* p_SDL_manager, SDL_Surface* p_tileset, int nb_column, int nb_row, int frame_id, SDL_Rect* p_screen_pos){

	SDL_Rect Rect_tile;
	Rect_tile.w = (p_tileset -> w) / nb_column;
	Rect_tile.h = (p_tileset -> h) / nb_row;
    Rect_tile.x = frame_id * Rect_tile.w;
    Rect_tile.y = 0;

    SDL_BlitSurface(p_tileset, &Rect_tile, p_SDL_manager -> p_surface, p_screen_pos);
}

