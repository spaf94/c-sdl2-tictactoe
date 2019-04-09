/******************************************************************************/

#include "endmenu.h"
#include "color.h"
#include "shape.h"

#define ENDMENU_WIDTH           (GAME_WINDOW_W / 2)
#define ENDMENU_HEIGTH          (GAME_WINDOW_H / 2)
#define ENDMENU_X               (ENDMENU_WIDTH / 2)
#define ENDMENU_Y               (ENDMENU_HEIGTH / 2)
#define ENDMENU_BORDER          5
#define ENDMENU_BUTTONS_CNT     2
#define ENDMENU_BUTTON_W        115
#define ENDMENU_BUTTON_H        50

/******************************************************************************/

static struct
{
    endmenu_option_t option;
    char str[16];
} _endmenu_options[] = {
    {   ENDMENU_OPTION_NONE,    "NONE"      },
    {   ENDMENU_OPTION_RESTART, "RESTART"   },
    {   ENDMENU_OPTION_QUIT,    "QUIT"      },
};

struct endmenu_t
{
    // SDL
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Rect buttons[ENDMENU_BUTTONS_CNT];
    // Menu
    endmenu_option_t option;
};

/******************************************************************************/

/**
* @brief Gets menu option text
* @param option menu option
* @return menu option text
*/
static
const char *_endmenu_option_str( endmenu_option_t option )
{
    unsigned size = ARRAY_SIZE(_endmenu_options);

    for ( unsigned i = 0; i < size; i++ )
    {
        if ( _endmenu_options[i].option == option )
            return _endmenu_options[i].str;
    }

    return NULL;
}

/******************************************************************************/

static
void _endmenu_buttons_positions_init( SDL_Rect *buttons )
{
    const int y = (ENDMENU_HEIGTH - (ENDMENU_BUTTON_H / 2));

    for ( int i = 0; i < ENDMENU_BUTTONS_CNT; i++ )
    {
        const int x0 = (30 + (ENDMENU_WIDTH - (ENDMENU_WIDTH / 2)));
        const int x = x0 + ((ENDMENU_BUTTON_W + 30) * i);
        SDL_Rect rect = { x, y, ENDMENU_BUTTON_W, ENDMENU_BUTTON_H };
        buttons[i] = rect;
    }
}

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

    // Init buttons positions
    _endmenu_buttons_positions_init( menu->buttons );

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
    SDL_Log( "endmenu_render \n" );

    // Draw menu border
    SDL_Color color = color_SDL_Color_get( COLOR_BLACK );
    SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_border = { ENDMENU_X, ENDMENU_Y, ENDMENU_WIDTH, ENDMENU_HEIGTH };
    SDL_RenderFillRect( menu->renderer, &rect_border );

    // Draw menu background
    const int x = ENDMENU_X + ENDMENU_BORDER;
    const int y = ENDMENU_Y + ENDMENU_BORDER;
    const int w = ENDMENU_WIDTH - (ENDMENU_BORDER * 2);
    const int h = ENDMENU_HEIGTH - (ENDMENU_BORDER * 2);
    color = color_SDL_Color_get( COLOR_WHITESMOKE );
    SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_background = { x, y, w, h };
    SDL_RenderFillRect( menu->renderer, &rect_background );

    // Draw buttons
    for ( int i = 0; i < ENDMENU_BUTTONS_CNT; i++ )
    {
        const endmenu_option_t option = ((endmenu_option_t)(i+1));
        const bool hover = (menu->option == option);
        const char *text = _endmenu_option_str( option );
        const SDL_Rect rect = menu->buttons[i];

        shape_button_render(
                    menu->renderer,
                    menu->font,
                    rect.x,
                    rect.y,
                    ENDMENU_BUTTON_W,
                    ENDMENU_BUTTON_H,
                    hover,
                    text );
    }
}

/******************************************************************************/

/**
* @brief Changes the end menu option
* @param menu   end game menu
* @param right   true, when is right button
*/
void endmenu_option_change( endmenu_t *menu, bool right )
{
    if ( right )
    {
        if ( menu->option == ENDMENU_OPTION_RESTART )
            menu->option = ENDMENU_OPTION_QUIT;
        else
            menu->option = ENDMENU_OPTION_RESTART;
    }
    else
    {
        if ( menu->option == ENDMENU_OPTION_QUIT )
            menu->option = ENDMENU_OPTION_RESTART;
        else
            menu->option = ENDMENU_OPTION_QUIT;
    }
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
