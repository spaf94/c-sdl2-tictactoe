#ifndef INTERNAL_H
#define INTERNAL_H

// Include SDL2 headers
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

// Include system headers
#include <stdio.h>
#include <stdbool.h>

// Defines
#define GAME_BOARD_DIVS     3
#define GAME_MAX_PLAYS      GAME_BOARD_DIVS * GAME_BOARD_DIVS
#define GAME_WINDOW_W       640 // Game window width
#define GAME_WINDOW_H       480 // Game window height

// Utils
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

#endif // INTERNAL_H
