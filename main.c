#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError()); // Affiche un message d'erreur si l'initialisation de la SDL a échouée
        return EXIT_FAILURE; // On quitte le programme si l'ouverture de la SDL a échouée

    } else {

        // Creation d'une surface de 640*480 pixels, 32bits/pxl pour les couleurs, en utilisant la mémoire de la carte 3D
        SDL_Window* p_window = SDL_CreateWindow("Ma fenetre de jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

        // Creation du renderer associé a la fenêtre
        SDL_Renderer* p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

        if (p_window != NULL){

            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
            SDL_DestroyWindow(p_window);

        } else {

            // Verification d'une potentielle erreur lors de la création de la fenètre
            printf("Impossble de creer la fenetre: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
    }


    SDL_Quit(); // On quitte la SDL avant de quitter le programme
    return EXIT_SUCCESS;
}
