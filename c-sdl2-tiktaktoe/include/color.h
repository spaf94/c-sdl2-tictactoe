#ifndef COLOR_H
#define COLOR_H

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

typedef enum
{
    COLOR_BLACK,
    COLOR_WHITE,
    COLOR_GAINSBORO,
    COLOR_DARKSLATEBLUE,
    COLOR_LIGHTSKYBLUE,
    // Game colors
    COLOR_GAME_BLUE,
    COLOR_GAME_LIGHTBLUE
} color_t;

/******************************************************************************/

/**
* @brief Gets SDL Color
* @param color  color id
* @return SDL color
*/
SDL_Color color_SDL_Color_get( color_t color );

/******************************************************************************/

#endif // COLOR_H
