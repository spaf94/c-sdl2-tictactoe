/******************************************************************************/

#include "color.h"

/******************************************************************************/

#define GUI_COLORS_ARR_LEN  13

/******************************************************************************/

static struct
{
    color_t color;
    SDL_Color sdl_color;
} _colors_arr[GUI_COLORS_ARR_LEN] = {
    { COLOR_NONE,           { 0   , 0   , 0   , 0 } },
    { COLOR_BLACK,          { 0   , 0   , 0   , 0 } },
    { COLOR_WHITE,          { 255 , 255 , 255 , 0 } },
    { COLOR_RED,            { 255 , 0   , 0   , 0 } },
    { COLOR_GRAY,           { 128 , 128 , 128 , 0 } },
    { COLOR_GAINSBORO,      { 220 , 220 , 220 , 0 } },
    { COLOR_LIGHTGRAY,      { 211 , 211 , 211 , 0 } },
    { COLOR_DARKSLATEBLUE,  { 72  , 61  , 139 , 0 } },
    { COLOR_LIGHTSKYBLUE,   { 135 , 206 , 250 , 0 } },
    { COLOR_WHITESMOKE,     { 245 , 245 , 245 , 0 } },
    { COLOR_LIGHTSLATEGRAY, { 119 , 136 , 153 , 0 } },
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
