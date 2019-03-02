#ifndef SHAPE_H
#define SHAPE_H

/******************************************************************************/

#include "internal.h"
#include "color.h"

/******************************************************************************/

/**
* @brief Renders a X shape
* @param renderer   renderer
* @param data       data: h = heigth, w = width, x = center x, y = center y
* @param thickness  X thickness
* @param color_id   color id
*/
void shape_X_render(
        SDL_Renderer *renderer,
        SDL_Rect *data,
        int thickness,
        color_t color_id );

/******************************************************************************/

/**
* @brief Render a circle shape
* @param renderer   renderer
* @param center     center: x = center x, y = center y
* @param radius     radius
* @param thickness  circle thickness
* @param color_id   color id
*/
void shape_circle_render(
        SDL_Renderer *renderer,
        SDL_Point *center,
        int radius,
        int thickness,
        color_t color_id );

/******************************************************************************/

#endif // SHAPE_H
