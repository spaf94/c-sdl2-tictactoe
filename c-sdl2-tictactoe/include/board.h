#ifndef BOARD_H
#define BOARD_H

/******************************************************************************/

#include "internal.h"
#include "engine.h"

/******************************************************************************/

typedef void board_closing_callback_t( bool quit, void *cb_arg );

typedef enum
{
    BOARD_DIRECTION_UP,
    BOARD_DIRECTION_DOWN,
    BOARD_DIRECTION_RIGHT,
    BOARD_DIRECTION_LEFT
} board_direction_t;

typedef struct board_t board_t;

/******************************************************************************/

/**
* @brief Create a board context
* @param renderer   game renderer
* @param font       game font
* @param cb         callback
* @param cb_arg     callback argument
* @return board context
*/
board_t *board_new(
        SDL_Renderer *renderer,
        TTF_Font *font,
        board_closing_callback_t *cb,
        void *cb_arg );

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

/**
* @brief Moves a player in the board
* @param board      game board
* @param direction  direction
*/
void board_player_move( board_t *board, board_direction_t direction );

/******************************************************************************/

/**
* @brief Moves a player to x y in the board
* @param board      game board
* @param x          x position
* @param y          y position
* @return true, if some change happens
*/
bool board_player_xy_move( board_t *board, const int x, const int y );

/******************************************************************************/

/**
* @brief Sets a board move
* @param board  game board
*/
void board_move_set( board_t *board );

/******************************************************************************/

/**
* @brief Restarts the board
* @param board  game board
*/
void board_restart( board_t *board );

/******************************************************************************/

#endif // BOARD_H
