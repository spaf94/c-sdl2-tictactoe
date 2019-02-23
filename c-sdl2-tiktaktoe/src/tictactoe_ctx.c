/******************************************************************************/

#include "tictactoe_ctx.h"
#include "tictactoe_gui.h"

#include <stdlib.h>

/******************************************************************************/

struct tictactoe_ctx_t
{
    // GUI context
    tictactoe_gui_t *gui;
    // Flag running
    bool running;
};

/******************************************************************************/

/**
* @brief Creates a new tictactoe context
*/
tictactoe_ctx_t *tictactoe_ctx_new()
{
    tictactoe_ctx_t *ctx = calloc( 1, sizeof (*ctx) );
    ctx->gui = tictactoe_gui_new(); // Creates game GUI

    tictactoe_ctx_running_set( ctx, true );

    return ctx;
}

/******************************************************************************/

/**
* @brief Release tictactoe context resources
* @param ctx    tictactoe context
*/
void tictactoe_ctx_free( tictactoe_ctx_t *ctx )
{
    if ( ctx != NULL )
    {
        // Free GUI context
        tictactoe_gui_free( ctx->gui );
        // Free game context
        free( ctx );
    }
}

/******************************************************************************/

/**
* @brief Gets flag running value
* @param ctx    tictactoe context
* @return true, when game is running
*/
bool tictactoe_ctx_running_get( tictactoe_ctx_t *ctx )
{
    if ( ctx != NULL )
        return ctx->running;

    return false;
}

/******************************************************************************/

/**
* @brief Sets flag running value
* @param ctx        tictactoe context
* @param running    running value [TRUE or FALSE]
*/
void tictactoe_ctx_running_set( tictactoe_ctx_t *ctx, bool running )
{
    if ( ctx != NULL )
        ctx->running = running;
}

/******************************************************************************/
