/******************************************************************************/

#include "menu.h"
#include "color.h"

/******************************************************************************/

#define MENU_BUTTON_W   150
#define MENU_BUTTON_H   50
#define MENU_BUTTON_B   3
#define MENU_BUTTON_BW  MENU_BUTTON_W + ( MENU_BUTTON_B * 2)
#define MENU_BUTTON_BH  MENU_BUTTON_H + ( MENU_BUTTON_B * 2)

/******************************************************************************/

/**
* @brief Render a button menu
* @param menu   menu context
* @param x      button x position
* @param y      button y position
* @param hover  true, to hover button
* @param text   button text
*/
static
void _menu_button_render(
        menu_t *menu,
        int x,
        int y,
        bool hover,
        const char *text )
{
    // Border position
    const int bx = x - MENU_BUTTON_B;
    const int by = y - MENU_BUTTON_B;
    // Draw border
    SDL_Color color = color_SDL_Color_get( COLOR_BLACK );
    SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_border = { bx, by, MENU_BUTTON_BW, MENU_BUTTON_BH };
    SDL_RenderFillRect( menu->renderer, &rect_border );

    // Gets button color
    if ( hover )
        color = color_SDL_Color_get( COLOR_GAME_LIGHTBLUE );
    else
        color = color_SDL_Color_get( COLOR_GAME_BLUE );
    // Draw button
    SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_button = { x, y, MENU_BUTTON_W, MENU_BUTTON_H };
    SDL_RenderFillRect( menu->renderer, &rect_button );

    // Gets text color
    if ( hover )
        color = color_SDL_Color_get( COLOR_BLACK );
    else
        color = color_SDL_Color_get( COLOR_WHITE );
    // Render text (CENTERED)
    SDL_Surface *tmp = TTF_RenderText_Blended( menu->font, text, color );
    menu->texture = SDL_CreateTextureFromSurface( menu->renderer, tmp );
    const int tx = x + ((MENU_BUTTON_W - tmp->w) / 2); // Center text
    const int ty = y + ((MENU_BUTTON_H - tmp->h) / 2); // Center text
    SDL_Rect rect_text = { tx, ty, tmp->w, tmp->h };
    SDL_RenderCopy( menu->renderer, menu->texture, NULL, &rect_text);
    SDL_FreeSurface( tmp );
}

/******************************************************************************/

/**
* @brief Create a menu context
* @param renderer   game renderer
* @param font       game font
* @param wh         game window heigth
* @param ww         game window width
* @return menu context
*/
menu_t *menu_new( SDL_Renderer *renderer, TTF_Font *font, int wh, int ww)
{
    menu_t *menu = calloc( 1, sizeof (*menu) );
    menu->renderer = renderer;
    menu->font = font;
    menu->window_h = wh;
    menu->window_w = ww;
    menu->option = MENU_OPTION_1VS1;
    menu->option_changed = false;
    menu->drawn = false;

    return menu;
}

/******************************************************************************/

/**
* @brief Release menu context
* @param menu   menu context
*/
void menu_free( menu_t *menu )
{
    if ( menu != NULL )
        free( menu );
}

/******************************************************************************/

/**
* @brief Render the menu
* @param menu   menu context
*/
void menu_render( menu_t *menu )
{
    if ( !menu->drawn || menu->option_changed )
    {
        // Set menu background
        SDL_Color color = color_SDL_Color_get( COLOR_GAINSBORO );
        SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
        SDL_RenderClear( menu->renderer );

        // Gets buttons x (CENTER buttons)
        const int x = ((menu->window_w / 2) - (MENU_BUTTON_W / 2));
        // Draw 1VS1 button
        bool hover = (menu->option == MENU_OPTION_1VS1);
        _menu_button_render( menu, x, 140, hover, "1 VS 1" );
        // Draw 1VSCOM button
        hover = (menu->option == MENU_OPTION_1VSCOM);
        _menu_button_render( menu, x, 220, hover, "1 VS COM" );
        // Draw QUIT button
        hover = (menu->option == MENU_OPTION_QUIT);
        _menu_button_render( menu, x, 300, hover, "QUIT" );

        menu->drawn = true;
        menu->option_changed = false;
    }
}

/******************************************************************************/
