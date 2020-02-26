#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Include the SDL library

int main(int argc, char *argv[])
{
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        // Creation d'une surface de 640*480 pixels, 32bits/pxl pour les couleurs, en utilisant la mémoire de la carte 3D
        SDL_Window* window = SDL_CreateWindow("Ma fenêtre de jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

        if (window == NULL){
            printf("Impossble de creer la fenetre: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }

        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError()); // Affiche un message d'erreur si l'initialisation de la SDL a échouée
        return EXIT_FAILURE; // On quitte le programme si l'ouverture de la SDL a échouée
    }

    SDL_Quit(); // On quitte la SDL avant de quitter le programme
    return EXIT_SUCCESS;
}
