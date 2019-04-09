/******************************************************************************/

#include "engine.h"

/******************************************************************************/

struct engine_t
{
    engine_play_t plays[GAME_BOARD_DIVS][GAME_BOARD_DIVS];
};

/******************************************************************************/

/**
* @brief Creates game engine
* @return game engine
*/
engine_t *engine_new()
{
    engine_t *engine = calloc( 1, sizeof (*engine) );

    return engine;
}

/******************************************************************************/

/**
* @brief Releases game engine resources
* @param engine game engine
*/
void engine_free( engine_t *engine )
{
    if ( engine != NULL )
    {
        free( engine );
    }
}

/******************************************************************************/

/**
* @brief Gets next movement
* @param engine game engine
* @param move   next move data
* @return true, if new move is founded
*/
bool engine_next_move_get( engine_t *engine, engine_move_t *move )
{
    if ( engine_move_valid( engine, move ) )
        return true;

    for ( int row = 0; row < GAME_BOARD_DIVS; row++ )
    {
        for ( int column = 0; column < GAME_BOARD_DIVS; column++ )
        {
            if ( engine->plays[row][column] == ENGINE_PLAY_N )
            {
                move->row = row;
                move->column = column;
                return true;
            }
        }
    }

    return false;
}

/******************************************************************************/

/**
* @brief Checks if move is valid
* @param engine game engine
* @param move   move data
* @return true, if move is valid
*/
bool engine_move_valid( engine_t *engine, engine_move_t *move )
{
    return ( engine->plays[move->row][move->column] == ENGINE_PLAY_N );
}

/******************************************************************************/

/**
* @brief Sets a player move
* @param engine game engine
* @param move   move data
* @param play   play type
*/
void engine_move_set( engine_t *engine, engine_move_t *move, engine_play_t play )
{
    engine->plays[move->row][move->column] = play;
}

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

/******************************************************************************/

/**
* @brief Checks if a game has finished
* @param engine     game engine
* @param winner_arr winner moves array
* @return true, when game finished
*/
bool engine_game_finished( engine_t *engine, engine_move_t *winner_arr )
{
    engine_play_t play = ENGINE_PLAY_N;
    engine_play_t last = ENGINE_PLAY_N;
    int count = 0;

    // For each row, for each column
    for ( int row = 0; row < GAME_BOARD_DIVS; row++ )
    {
        count = 0;
        for ( int column = 0; column < GAME_BOARD_DIVS; column++ )
        {
            play = engine->plays[row][column];
            if ( column == 0 )
                last = play;
            if ( play != last || play == ENGINE_PLAY_N )
                break;

            winner_arr[count].row = row;
            winner_arr[count].column = column;
            count++;

            if ( count == GAME_BOARD_DIVS )
                return true;
        }
    }

    // For each column, for each row
    for ( int column = 0; column < GAME_BOARD_DIVS; column++ )
    {
        count = 0;
        for ( int row = 0; row < GAME_BOARD_DIVS; row++ )
        {
            play = engine->plays[row][column];
            if ( row == 0 )
                last = play;
            if ( play != last || play == ENGINE_PLAY_N )
                break;

            winner_arr[count].row = row;
            winner_arr[count].column = column;
            count++;

            if ( count == GAME_BOARD_DIVS )
                return true;
        }
    }

    // First diagonal
    count = 0;
    for ( int row = 0, column = 0; row < GAME_BOARD_DIVS; row++, column++ )
    {
        play = engine->plays[row][column];
        if ( row == 0 && column == 0 )
            last = play;
        if ( play != last || play == ENGINE_PLAY_N )
            break;

        winner_arr[count].row = row;
        winner_arr[count].column = column;
        count++;

        if ( count == GAME_BOARD_DIVS )
            return true;
    }

    // Second diagonal
    count = 0;
    const int col_max = (GAME_BOARD_DIVS - 1);
    for ( int row = 0, column = col_max; row < GAME_BOARD_DIVS; row++, column-- )
    {
        play = engine->plays[row][column];
        if ( row == 0 && column == col_max )
            last = play;
        if ( play != last || play == ENGINE_PLAY_N )
            break;

        winner_arr[count].row = row;
        winner_arr[count].column = column;
        count++;

        if ( count == GAME_BOARD_DIVS )
            return true;
    }

    return false;
}

/******************************************************************************/

void engine_plays_clean( engine_t *engine )
{
    memset( &engine->plays, 0, sizeof (engine->plays) );
}

/******************************************************************************/

