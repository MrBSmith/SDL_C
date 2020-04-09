#include "SDL_event.h"

// Boucle attendant des evenements SDL
int events_manager(input* p_input){
    SDL_Event event;
    *p_input = EMPTY;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: // En cas d'event quit
                return 1;
                break;

            case SDL_KEYDOWN: // En cas d'input clavier
                *p_input = get_input(event.key.keysym.sym);
                print_input(*p_input);
                break;
        }
    }

    return 0;
}
