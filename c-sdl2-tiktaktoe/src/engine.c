#include "engine.h"

struct engine_t
{
    engine_play_t plays[GAME_BOARD_DIVS][GAME_BOARD_DIVS];
};

engine_t *engine_new()
{
    engine_t *engine = calloc( 1, sizeof (*engine) );

    return engine;
}

void engine_free( engine_t *engine )
{
    if ( engine != NULL )
    {
        free( engine );
    }
}

bool engine_next_move_get( engine_t *engine, int *row, int *column )
{
    if ( engine->plays[*row][*column] == ENGINE_PLAY_N )
        return true;

    for ( int i = 0; i < GAME_BOARD_DIVS; i++ )
    {
        for ( int k = 0; k < GAME_BOARD_DIVS; k++ )
        {
            if ( engine->plays[i][k] == ENGINE_PLAY_N )
            {
                *row = i;
                *column = k;
                return true;
            }
        }
    }

    return false;
}

void engine_play_set( engine_t *engine, int row, int column, engine_play_t play )
{
    engine->plays[row][column] = play;
}
