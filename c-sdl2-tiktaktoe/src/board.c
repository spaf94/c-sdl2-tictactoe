/******************************************************************************/

#include "board.h"
#include "color.h"
#include "shape.h"

#include <math.h>

/******************************************************************************/

#define BOARD_LINE_W    405 // Board line width
#define BOARD_LINE_H    5   // Board line heigth
#define BOARD_DIV_W     (BOARD_LINE_W / 3) // Board divided in 3 zones
#define BOARD_TIMER_MS  500

/******************************************************************************/

static
void _board_winner_line_render( board_t *board, engine_move_t *winner_arr )
{
    const engine_move_t im = winner_arr[0];
    SDL_Rect ini_rect = board->rect_arr[im.row][im.column];

    const engine_move_t em = winner_arr[2];
    SDL_Rect end_rect = board->rect_arr[em.row][em.column];

    SDL_Point ini_point = { 0 };
    ini_point.x = ini_rect.x + (ini_rect.w / 2);
    ini_point.y = ini_rect.y + (ini_rect.h / 2);

    SDL_Point end_point = { 0 };
    end_point.x = end_rect.x + (end_rect.w / 2);
    end_point.y = end_rect.y + (end_rect.h / 2);

    shape_line_thickness_render(
                board->renderer, &ini_point, &end_point, 5, COLOR_RED );
}

static
void _board_player_render( SDL_Renderer *renderer, SDL_Rect *rect, bool playerX )
{
    const int cx = rect->x + (rect->w / 2);
    const int cy = rect->y + (rect->h / 2);
    if ( playerX )
    {
        SDL_Rect data = { cx, cy, 65, 65 };
        shape_X_render( renderer, &data, 5, COLOR_LIGHTSLATEGRAY );
    }
    else
    {
        SDL_Point center = { cx, cy };
        shape_circle_render( renderer, &center, 35, 5, COLOR_BLACK );
    }
}

/******************************************************************************/

static
void _board_plays_render( board_t *board )
{
    int x_arr_len = 0;
    int o_arr_len = 0;
    engine_move_t x_arr[GAME_MAX_PLAYS] = { 0 };
    engine_move_t o_arr[GAME_MAX_PLAYS] = { 0 };
    engine_moves_get( board->engine, x_arr, &x_arr_len, o_arr, &o_arr_len );

    // Draw X's
    for ( int i = 0; i < x_arr_len; i++ )
    {
        const engine_move_t x = x_arr[i];
        SDL_Rect rect = board->rect_arr[x.row][x.column];

        _board_player_render( board->renderer, &rect, true );
    }

    // Draw O's
    for ( int i = 0; i < o_arr_len; i++ )
    {
        const engine_move_t o = o_arr[i];
        SDL_Rect rect = board->rect_arr[o.row][o.column];

        _board_player_render( board->renderer, &rect, false );
    }
}

/******************************************************************************/

static
uint32_t _board_timer_elapsed( uint32_t interval, void *param )
{
    board_t *board = param;

    if ( board->blinking )
        board->blinking = false;
    else
        board->blinking = true;

    board->timer = SDL_AddTimer( interval, _board_timer_elapsed, board );
}

/******************************************************************************/

