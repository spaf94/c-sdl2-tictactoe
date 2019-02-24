#ifndef TICTACTOE_CTX_H
#define TICTACTOE_CTX_H

/******************************************************************************/

#include "tictactoe_gui.h"
#include "internal.h"

/******************************************************************************/

typedef enum menu_options
{
    MENU_OPTION_NONE    = -1,
    MENU_OPTION_1VS1    = 0,
    MENU_OPTION_1VSCOM  = 1,
    MENU_OPTION_QUIT    = 2
} menu_option_t;

typedef struct tictactoe_ctx
{
    // GUI context
    tictactoe_gui_t *gui;
    // Menu option
    menu_option_t menu_option;
    // Flag running
    bool running;
} tictactoe_ctx_t;

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
* @brief Renderizes game
* @param ctx    game context
*/
void tictactoe_ctx_renderize( tictactoe_ctx_t *ctx );

/******************************************************************************/

#endif // TICTACTOE_CTX_H
