#include <stdio.h>
#include <stdlib.h>

#include "inputkey.h"

// Get the input from the player, and return it
input get_input(int sym){
    input control = EMPTY;
    switch(sym){
        case SDLK_z:
            control = UP; break;

        case SDLK_q:
            control = LEFT; break;

        case SDLK_d:
            control = RIGHT; break;

        case SDLK_s:
            control = DOWN; break;

        case SDLK_v:
            control = CONFIRM; break;

        case SDLK_n:
            control = CANCEL; break;

        default :
            control = ERROR; break;
    }

    return control;
}

// Print the given input in the console
void print_input(input inp){
    if (inp != EMPTY){
        printf("Input: ");
        switch(inp)
        {
            case UP:
                 printf("UP\n"); break;
            case LEFT:
                 printf("LEFT\n"); break;
            case RIGHT:
                printf("RIGHT\n"); break;
            case DOWN:
                printf("DOWN\n"); break;
            case CONFIRM:
                printf("CONFIRM\n"); break;
            case CANCEL:
                printf("CANCEL\n"); break;
            default :
                printf("ERROR\n"); break;
        }
    }
}


void move_character(input ply_input, SDL_Rect* p_rect, int move_speed){
    if (ply_input != EMPTY){
        switch(ply_input)
        {
            case UP:
                p_rect -> y -= move_speed; break;
            case LEFT:
                p_rect -> x -= move_speed; break;
            case RIGHT:
                p_rect -> x += move_speed; break;
            case DOWN:
                p_rect -> y += move_speed; break;
            default :
                break;
        }
    }
}

