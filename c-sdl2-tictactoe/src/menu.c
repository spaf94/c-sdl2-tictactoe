/******************************************************************************/

#include "menu.h"
#include "color.h"

/******************************************************************************/

#define MENU_BUTTONS_CNT    3
#define MENU_BUTTON_W       150
#define MENU_BUTTON_H       50
#define MENU_BUTTON_B       3
#define MENU_BUTTON_BW      MENU_BUTTON_W + ( MENU_BUTTON_B * 2)
#define MENU_BUTTON_BH      MENU_BUTTON_H + ( MENU_BUTTON_B * 2)

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
    SDL_Texture *texture;
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
    const int x = ((menu->window_w / 2) - (MENU_BUTTON_W / 2));

    for ( int i = 0; i < MENU_BUTTONS_CNT; i++ )
    {
        const int y = 140 + ((MENU_BUTTON_H + 30) * i);
        SDL_Rect rect = { x, y, MENU_BUTTON_W, MENU_BUTTON_H };
        menu->buttons[i] = rect;
    }
}

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
    {
        if ( menu->texture != NULL )
            SDL_DestroyTexture( menu->texture );

        free( menu );
    }
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
            _menu_button_render( menu, rect.x, rect.y, hover, str );
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
void menu_option_choose( menu_t *menu, const int x, const int y )
{
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
            break;
        }
    }
}

/******************************************************************************/
