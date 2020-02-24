#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h> // Include the SDL library

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
       printf("Erreur d'initialisation de la SDL : %s", SDL_GetError()); // Affiche un message d'erreur si l'initialisation de la SDL a échouée
       return EXIT_FAILURE; // On quitte le programme si l'ouverture de la SDL a échouée
    }

    SDL_Quit(); // On quitte la SDL avant de quitter le programme
    return 0;
}
