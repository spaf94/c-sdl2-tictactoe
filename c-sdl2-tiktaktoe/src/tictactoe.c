#include "tictactoe.h"

#define WINDOW_TITLE    "Tic-Tac-Toe"
#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define CRAZY_TTF_FILE  "../c-sdl2-tiktaktoe/fonts/crazy.ttf"

static
void _tictactoe_sdl_data_init( tictactoe_t *ttt )
{
    // Create game window
    ttt->window = SDL_CreateWindow( WINDOW_TITLE,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    0 );
    // Create game renderer
    uint32_t flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ttt->renderer = SDL_CreateRenderer( ttt->window, -1, flags );
    // Load font
    ttt->font = TTF_OpenFont( CRAZY_TTF_FILE, 24 );
    if ( ttt->font == NULL )
        SDL_Log( "OPEN FONT FAILED! \n" );
}

tictactoe_t *tictactoe_new()
{
    tictactoe_t *ttt = calloc( 1, sizeof (*ttt) );
    ttt->running = true;
    ttt->play_mode = PLAY_MODE_NONE;
    // Init SDL data
    _tictactoe_sdl_data_init( ttt );
    // Init menu
    ttt->menu = menu_new( ttt->renderer, ttt->font );

    return ttt;
}

void tictactoe_free( tictactoe_t *ttt )
{
    if ( ttt != NULL )
    {
        if ( ttt->menu != NULL )
            menu_free( ttt->menu );

        free( ttt );
    }
}

void tictactoe_render( tictactoe_t *ttt )
{
    const bool menu = (ttt->play_mode == PLAY_MODE_NONE);
    if ( menu )
    {
        menu_render( ttt->menu );
    }
    else
    {

    }

    SDL_RenderPresent( ttt->renderer );
}
