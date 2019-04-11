/******************************************************************************/

#include "board.h"
#include "color.h"
#include "shape.h"
#include "endmenu.h"

#include <math.h>

/******************************************************************************/

#define BOARD_LINE_W    405 // Board line width
#define BOARD_LINE_H    5   // Board line heigth
#define BOARD_DIV_W     (BOARD_LINE_W / 3) // Board divided in 3 zones
#define BOARD_TIMER_MS  500
#define BOARD_SHAPE_TH  5   // Board shape thickness

/******************************************************************************/

struct board_t
{
    // SDL
    SDL_Renderer *renderer;
    TTF_Font *font;
    // Board
    engine_t *engine;
    endmenu_t *menu;
    board_closing_callback_t *cb;
    void *cb_arg;
    int timer;
    bool blinking;
    bool playerX;
    bool finished;
    // Board rectangles
    SDL_Rect rect_arr[GAME_BOARD_DIVS][GAME_BOARD_DIVS];
    engine_move_t play_data;
};

/******************************************************************************/

/**
* @brief Renders the winner line
* @param board      game board
* @param winner_arr winner moves array
*/
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
                board->renderer,
                &ini_point,
                &end_point,
                BOARD_SHAPE_TH,
                COLOR_RED );
}

/******************************************************************************/

/**
* @brief Renders the player (X or O)
* @param renderer   game renderer
* @param rect       rectangle to draw
* @param playerX    true, if is X player
*/
static
void _board_player_render( SDL_Renderer *renderer, SDL_Rect *rect, bool playerX )
{
    const int cx = rect->x + (rect->w / 2);
    const int cy = rect->y + (rect->h / 2);

    if ( playerX )
    {
        SDL_Rect data = { cx, cy, 65, 65 };
        shape_X_render( renderer, &data, BOARD_SHAPE_TH, COLOR_LIGHTSLATEGRAY );
    }
    else
    {
        SDL_Point center = { cx, cy };
        shape_circle_render( renderer, &center, 35, BOARD_SHAPE_TH, COLOR_BLACK );
    }
}

/******************************************************************************/

/**
* @brief Renders board playing animation
* @param board  game board
*/
static
void _board_playing_animation_render( board_t *board )
{
    SDL_Color color = { 0 };
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

/******************************************************************************/

/**
* @brief Renders all game plays
* @param board  game board
*/
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

/**
* @brief On board timer elapsed
* @param interval   interval
* @param param      param
*/
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
        const int wm = ((GAME_WINDOW_W - BOARD_LINE_W) / 2); // Width margin
        lh = BOARD_LINE_W;
        lw = BOARD_LINE_H;
        ly = ((GAME_WINDOW_H - BOARD_LINE_W) / 2);
        lx = (wm + (BOARD_DIV_W * line));
    }
    else
    {
        // Horizontal line
        const int hm = ((GAME_WINDOW_H - BOARD_LINE_W) / 2); // Height margin
        lh = BOARD_LINE_H;
        lw = BOARD_LINE_W;
        ly = (hm + (BOARD_DIV_W * line));
        lx = ((GAME_WINDOW_W - BOARD_LINE_W) / 2);
    }

    SDL_Color color = color_SDL_Color_get( COLOR_GAME_BLUE );
    SDL_SetRenderDrawColor( board->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect = { lx, ly, lw, lh };
    SDL_RenderFillRect( board->renderer, &rect );
}

/******************************************************************************/

/**
* @brief Initialize the plays rectangles array
* @param board  game board
*/
static
void _board_plays_rect_init( board_t *board )
{
    const int wm = ((GAME_WINDOW_W - BOARD_LINE_W) / 2); // Width margin
    const int hm = ((GAME_WINDOW_H - BOARD_LINE_W) / 2); // Height margin

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
* @param cb         callback
* @param cb_arg     callback argument
* @return board context
*/
board_t *board_new(
        SDL_Renderer *renderer,
        TTF_Font *font,
        board_closing_callback_t *cb,
        void *cb_arg )
{
    board_t *board = calloc( 1, sizeof (*board) );
    board->renderer = renderer;
    board->font = font;
    board->blinking = true;
    board->engine = engine_new();
    board->menu = endmenu_new( renderer, font );
    board->cb = cb;
    board->cb_arg = cb_arg;

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
        if ( board->menu != NULL )
            endmenu_free( board->menu );
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
    board->finished = engine_game_finished( board->engine, winner_arr );

    // Game not finished, draw animation
    if ( !board->finished )
        _board_playing_animation_render( board );

    // Draw horizontal lines
    for ( int i = 1; i < 3; i++ )
        _board_line_render( board, i, false );

    // Draw vertical lines
    for ( int i = 1; i < 3; i++ )
        _board_line_render( board, i, true );

    // Draw last plays
    _board_plays_render( board );

    // Game finished, draw winner line
    if ( board->finished )
    {
        _board_winner_line_render( board, winner_arr );
        endmenu_render( board->menu );
    }
}

/******************************************************************************/

/**
* @brief Moves a player in the board
* @param board      game board
* @param direction  direction
*/
void board_player_move( board_t *board, board_direction_t direction )
{
    if ( board->finished )
    {
        switch ( direction )
        {
        case BOARD_DIRECTION_RIGHT:
            endmenu_option_change( board->menu, true );
            break;
        case BOARD_DIRECTION_LEFT:
            endmenu_option_change( board->menu, false );
            break;
        default:
            break;
        }

        return;
    }

    // Game in progress
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

/**
* @brief Moves a player to x y in the board
* @param board      game board
* @param x          x position
* @param y          y position
*/
void board_player_xy_move( board_t *board, const int x, const int y )
{
    if ( board->finished )
        return;

    for ( int row = 0; row < GAME_BOARD_DIVS; row++ )
    {
        for ( int column = 0; column < GAME_BOARD_DIVS; column++ )
        {
            SDL_Rect rect = board->rect_arr[row][column];
            const bool x_ok = ((rect.x < x) && (x < (rect.x + rect.w)));
            const bool y_ok = ((rect.y < y) && (y < (rect.y + rect.h)));

            if ( x_ok && y_ok )
            {
                board->play_data.row = row;
                board->play_data.column = column;
                break;
            }
        }
    }
}

/******************************************************************************/

/**
* @brief Sets a board move
* @param board  game board
*/
void board_move_set( board_t *board )
{
    if ( board->finished )
    {
        endmenu_option_t option = endmenu_option_get( board->menu );
        const bool quit = (option == ENDMENU_OPTION_QUIT);

        if ( board->cb != NULL )
            board->cb( quit, board->cb_arg );
    }
    else
    {
        if ( board->playerX )
        {
            board->playerX = false;
            engine_move_set( board->engine, &board->play_data, ENGINE_PLAY_X );
        }
        else
        {
            board->playerX = true;
            engine_move_set( board->engine, &board->play_data, ENGINE_PLAY_O );
        }
    }
}

/******************************************************************************/

/**
* @brief Restarts the board
* @param board  game board
*/
void board_restart( board_t *board )
{
    // Clean up board
    board->finished = false;
    board->playerX = false;
    board->blinking = true;
    board->timer = 0;
    memset( &board->play_data, 0, sizeof (board->play_data) );
    // Clean up engine plays
    engine_plays_clean( board->engine );
}

/******************************************************************************/
