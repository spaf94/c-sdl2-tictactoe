#ifndef ENGINE_H
#define ENGINE_H

#include "internal.h"

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
} engine_play_data_t;

typedef struct engine_t engine_t;

engine_t *engine_new();

void engine_free( engine_t *engine );

bool engine_next_move_get( engine_t *engine, engine_play_data_t *data );

bool engine_move_valid( engine_t *engine, engine_play_data_t *data );

void engine_play_set( engine_t *engine, int row, int column, engine_play_t play );

void engine_plays_get(
        engine_t *engine,
        engine_play_data_t *x_arr,
        int *x_arr_len,
        engine_play_data_t *o_arr,
        int *o_arr_len );

#endif // ENGINE_H
