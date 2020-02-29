#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int init_SDL_window(SDL_Window* p_window, SDL_Renderer* p_renderer);

int main(int argc, char *argv[])
{
    SDL_Window* p_window = NULL;
    SDL_Renderer* p_renderer = NULL;
    SDL_Event evenement;
    int prog_finished = 0;

    // Initialisation de la SDL, de la fenêtre et du renderer associé
    if(SDL_Init(SDL_INIT_VIDEO) != 0){

        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError()); // Affiche un message d'erreur si l'initialisation de la SDL a échouée
        return EXIT_FAILURE; // On quitte le programme si l'ouverture de la SDL a échouée

    } else {

        // Creation d'une surface de 640*480 pixels, 32bits/pxl pour les couleurs, en utilisant la mémoire de la carte 3D
        p_window = SDL_CreateWindow("Ma fenetre de jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

        // Creation du renderer associé a la fenêtre
        p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

        // Verification d'une potentielle erreur lors de la création de la fenètre
        if(p_window == NULL){
            printf("Impossble de creer la fenetre: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }

        // Verification d'une potentielle erreur lors de la création du renderer
        if(p_renderer == NULL){
            printf("Impossble de creer le renderer: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
    }

    // Initialisation d'un point
    SDL_Point point1;

    // Définition de la position du point
    point1.x = 10;
    point1.y = 20;

    // Initialisation d'un rect
    SDL_Rect rect1;

    // Définition de la position du rect, et de ses dimentions
    rect1.x = 40;
    rect1.y = 50;
    rect1.w = 20;
    rect1.h = 20;

    // Initialisation d'une couleur
    SDL_Color red;

    // Définition de la couleur contenue dans notre element de type SDL_Color fraichement initialisé
    red.r = 255;
    red.g = 0;
    red.b = 0;
    red.a = 255;


    // Boucle principale du programme
    while(prog_finished != 1)
    {

        // Verifie qu'un evenement a eu lieu, si l'evenement est
        while(SDL_PollEvent(&evenement)){
            if(evenement.type == SDL_QUIT){
                prog_finished = 1;
                break;
            }
        }

        SDL_RenderPresent(p_renderer);
    }

    // Détruit la fenêtre et le renderer avant de quitter le programme
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyWindow(p_window);

    // On quitte la SDL avant de quitter le programme
    SDL_Quit();
    return EXIT_SUCCESS;
}
