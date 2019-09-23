#ifndef ENGINE_H
#define ENGINE_H

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

typedef enum
{
    ENGINE_PLAY_N    = 0,
    ENGINE_PLAY_O    = 1,
    ENGINE_PLAY_X    = 2
} engine_play_t;

typedef struct
{
    int row;
    int column;
} engine_move_t;

typedef struct engine_t engine_t;

/******************************************************************************/

/**
* @brief Creates game engine
* @return game engine
*/
engine_t *engine_new( void );

/******************************************************************************/

/**
* @brief Releases game engine resources
* @param engine game engine
*/
void engine_free( engine_t *engine );

/******************************************************************************/

/**
* @brief Gets next movement
* @param engine game engine
* @param move   next move data
* @return true, if new move is founded
*/
bool engine_next_move_get( engine_t *engine, engine_move_t *move );

/******************************************************************************/

/**
* @brief Checks if move is valid
* @param engine game engine
* @param move   move data
* @return true, if move is valid
*/
bool engine_move_valid( engine_t *engine, engine_move_t *move );

/******************************************************************************/

/**
* @brief Sets a player move
* @param engine game engine
* @param move   move data
* @param play   play type
*/
void engine_move_set(
        engine_t *engine, engine_move_t *move, engine_play_t play );

/******************************************************************************/

/**
* @brief Gets all game moves
* @param engine     game engine
* @param x_arr      player X moves array
* @param x_arr_len  player X moves array length
* @param o_arr      player O moves array
* @param o_arr_len  player O moves array length
*/
void engine_moves_get(
        engine_t *engine,
        engine_move_t *x_arr,
        int *x_arr_len,
        engine_move_t *o_arr,
        int *o_arr_len );

/******************************************************************************/

/**
* @brief Checks if a game has finished
* @param engine     game engine
* @param winner_arr winner moves array
* @return true, when game finished
*/
bool engine_game_finished( engine_t *engine, engine_move_t *winner_arr );

/******************************************************************************/

/**
 * @brief Cleans engine plays
 * @param engine    Game engine
 */
void engine_plays_clean( engine_t *engine );

/******************************************************************************/

/**
 * @brief Gets next COM move
 * @param engine    Game engine
 * @param move      Next move
 */
void engine_com_next_move_get( engine_t *engine, engine_move_t *move );

/******************************************************************************/

#endif // ENGINE_H
