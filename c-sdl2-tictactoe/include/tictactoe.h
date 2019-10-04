#ifndef TICTACTOE_H
#define TICTACTOE_H

/******************************************************************************/

#include "internal.h"
#include "menu.h"
#include "board.h"

/******************************************************************************/

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
    board_t *board;
    bool running;
    play_mode_t play_mode;
} tictactoe_t;

/******************************************************************************/

/**
* @brief Create game context
* @return game context
*/
tictactoe_t *tictactoe_new( void );

/******************************************************************************/

/**
* @brief Release game resources
* @param ttt    game context
*/
void tictactoe_free( tictactoe_t *ttt );

/******************************************************************************/

/**
* @brief Render the game
* @param ttt    game context
*/
void tictactoe_render( tictactoe_t *ttt );

/******************************************************************************/

/**
* @brief Handle game events
* @param ttt    game context
*/
void tictactoe_events_handle( tictactoe_t *ttt );

/******************************************************************************/

#endif // TICTACTOE_H
