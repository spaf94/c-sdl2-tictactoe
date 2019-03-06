#ifndef ENGINE_H
#define ENGINE_H

#include "internal.h"

typedef enum
{
    ENGINE_PLAY_N    = 0,
    ENGINE_PLAY_O    = 1,
    ENGINE_PLAY_X    = 2
} engine_play_t;

typedef struct engine_t engine_t;

engine_t *engine_new();

void engine_free( engine_t *engine );

bool engine_next_move_get( engine_t *engine, int *row, int *column );

void engine_play_set( engine_t *engine, int row, int column, engine_play_t play );

#endif // ENGINE_H
