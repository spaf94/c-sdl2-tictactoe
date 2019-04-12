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

typedef struct menu_t menu_t;

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

/**
* @brief Changes the menu option
* @param menu   game menu
* @param down   true, when is down button
*/
void menu_option_change( menu_t *menu, bool down );

/******************************************************************************/

/**
* @brief Gets the menu option
* @param menu   game menu
* @return menu option
*/
menu_option_t menu_option_get( menu_t *menu );

/******************************************************************************/

/**
* @brief Choose a menu option [eg. mouse click]
* @param menu   game menu
* @param x      x position clicked
* @param y      y position clicked
* @return true, if some option choosed
*/
bool menu_option_choose( menu_t *menu, const int x, const int y );

/******************************************************************************/

void menu_drawn_set( menu_t *menu, bool drawn );

/******************************************************************************/

#endif // MENU_H
