/******************************************************************************/

#include "tictactoe_ctx.h"

#include <stdlib.h>

/******************************************************************************/

struct tictactoe_ctx_t
{
    int status;
};

/******************************************************************************/

/**
* Creates a new tictactoe context
*/
tictactoe_ctx_t *tictactoe_ctx_new()
{
    tictactoe_ctx_t *ctx = calloc( 1, sizeof (*ctx) );
    ctx->status = -1;

    return ctx;
}

/******************************************************************************/

/**
* Release tictactoe context resources
* @param ctx    tictactoe context
*/
void tictactoe_ctx_free( tictactoe_ctx_t *ctx )
{
    free( ctx );
}

/******************************************************************************/
