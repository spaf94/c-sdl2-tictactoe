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

bool engine_next_move_get( engine_t *engine, engine_play_data_t *data )
{
    if ( engine->plays[data->row][data->column] == ENGINE_PLAY_N )
        return true;

    for ( int i = 0; i < GAME_BOARD_DIVS; i++ )
    {
        for ( int k = 0; k < GAME_BOARD_DIVS; k++ )
        {
            if ( engine->plays[i][k] == ENGINE_PLAY_N )
            {
                data->row = i;
                data->column = k;
                return true;
            }
        }
    }

    return false;
}

bool engine_move_valid( engine_t *engine, engine_play_data_t *data )
{
    return (engine->plays[data->row][data->column] == ENGINE_PLAY_N);
}

void engine_play_set( engine_t *engine, int row, int column, engine_play_t play )
{
    engine->plays[row][column] = play;
}

void engine_plays_get(
        engine_t *engine,
        engine_play_data_t *x_arr,
        int *x_arr_len,
        engine_play_data_t *o_arr,
        int *o_arr_len )
{
    int x_len = 0;
    int o_len = 0;

    for ( int i = 0; i < GAME_BOARD_DIVS; i++ )
    {
        for ( int k = 0; k < GAME_BOARD_DIVS; k++ )
        {
            const engine_play_t play = engine->plays[i][k];

            switch ( play )
            {
            case ENGINE_PLAY_X:
                x_arr[x_len].row = i;
                x_arr[x_len].column = k;
                x_len++;
                break;
            case ENGINE_PLAY_O:
                o_arr[o_len].row = i;
                o_arr[o_len].column = k;
                o_len++;
                break;
            default:
                break;
            }
        }
    }

    if ( x_arr_len != NULL )
        *x_arr_len = x_len;
    if ( o_arr_len != NULL )
        *o_arr_len = o_len;
}
