/******************************************************************************/

#include "tictactoe_ctx.h"
#include "tictactoe_events.h"

/******************************************************************************/

int main()
{
    // Init SDL (takes some time)
    SDL_Init( SDL_INIT_VIDEO );
    // Create game context
    tictactoe_ctx_t *ctx = tictactoe_ctx_new();
    if ( ctx == NULL )
        goto end;

    while ( ctx->running )
    {
        tictactoe_events_process( ctx );
        tictactoe_ctx_renderize( ctx );
    }

end:
    // Release game context
    tictactoe_ctx_free( ctx );
    // Release SDL
    SDL_Quit();

    return 0;
}

/******************************************************************************/
