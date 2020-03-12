#ifndef SDL_MANAGER_H_INCLUDED
#define SDL_MANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef struct SDL_manager
{
    SDL_Window *p_window;
    SDL_Renderer *p_renderer;
    SDL_Texture *p_texture;
    SDL_Surface *p_surface;
} SDL_manager;

int SDL_init_manager(SDL_manager* p_SDL_manager);

#endif // SDL_MANAGER_H_INCLUDED
