#ifndef INPUTKEY_H_INCLUDED
#define INPUTKEY_H_INCLUDED

#include <SDL.h>
#include "vector.h"

typedef enum input {UP, DOWN, RIGHT, LEFT, CONFIRM, CANCEL, ERROR, EMPTY} input;

// Get the input from the player, and return it
input get_input(int sym);

// Print the given input in the console
void print_input(input inp);

// Move the given rect accordingly to the input of the player
void move_character(input ply_input, SDL_Rect* p_rect, int move_speed);

#endif // INPUTKEY_H_INCLUDED
