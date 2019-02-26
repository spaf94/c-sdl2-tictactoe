#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "internal.h"
#include "menu.h"

typedef enum
{
    PLAY_MODE_NONE,
    PLAY_MODE_1VS1,
    PLAY_MODE_1VSCOM
} play_mode_t;

typedef struct
{
    // SDL
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    // Game
    menu_t *menu;
    bool running;
    play_mode_t play_mode;
} tictactoe_t;

tictactoe_t *tictactoe_new();

void tictactoe_free( tictactoe_t *ttt );

void tictactoe_render( tictactoe_t *ttt );

#endif // TICTACTOE_H
