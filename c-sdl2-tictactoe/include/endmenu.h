#ifndef ENDMENU_H
#define ENDMENU_H

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

typedef enum
{
    ENDMENU_OPTION_NONE,
    ENDMENU_OPTION_RESTART,
    ENDMENU_OPTION_QUIT
} endmenu_option_t;

typedef struct endmenu_t endmenu_t;

/******************************************************************************/

/**
* @brief Create a end menu context
* @param renderer   game renderer
* @param font       game font
* @return end menu context
*/
endmenu_t *endmenu_new( SDL_Renderer *renderer, TTF_Font *font );

/******************************************************************************/

/**
* @brief Release end menu context
* @param menu   end game menu
*/
void endmenu_free( endmenu_t *menu );

/******************************************************************************/

/**
* @brief Render the end menu
* @param menu   end game menu
*/
void endmenu_render( endmenu_t *menu );

/******************************************************************************/

/**
* @brief Changes the end menu option
* @param menu   end game menu
* @param down   true, when is right button
*/
void endmenu_option_change( endmenu_t *menu, bool right );

/******************************************************************************/

/**
* @brief Gets the end menu option
* @param menu   end game menu
* @return end menu option
*/
endmenu_option_t endmenu_option_get( endmenu_t *menu );

/******************************************************************************/

/**
* @brief Choose a end menu option [eg. mouse click]
* @param menu   end game menu
* @param x      x position clicked
* @param y      y position clicked
*/
void endmenu_option_choose( endmenu_t *menu, const int x, const int y );

/******************************************************************************/

#endif // ENDMENU_H
