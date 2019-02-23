#ifndef TICTACTOE_CTX_H
#define TICTACTOE_CTX_H

/******************************************************************************/

typedef struct tictactoe_ctx_t tictactoe_ctx_t;

/******************************************************************************/

/**
* Creates a new tictactoe context
*/
tictactoe_ctx_t *tictactoe_ctx_new();

/******************************************************************************/

/**
* Release tictactoe context resources
* @param ctx    tictactoe context
*/
void tictactoe_ctx_free( tictactoe_ctx_t *ctx );

/******************************************************************************/

#endif // TICTACTOE_CTX_H
