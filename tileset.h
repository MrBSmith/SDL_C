#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED
#include <SDL.h>
#include "SDL_manager.h"

typedef struct SDL_tileset{
    SDL_Surface * p_surface;
    int rows;
    int columns;
} SDL_tileset;

void SDL_CreateTilesetFromPNG(SDL_tileset * p_tileset ,const char* file, int rows, int columns);
void DrawSpriteFromTileset(SDL_manager* p_SDL_manager, SDL_tileset* p_tileset, int frame_id, SDL_Rect* p_screen_pos);

#endif // TILESET_H_INCLUDED
