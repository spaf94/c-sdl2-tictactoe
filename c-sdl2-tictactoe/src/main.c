/******************************************************************************/

#include "tictactoe.h"

/******************************************************************************/

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    // Init SDL (takes some time)
    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    // Create game context
    tictactoe_t *ttt = tictactoe_new();

    while ( ttt->running )
    {
        tictactoe_events_handle( ttt );
        tictactoe_render( ttt );
        SDL_Delay( 100 );
    }

    // Release game context
    tictactoe_free( ttt );
    // Quit SDL
    TTF_Quit();
    SDL_Quit();

    return 0;
}

/******************************************************************************/
