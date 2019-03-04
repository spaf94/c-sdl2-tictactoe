#ifndef BOARD_H
#define BOARD_H

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

typedef struct
{
    // SDL
    SDL_Renderer *renderer;
    TTF_Font *font;
    // Aux data
    int window_w;
    int window_h;
    // Board
    int timer;
    bool playing;
    bool blinking;
} board_t;

/******************************************************************************/

/**
* @brief Create a board context
* @param renderer   game renderer
* @param font       game font
* @param wh         game window heigth
* @param ww         game window width
* @return board context
*/
board_t *board_new( SDL_Renderer *renderer, TTF_Font *font, int wh, int ww );

/******************************************************************************/

/**
* @brief Release board context
* @param board   board context
*/
void board_free( board_t *board );

/******************************************************************************/

/**
* @brief Render the board
* @param board   board context
*/
void board_render( board_t *board );

/******************************************************************************/

#endif // BOARD_H
