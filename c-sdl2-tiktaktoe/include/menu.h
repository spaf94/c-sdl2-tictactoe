#ifndef MENU_H
#define MENU_H

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

typedef enum
{
    MENU_OPTION_NONE,
    MENU_OPTION_1VS1,
    MENU_OPTION_1VSCOM,
    MENU_OPTION_QUIT
} menu_option_t;

typedef struct
{
    // SDL
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *texture;
    // Aux data
    int window_w;
    int window_h;
    // Menu
    menu_option_t option;
    bool option_changed;
    bool drawn;
} menu_t;

/******************************************************************************/

/**
* @brief Create a menu context
* @param renderer   game renderer
* @param font       game font
* @param wh         game window heigth
* @param ww         game window width
* @return menu context
*/
menu_t *menu_new( SDL_Renderer *renderer, TTF_Font *font, int wh, int ww );

/******************************************************************************/

/**
* @brief Release menu context
* @param menu   menu context
*/
void menu_free( menu_t *menu );

/******************************************************************************/

/**
* @brief Render the menu
* @param menu   menu context
*/
void menu_render( menu_t *menu );

/******************************************************************************/

#endif // MENU_H