/**
* Render board line
* @param board      board context
* @param line       line number
* @param vertical   true, for vertical line
*/
static
void _board_line_render( board_t *board, int line, bool vertical )
{
    int lh = 0; // Line height
    int lw = 0; // Line width
    int lx = 0; // Line x position
    int ly = 0; // Line y position

    if ( vertical )
    {
        // Vertical line
        const int wm = ((board->window_w - BOARD_LINE_W) / 2); // Width margin
        lh = BOARD_LINE_W;
        lw = BOARD_LINE_H;
        ly = ((board->window_h - BOARD_LINE_W) / 2);
        lx = (wm + (BOARD_DIV_W * line));
    }
    else
    {
        // Horizontal line
        const int hm = ((board->window_h - BOARD_LINE_W) / 2); // Height margin
        lh = BOARD_LINE_H;
        lw = BOARD_LINE_W;
        ly = (hm + (BOARD_DIV_W * line));
        lx = ((board->window_w - BOARD_LINE_W) / 2);
    }

    SDL_Color color = color_SDL_Color_get( COLOR_GAME_BLUE );
    SDL_SetRenderDrawColor( board->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect = { lx, ly, lw, lh };
    SDL_RenderFillRect( board->renderer, &rect );
}

/******************************************************************************/

static
void _board_plays_rect_init( board_t *board )
{
    const int wm = ((board->window_w - BOARD_LINE_W) / 2); // Width margin
    const int hm = ((board->window_h - BOARD_LINE_W) / 2); // Height margin

    for ( int i = 0; i < 3; i++ )
    {
        for ( int k = 0; k < 3; k++ )
        {
            board->rect_arr[i][k].x = wm + (BOARD_DIV_W * k);
            board->rect_arr[i][k].y = hm + (BOARD_DIV_W * i);
            board->rect_arr[i][k].h = BOARD_DIV_W;
            board->rect_arr[i][k].w = BOARD_DIV_W;
        }
    }
}

/******************************************************************************/

/**
* @brief Create a board context
* @param renderer   game renderer
* @param font       game font
* @param wh         game window heigth
* @param ww         game window width
* @return board context
*/
board_t *board_new( SDL_Renderer *renderer, TTF_Font *font, int wh, int ww )
{
    board_t *board = calloc( 1, sizeof (*board) );
    board->renderer = renderer;
    board->font = font;
    board->window_h = wh;
    board->window_w = ww;
    board->blinking = true;
    board->engine = engine_new();

    _board_plays_rect_init( board );

    return board;
}

/******************************************************************************/

/**
* @brief Release board context
* @param board   board context
*/
void board_free( board_t *board )
{
    if ( board != NULL )
    {
        free( board );

        if ( board->engine != NULL )
            engine_free( board->engine );
    }
}

/******************************************************************************/

/**
* @brief Render the board
* @param board   board context
*/
void board_render( board_t *board )
{
    if( board->timer <= 0 )
        board->timer = SDL_AddTimer( BOARD_TIMER_MS, _board_timer_elapsed, board );

    // Set menu background
    SDL_Color color = color_SDL_Color_get( COLOR_WHITESMOKE );
    SDL_SetRenderDrawColor( board->renderer, color.r, color.g, color.b, color.a );
    SDL_RenderClear( board->renderer );

    // Checks if game finished
    engine_move_t winner_arr[GAME_BOARD_DIVS] = { 0 };
    const bool finished = engine_game_finished( board->engine, winner_arr );

    if ( finished )
    {
        _board_winner_line_render( board, winner_arr );
    }
    else
    {
        engine_next_move_get( board->engine, &board->play_data );

        if ( board->blinking )
            color = color_SDL_Color_get( COLOR_GAINSBORO );
        else
            color = color_SDL_Color_get( COLOR_WHITESMOKE );

        SDL_SetRenderDrawColor( board->renderer, color.r, color.g, color.b, color.a );
        SDL_Rect rect = board->rect_arr[board->play_data.row][board->play_data.column];
        SDL_RenderFillRect( board->renderer, &rect );

        _board_player_render( board->renderer, &rect, board->playerX );
    }

    // Draw horizontal lines
    for ( int i = 1; i < 3; i++ )
        _board_line_render( board, i, false );

    // Draw vertical lines
    for ( int i = 1; i < 3; i++ )
        _board_line_render( board, i, true );

    // Draw last plays
    _board_plays_render( board );
}

/******************************************************************************/

/**
* @brief Moves a player in the board
* @param board      game board
* @param direction  direction
*/
void board_player_move( board_t *board, board_direction_t direction )
{
    if ( direction == BOARD_DIRECTION_UP )
    {
        if ( (board->play_data.row - 1) < 0 )
            board->play_data.row = (GAME_BOARD_DIVS - 1);
        else
            board->play_data.row--;

        while ( !engine_move_valid( board->engine, &board->play_data ))
        {
            if ( (board->play_data.row - 1) < 0 )
                board->play_data.row = (GAME_BOARD_DIVS - 1);
            else
                board->play_data.row--;
        }
    }
    else if ( direction == BOARD_DIRECTION_DOWN )
    {
        if ( (board->play_data.row + 1) >= GAME_BOARD_DIVS )
            board->play_data.row = 0;
        else
            board->play_data.row++;

        while ( !engine_move_valid( board->engine, &board->play_data ))
        {
            if ( (board->play_data.row + 1) >= GAME_BOARD_DIVS )
                board->play_data.row = 0;
            else
                board->play_data.row++;
        }
    }
    else if ( direction == BOARD_DIRECTION_RIGHT )
    {
        if ( (board->play_data.column + 1) >= GAME_BOARD_DIVS )
            board->play_data.column = 0;
        else
            board->play_data.column++;

        while ( !engine_move_valid( board->engine, &board->play_data ))
        {
            if ( (board->play_data.column + 1) >= GAME_BOARD_DIVS )
                board->play_data.column = 0;
            else
                board->play_data.column++;
        }
    }
    else if ( direction == BOARD_DIRECTION_LEFT )
    {
        if ( (board->play_data.column - 1) < 0 )
            board->play_data.column = (GAME_BOARD_DIVS - 1);
        else
            board->play_data.column--;

        while ( !engine_move_valid( board->engine, &board->play_data ))
        {
            if ( (board->play_data.column - 1) < 0 )
                board->play_data.column = (GAME_BOARD_DIVS - 1);
            else
                board->play_data.column--;
        }
    }
}

/******************************************************************************/
