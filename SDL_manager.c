#include "SDL_manager.h"


int SDL_init_manager(SDL_manager* p_SDL_manager){

    // Initialisation de la SDL, de la fen�tre et du renderer associ�
    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError()); // Affiche un message d'erreur si l'initialisation de la SDL a �chou�e
        return EXIT_FAILURE; // On quitte le programme si l'ouverture de la SDL a �chou�e

    } else {

        // Creation d'une surface de 640*480 pixels, 32bits/pxl pour les couleurs, en utilisant la m�moire de la carte 3D
        p_SDL_manager -> p_window = SDL_CreateWindow("Ma fenetre de jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

        // Creation du renderer associ� a la fen�tre
        p_SDL_manager -> p_renderer = SDL_CreateRenderer(p_SDL_manager -> p_window, -1, SDL_RENDERER_ACCELERATED);

        // Verification d'une potentielle erreur lors de la cr�ation de la fen�tre
        if(p_SDL_manager -> p_window == NULL){
            printf("Impossble de creer la fenetre: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }

        // Verification d'une potentielle erreur lors de la cr�ation du renderer
        if(p_SDL_manager -> p_renderer == NULL){
            printf("Impossble de creer le renderer: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
