/******************************************************************************/

#include "color.h"

/******************************************************************************/

#define GUI_COLORS_ARR_LEN  8

/******************************************************************************/

static struct
{
    color_t color;
    SDL_Color sdl_color;
} _colors_arr[GUI_COLORS_ARR_LEN] = {
    { COLOR_BLACK,          { 0   , 0   , 0   , 0 } },
    { COLOR_WHITE,          { 255 , 255 , 255 , 0 } },
    { COLOR_RED,            { 255 , 0   , 0   , 0 } },
    { COLOR_GAINSBORO,      { 220 , 220 , 220 , 0 } },
    { COLOR_DARKSLATEBLUE,  { 72  , 61  , 139 , 0 } },
    { COLOR_LIGHTSKYBLUE,   { 135 , 206 , 250 , 0 } },
    // Game colors
    { COLOR_GAME_BLUE,      { 48  , 78  , 98  , 0 } },
    { COLOR_GAME_LIGHTBLUE, { 114 , 159 , 207 , 0 } },
};

/******************************************************************************/

/**
* @brief Gets SDL Color
* @param color  color id
* @return SDL color
*/
SDL_Color color_SDL_Color_get( color_t color )
{
    for ( unsigned i = 0; i < GUI_COLORS_ARR_LEN; i++ )
    {
        if ( _colors_arr[i].color == color )
            return (_colors_arr[i].sdl_color);
    }

    return _colors_arr[0].sdl_color;
}

/******************************************************************************/
