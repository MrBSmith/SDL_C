#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

int init_SDL_window(SDL_Window* p_window, SDL_Renderer* p_renderer);
void DrawCircle(SDL_Renderer *p_renderer, int origin_x, int origin_y, int radius, SDL_Color color);
void DrawFilledCircle(SDL_Renderer *p_renderer, int origin_x, int origin_y, int radius, SDL_Color color);

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

        // Verification d'une potentielle erreur lors de la création de la fenêtre
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
    SDL_Rect rect1, rect2, rect3;

    // Définition de la position du rect, et de ses dimentions
    rect1.x = 40;
    rect1.y = 50;
    rect1.w = 20;
    rect1.h = 20;

    // Définition de la position du rect, et de ses dimentions
    rect2.x = 140;
    rect2.y = 50;
    rect2.w = 20;
    rect2.h = 20;

    // Définition de la position du rect, et de ses dimentions
    rect3.x = 200;
    rect3.y = 50;
    rect3.w = 20;
    rect3.h = 20;

    // Initialisation d'une couleur
    SDL_Color red;

    // Définition de la couleur contenue dans notre element de type SDL_Color fraichement initialisé
    red.r = 255;
    red.g = 0;
    red.b = 0;
    red.a = 255;

    // Initialisation d'une couleur
    SDL_Color black;

    // Définition de la couleur contenue dans notre element de type SDL_Color fraichement initialisé
    black.r = 0;
    black.g = 0;
    black.b = 0;
    black.a = 255;

    // Creation d'une surface
    SDL_Surface* p_surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
    SDL_Surface* p_surface2 = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

    // Déssine un rectangle bleu dans la surface
    SDL_FillRect(p_surface, &rect3, SDL_MapRGB(p_surface->format, 0, 255, 0));

    // Copie une surface dans une autre
    SDL_BlitSurface(p_surface, NULL, p_surface2, NULL);

    // Crée une texture a partir de la surface
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface2);

    // Libere l'espace en memoire attribué a la surface
    SDL_FreeSurface(p_surface);
    SDL_FreeSurface(p_surface2);

    Uint32 format = 0;
    int access = 0;
    int width = 0;
    int height = 0;

    if(SDL_QueryTexture(p_texture, &format, &access, &width, &height) != 0){
        return EXIT_FAILURE;
    } else {
        printf("La texture fait %d par %d", width, height);
    }

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

        /*
        // Rempli le fond de la couleur déclarée plus haut
        SDL_SetRenderDrawColor(p_renderer, red.r, red.g, red.b, red.a);
        SDL_RenderClear(p_renderer);

        // Dessine un rectangle de couleur noir
        SDL_SetRenderDrawColor(p_renderer, black.r, black.g, black.b, black.a);
        SDL_RenderDrawRect(p_renderer, &rect1);

        SDL_RenderDrawRect(p_renderer, &rect2);
        SDL_RenderFillRect(p_renderer, &rect2);

        // Dessine un cercle de couleur noir, vide
        DrawCircle(p_renderer, 100, 150, 40, black);

        // Dessine un cercle de couleur noir, plein
        DrawFilledCircle(p_renderer, 200, 150, 40, black);
        */

        // Définit la texture comme cible du renderer
        SDL_SetRenderTarget(p_renderer, p_texture);

        // Déssine la texture
        SDL_RenderCopy(p_renderer, p_texture, NULL, NULL);

        SDL_RenderPresent(p_renderer);
    }

    // Détruit la fenêtre et le renderer avant de quitter le programme
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyWindow(p_window);

    // On quitte la SDL avant de quitter le programme
    SDL_Quit();
    return EXIT_SUCCESS;
}


// Dessine le cercle donné
void DrawCircle(SDL_Renderer *p_renderer, int origin_x, int origin_y, int radius, SDL_Color color)
{
    int new_x = 0;
    int new_y = 0;
    int old_x =  origin_x + radius;
    int old_y = origin_y;
    float step = (M_PI * 2) / 50;

    SDL_SetRenderDrawColor(p_renderer, color.r, color.g, color.b, 255);

    for(float theta = 0; theta <= (M_PI * 2); theta += step){
        new_x = origin_x + (radius * cos(theta));
        new_y = origin_y - (radius * sin(theta));

        SDL_RenderDrawLine(p_renderer, old_x, old_y, new_x, new_y);

        old_x = new_x;
        old_y = new_y;
    }

    new_x = origin_x + radius;
    new_y = origin_y;
    SDL_RenderDrawLine(p_renderer, old_x, old_y, new_x, new_y);

}


// Dessine le cercle donné, rempli
void DrawFilledCircle(SDL_Renderer *p_renderer, int origin_x, int origin_y, int radius, SDL_Color color)
{
	for(double dy = 1; dy <= radius; dy += 1.0){

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));

		SDL_SetRenderDrawColor(p_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(p_renderer, origin_x - dx, origin_y + dy - radius, origin_x + dx, origin_y + dy - radius);
		SDL_RenderDrawLine(p_renderer, origin_x - dx, origin_y - dy + radius, origin_x + dx, origin_y - dy + radius);

	}
}

