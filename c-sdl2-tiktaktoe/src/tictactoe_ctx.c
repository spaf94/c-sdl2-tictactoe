/******************************************************************************/

#include "tictactoe_ctx.h"

/******************************************************************************/

/**
* @brief Creates a new tictactoe context
*/
tictactoe_ctx_t *tictactoe_ctx_new()
{
    tictactoe_ctx_t *ctx = calloc( 1, sizeof (*ctx) );
    ctx->gui = tictactoe_gui_new(); // Creates game GUI
    ctx->menu_option = MENU_OPTION_1VS1;
    ctx->running = true;

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
* @brief Renderizes game
* @param ctx    game context
*/
void tictactoe_ctx_renderize( tictactoe_ctx_t *ctx )
{
    // Gets menu option
    ttt_img_t img = TTT_IMG_NONE;
    switch ( ctx->menu_option )
    {
    case MENU_OPTION_NONE:
        img = TTT_IMG_NONE;
        break;
    case MENU_OPTION_1VS1:
        img = TTT_IMG_MENU_1VS1;
        break;
    case MENU_OPTION_1VSCOM:
        img = TTT_IMG_MENU_1VSCOM;
        break;
    case MENU_OPTION_QUIT:
        img = TTT_IMG_MENU_QUIT;
        break;
    }

    SDL_Log( "ctx->menu_option: %d | img: %d \n", ctx->menu_option, img );

    // Draw menu
    tictactoe_gui_menu_renderize( ctx->gui, img );

    // Show render
    SDL_RenderPresent( ctx->gui->ren_main );
}

/******************************************************************************/
