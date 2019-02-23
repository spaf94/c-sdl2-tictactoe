#include "tictactoe_ctx.h"
#include "internal.h"

#include <stdio.h>

int main()
{
    // Init SDL (takes some time)
    SDL_Init( SDL_INIT_VIDEO );
    // Create game context
    tictactoe_ctx_t *ctx = tictactoe_ctx_new();
    if ( ctx == NULL )
        goto end;

//    while ( tictactoe_ctx_running_get( ctx) )
//    {

//    }

    SDL_Delay( 3000 );

end:
    // Release game context
    tictactoe_ctx_free( ctx );
    // Release SDL
    SDL_Quit();

    return 0;
}
