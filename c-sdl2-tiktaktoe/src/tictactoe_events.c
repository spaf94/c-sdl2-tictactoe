/******************************************************************************/

#include "tictactoe_events.h"
#include "internal.h"

/******************************************************************************/

/**
* @brief Handling keydown events
* @param ctx    tictactoe context
* @param key_ev keyboard event
*/
static
void _tictactoe_events_keydown_handle(
        tictactoe_ctx_t *ctx, SDL_KeyboardEvent *key_ev )
{
    switch ( key_ev->keysym.sym )
    {
    case SDLK_ESCAPE:
        ctx->running = false;
        break;
    case SDLK_DOWN:
        if ( (ctx->menu_option + 1) > MENU_OPTION_QUIT )
            ctx->menu_option = MENU_OPTION_1VS1;
        else
            ctx->menu_option++;
        break;
    case SDLK_UP:
        if ( (ctx->menu_option - 1) < MENU_OPTION_1VS1 )
            ctx->menu_option = MENU_OPTION_QUIT;
        else
            ctx->menu_option--;
        break;
    default:
        break;
    }
}

/******************************************************************************/

/**
* @brief Process game events
* @param ctx    tictactoe context
*/
void tictactoe_events_process( tictactoe_ctx_t *ctx )
{
    SDL_Event event = { 0 };

    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
        case SDL_KEYDOWN:
            _tictactoe_events_keydown_handle( ctx, &event.key );
            break;
        case SDL_WINDOWEVENT_CLOSE:
        case SDL_QUIT:
            ctx->running = false;
            break;
        }
    }
}

/******************************************************************************/
