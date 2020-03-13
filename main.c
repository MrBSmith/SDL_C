#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "cercle.h"
#include "SDL_manager.h"


int init_SDL_window(SDL_Window* p_window, SDL_Renderer* p_renderer);

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

    // Initialisation d'un point
    // SDL_Point point1 = {20, 10};

    // Initialisation des rects
    SDL_Rect rect1 = {40, 50, 20, 20};
    SDL_Rect rect2 = {140, 50, 20, 20};
    SDL_Rect rect3 = {200, 50, 20, 20};

    // Initialisation d'une couleur
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color black = {0, 0, 0, 255};

    // Creation d'un cercle
    circle circle1 = {100, 150, 40};
    circle circle2 = {200, 150, 40};


    SDL_Surface* p_surface = IMG_Load("Stump.png");

    // Creation d'une surface
    //SDL_Surface* p_surface = SDL_LoadBMP("Vierbit4.bmp");
    SDL_Surface* p_surface2 = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

    // Déssine un rectangle bleu dans la surface
    SDL_FillRect(p_surface, &rect3, SDL_MapRGB(p_surface->format, 0, 255, 0));

    // Copie une surface dans une autre
    SDL_BlitSurface(p_surface, NULL, p_surface2, NULL);

    // Crée une texture a partir de la surface
    p_SDL_manager -> p_texture = SDL_CreateTextureFromSurface(p_SDL_manager -> p_renderer, p_surface);

    // Libere l'espace en memoire attribué a la surface
    SDL_FreeSurface(p_surface);
    SDL_FreeSurface(p_surface2);

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
        // Verifie qu'un evenement a eu lieu, si l'evenement est
        while(SDL_PollEvent(&evenement)){
            if(evenement.type == SDL_QUIT){
                prog_finished = 1;
                break;
            }
        }

        // Rempli le fond de la couleur déclarée plus haut
        SDL_SetRenderDrawColor(p_SDL_manager -> p_renderer, red.r, red.g, red.b, red.a);
        SDL_RenderClear(p_SDL_manager -> p_renderer);

        // Dessine un rectangle de couleur noir
        SDL_SetRenderDrawColor(p_SDL_manager -> p_renderer, black.r, black.g, black.b, black.a);
        SDL_RenderDrawRect(p_SDL_manager -> p_renderer, &rect1);

        SDL_RenderDrawRect(p_SDL_manager -> p_renderer, &rect2);
        SDL_RenderFillRect(p_SDL_manager -> p_renderer, &rect2);

        // Dessine un cercle de couleur noir, vide
        DrawCircle(p_SDL_manager -> p_renderer, &circle1, black);

        // Dessine un cercle de couleur noir, plein
        DrawFilledCircle(p_SDL_manager -> p_renderer, &circle2, black);


        // Définit la texture comme cible du renderer
        SDL_SetRenderTarget(p_SDL_manager -> p_renderer, p_SDL_manager -> p_texture);

        // Déssine la texture
        SDL_RenderCopy(p_SDL_manager -> p_renderer, p_SDL_manager -> p_texture, NULL, NULL);


        SDL_RenderPresent(p_SDL_manager -> p_renderer);
    }

    // Détruit la fenêtre et le renderer avant de quitter le programme
    SDL_DestroyRenderer(p_SDL_manager -> p_renderer);
    SDL_DestroyWindow(p_SDL_manager -> p_window);

    // On quitte la SDL avant de quitter le programme
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
