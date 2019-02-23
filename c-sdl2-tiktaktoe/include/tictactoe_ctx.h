#ifndef TICTACTOE_CTX_H
#define TICTACTOE_CTX_H

/******************************************************************************/

#include <stdbool.h>

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

/**
* @brief Gets flag running value
* @param ctx    tictactoe context
* @return true, when game is running
*/
bool tictactoe_ctx_running_get( tictactoe_ctx_t *ctx );

/******************************************************************************/

/**
* @brief Sets flag running value
* @param ctx        tictactoe context
* @param running    running value [TRUE or FALSE]
*/
void tictactoe_ctx_running_set( tictactoe_ctx_t *ctx, bool running );

/******************************************************************************/

#endif // TICTACTOE_CTX_H
