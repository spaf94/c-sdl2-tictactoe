/******************************************************************************/

#include "menu.h"
#include "color.h"
#include "shape.h"

/******************************************************************************/

#define MENU_BUTTONS_CNT    3

/******************************************************************************/

static struct
{
    menu_option_t option;
    char str[16];
} _menu_options[] = {
    {   MENU_OPTION_NONE    , "NONE"        },
    {   MENU_OPTION_1VS1    , "1 VS 1"      },
    {   MENU_OPTION_1VSCOM  , "1 VS COM"    },
    {   MENU_OPTION_QUIT    , "QUIT"        },
};

struct menu_t
{
    // SDL
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Rect buttons[MENU_BUTTONS_CNT];
    // Aux data
    int window_w;
    int window_h;
    // Menu
    menu_option_t option;
    bool option_changed;
    bool drawn;
};

/******************************************************************************/

/**
* @brief Gets menu option text
* @param option menu option
* @return menu option text
*/
static
const char *_menu_option_str( menu_option_t option )
{
    unsigned size = ARRAY_SIZE(_menu_options);

    for ( unsigned i = 0; i < size; i++ )
    {
        if ( _menu_options[i].option == option )
            return _menu_options[i].str;
    }

    return NULL;
}

/******************************************************************************/

/**
* @brief Initialize menu buttons position
* @param menu   game menu
*/
static
void _menu_buttons_positions_init( menu_t *menu )
{
    const int x = ((menu->window_w / 2) - (BUTTON_W / 2));

    for ( int i = 0; i < MENU_BUTTONS_CNT; i++ )
    {
        const int y = 140 + ((BUTTON_H + 30) * i);
        SDL_Rect rect = { x, y, BUTTON_W, BUTTON_H };
        menu->buttons[i] = rect;
    }
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

    // Initialize menu buttons positions
    _menu_buttons_positions_init( menu );

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

        for ( int i = 0; i < MENU_BUTTONS_CNT; i++ )
        {
            const menu_option_t option = ((menu_option_t)(i+1));
            const SDL_Rect rect = menu->buttons[i];
            const bool hover = (menu->option == option);
            const char *str = _menu_option_str( option );
            shape_button_150_50_render(
                        menu->renderer, menu->font, rect.x, rect.y, hover, str );
        }

        menu->drawn = true;
        menu->option_changed = false;
    }
}

/******************************************************************************/

/**
* @brief Changes the menu option
* @param menu   game menu
* @param down   true, when is down button
*/
void menu_option_change( menu_t *menu, bool down )
{
    if ( down )
    {
        if ( (menu->option + 1) > MENU_OPTION_QUIT )
            menu->option = MENU_OPTION_1VS1;
        else
            menu->option++;
    }
    else
    {
        if ( (menu->option - 1) < MENU_OPTION_1VS1 )
            menu->option = MENU_OPTION_QUIT;
        else
            menu->option--;
    }

    menu->option_changed = true;
}

/******************************************************************************/

/**
* @brief Gets the menu option
* @param menu   game menu
* @return menu option
*/
menu_option_t menu_option_get( menu_t *menu )
{
    return menu->option;
}

/******************************************************************************/

/**
* @brief Choose a menu option [eg. mouse click]
* @param menu   game menu
* @param x      x position clicked
* @param y      y position clicked
*/
bool menu_option_choose( menu_t *menu, int x, int y )
{
    bool ok = false;

    for ( int i = 0; i < MENU_BUTTONS_CNT; i++ )
    {
        const SDL_Rect rect = menu->buttons[i];
        const bool x_ok = ((rect.x < x) && (x < (rect.x + rect.w)));
        const bool y_ok = ((rect.y < y) && (y < (rect.y + rect.h)));

        if ( x_ok && y_ok )
        {
            const menu_option_t option = ((menu_option_t)(i + 1));
            menu->option = option;
            menu->option_changed = true;
            ok = true;
            break;
        }
    }

    return ok;
}

/******************************************************************************/

void menu_drawn_set( menu_t *menu, bool drawn )
{
    if ( menu != NULL )
        menu->drawn = drawn;
}

/******************************************************************************/
