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
            board->rect_arr[i][k].x = wm + (BOARD_DIV_W * i);
            board->rect_arr[i][k].y = hm + (BOARD_DIV_W * k);
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
    board->playing = true;
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
    SDL_Color color = color_SDL_Color_get( COLOR_GAINSBORO );
    SDL_SetRenderDrawColor( board->renderer, color.r, color.g, color.b, color.a );
    SDL_RenderClear( board->renderer );

    if ( board->playing )
    {
        engine_next_move_get( board->engine, &board->row, &board->column );

        if ( board->blinking )
            color = color_SDL_Color_get( COLOR_LIGHTSKYBLUE );
        else
            color = color_SDL_Color_get( COLOR_GAINSBORO );

        SDL_SetRenderDrawColor( board->renderer, color.r, color.g, color.b, color.a );
        SDL_Rect rect = board->rect_arr[board->row][board->column];
        SDL_RenderFillRect( board->renderer, &rect );

        const int cx = rect.x + (rect.w / 2);
        const int cy = rect.y + (rect.h / 2);
        if ( board->playerX )
        {
            SDL_Rect data = { cx, cy, 100, 100 };
            shape_X_render( board->renderer, &data, 4, COLOR_BLACK );
        }
        else
        {
            SDL_Point center = { cx, cy };
            shape_circle_render( board->renderer, &center, 50, 4, COLOR_RED );
        }
    }

    // Draw horizontal lines
    for ( int i = 1; i < 3; i++ )
        _board_line_render( board, i, false );

    // Draw vertical lines
    for ( int i = 1; i < 3; i++ )
        _board_line_render( board, i, true );
}

/******************************************************************************/
