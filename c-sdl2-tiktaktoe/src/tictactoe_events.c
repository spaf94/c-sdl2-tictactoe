/******************************************************************************/

#include "tictactoe_events.h"
#include "internal.h"

/******************************************************************************/

/**
* @brief Handling SDLK_RETURN keydown event
* @param ctx    game context
*/
static
void _tictactoe_events_keydown_SDLK_RETURN_handle( tictactoe_ctx_t *ctx )
{
    if ( ctx->playing )
    {

    }
    else
    {
        switch ( ctx->menu_option )
        {
        case MENU_OPTION_QUIT:
            ctx->running = false;
            break;
        default:
            break;
        }
    }
}

/******************************************************************************/

/**
* @brief Handling SDLK_UP keydown event
* @param ctx    game context
*/
static
void _tictactoe_events_keydown_SDLK_UP_handle( tictactoe_ctx_t *ctx )
{
    if ( ctx->playing )
    {

    }
    else
    {
        if ( (ctx->menu_option - 1) < MENU_OPTION_1VS1 )
            ctx->menu_option = MENU_OPTION_QUIT;
        else
            ctx->menu_option--;
    }
}

/******************************************************************************/

/**
* @brief Handling SDLK_DOWN keydown event
* @param ctx    game context
*/
static
void _tictactoe_events_keydown_SDLK_DOWN_handle( tictactoe_ctx_t *ctx )
{
    if ( ctx->playing )
    {

    }
    else
    {
        if ( (ctx->menu_option + 1) > MENU_OPTION_QUIT )
            ctx->menu_option = MENU_OPTION_1VS1;
        else
            ctx->menu_option++;
    }
}

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
    SDL_Log( "%d \n", key_ev->keysym.sym );

    switch ( key_ev->keysym.sym )
    {
    case SDLK_ESCAPE:
        ctx->running = false;
        break;
    case SDLK_DOWN:
        _tictactoe_events_keydown_SDLK_DOWN_handle( ctx );
        break;
    case SDLK_UP:
        _tictactoe_events_keydown_SDLK_UP_handle( ctx );
        break;
    case SDLK_RETURN:
        _tictactoe_events_keydown_SDLK_RETURN_handle( ctx );
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
