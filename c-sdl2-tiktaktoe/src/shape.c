/******************************************************************************/

#include "shape.h"

/******************************************************************************/

/**
* @brief Renders a line with a specified thickness
* @param renderer   renderer
* @param point1     point 1
* @param point2     point 2
* @param thickness  line thickness
*/
static
void _shape_line_thickness_render(
        SDL_Renderer *renderer,
        SDL_Point *point1,
        SDL_Point *point2,
        int thickness )
{
    int p1x = 0;
    int p2x = 0;

    for ( int i = 0; i < thickness; i++ )
    {
        p1x = point1->x + i;
        p2x = point2->x + i;
        SDL_RenderDrawLine ( renderer, p1x, point1->y, p2x, point2->y );
    }
}

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
        color_t color_id )
{
    // Gets X color
    SDL_Color color = color_SDL_Color_get( color_id );
    SDL_SetRenderDrawColor ( renderer, color.r, color.g, color.b, color.a );

    // Line 1
    SDL_Point pa1 = { 0 };
    pa1.x = data->x - (data->w / 2);
    pa1.y = data->y - (data->h / 2);
    SDL_Point pb1 = { 0 };
    pb1.x = data->x + (data->w / 2);
    pb1.y = data->y + (data->h / 2);
    _shape_line_thickness_render( renderer, &pa1, &pb1, thickness );

    // Line 2
    SDL_Point pa2 = { 0 };
    pa2.x = data->x + (data->w / 2);
    pa2.y = data->y - (data->h / 2);
    SDL_Point pb2 = { 0 };
    pb2.x = data->x - (data->w / 2);
    pb2.y = data->y + (data->h / 2);
    _shape_line_thickness_render( renderer, &pa2, &pb2, thickness );
}

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
        color_t color_id )
{
    SDL_Point point1 = { 0 };
    SDL_Point point2 = { (center->x + radius), center->y };
    double step = (M_PI * 2) / 50;

    SDL_Color color = color_SDL_Color_get( color_id );
    SDL_SetRenderDrawColor ( renderer, color.r, color.g, color.b, color.a );

    for ( double theta = 0; theta <= (M_PI * 2); theta += step )
    {
        point1.x = center->x + (int)(radius * cos ( theta ));
        point1.y = center->y - (int)(radius * sin ( theta ));

        _shape_line_thickness_render( renderer, &point1, &point2, thickness);

        point2.x = point1.x;
        point2.y = point1.y;
    }

    point1.x = center->x + (int)(radius * cos(0));
    point1.y = center->y - (int)(radius * sin(0));
    _shape_line_thickness_render( renderer, &point1, &point2, thickness);
}

/******************************************************************************/
