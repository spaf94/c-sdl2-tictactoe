/******************************************************************************/

#include "endmenu.h"
#include "color.h"

#define ENDMENU_WIDTH       (GAME_WINDOW_W / 2)
#define ENDMENU_HEIGTH      (GAME_WINDOW_H / 2)
#define ENDMENU_X           (ENDMENU_WIDTH / 2)
#define ENDMENU_Y           (ENDMENU_HEIGTH / 2)
#define ENDMENU_BORDER      5

/******************************************************************************/

struct endmenu_t
{
    // SDL
    SDL_Renderer *renderer;
    TTF_Font *font;
    // Menu
    endmenu_option_t option;
};

/******************************************************************************/

/**
* @brief Create a end menu context
* @param renderer   game renderer
* @param font       game font
* @return end menu context
*/
endmenu_t *endmenu_new( SDL_Renderer *renderer, TTF_Font *font )
{
    endmenu_t *menu = calloc(1, sizeof (*menu));
    menu->renderer = renderer;
    menu->font = font;
    menu->option = ENDMENU_OPTION_RESTART;

    return menu;
}

/******************************************************************************/

/**
* @brief Release end menu context
* @param menu   end game menu
*/
void endmenu_t_free( endmenu_t *menu )
{
    if ( menu != NULL )
    {
        free( menu );
    }
}

/******************************************************************************/

/**
* @brief Render the end menu
* @param menu   end game menu
*/
void endmenu_render( endmenu_t *menu )
{
    SDL_Color color = color_SDL_Color_get( COLOR_BLACK );
    SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_border = { ENDMENU_X, ENDMENU_Y, ENDMENU_WIDTH, ENDMENU_HEIGTH };
    SDL_RenderFillRect( menu->renderer, &rect_border );
}

/******************************************************************************/

/**
* @brief Changes the end menu option
* @param menu   end game menu
* @param down   true, when is down button
*/
void endmenu_option_change( endmenu_t *menu, bool down )
{

}

/******************************************************************************/

/**
* @brief Gets the end menu option
* @param menu   end game menu
* @return end menu option
*/
endmenu_option_t endmenu_option_get( endmenu_t *menu )
{
    if ( menu != NULL )
        return menu->option;

    return ENDMENU_OPTION_NONE;
}

/******************************************************************************/

/**
* @brief Choose a end menu option [eg. mouse click]
* @param menu   end game menu
* @param x      x position clicked
* @param y      y position clicked
*/
void endmenu_option_choose( endmenu_t *menu, const int x, const int y )
{

}

/******************************************************************************/
