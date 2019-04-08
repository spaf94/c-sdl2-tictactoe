/******************************************************************************/

#include "shape.h"

/******************************************************************************/

#define BUTTON_B       3
#define BUTTON_BW      BUTTON_W + ( BUTTON_B * 2)
#define BUTTON_BH      BUTTON_H + ( BUTTON_B * 2)

/******************************************************************************/

/**
* @brief Renders a line with a specified thickness
* @param renderer   renderer
* @param point1     point 1
* @param point2     point 2
* @param thickness  line thickness
* @param color_id   color id
*/
void shape_line_thickness_render(
        SDL_Renderer *renderer,
        SDL_Point *point1,
        SDL_Point *point2,
        int thickness,
        color_t color_id )
{
    int p1x = 0;
    int p2x = 0;

    if ( color_id != COLOR_NONE )
    {
        // Gets line color
        SDL_Color color = color_SDL_Color_get( color_id );
        SDL_SetRenderDrawColor ( renderer, color.r, color.g, color.b, color.a );
    }

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
    // Line 1
    SDL_Point pa1 = { 0 };
    pa1.x = data->x - (data->w / 2);
    pa1.y = data->y - (data->h / 2);
    SDL_Point pb1 = { 0 };
    pb1.x = data->x + (data->w / 2);
    pb1.y = data->y + (data->h / 2);
    shape_line_thickness_render(
                renderer, &pa1, &pb1, thickness, color_id );

    // Line 2
    SDL_Point pa2 = { 0 };
    pa2.x = data->x + (data->w / 2);
    pa2.y = data->y - (data->h / 2);
    SDL_Point pb2 = { 0 };
    pb2.x = data->x - (data->w / 2);
    pb2.y = data->y + (data->h / 2);
    shape_line_thickness_render(
                renderer, &pa2, &pb2, thickness, color_id );
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

        shape_line_thickness_render(
                    renderer, &point1, &point2, thickness, COLOR_NONE );

        point2.x = point1.x;
        point2.y = point1.y;
    }

    point1.x = center->x + (int)(radius * cos(0));
    point1.y = center->y - (int)(radius * sin(0));
    shape_line_thickness_render(
                renderer, &point1, &point2, thickness, COLOR_NONE );
}

/******************************************************************************/

/**
* @brief Render a button
* @param renderer   game renderer
* @param font       game font
* @param x          button x position
* @param y          button y position
* @param hover      true, to hover button
* @param text       button text
*/
void shape_button_150_50_render(
        SDL_Renderer *renderer,
        TTF_Font *font,
        int x,
        int y,
        bool hover,
        const char *text )
{
    shape_button_render(
                renderer,
                font,
                x,
                y,
                BUTTON_W,
                BUTTON_H,
                hover,
                text );
}

/******************************************************************************/

/**
* @brief Render a button
* @param renderer   game renderer
* @param font       game font
* @param x          button x position
* @param y          button y position
* @param w          button width
* @param h          button height
* @param hover      true, to hover button
* @param text       button text
*/
void shape_button_render(
        SDL_Renderer *renderer,
        TTF_Font *font,
        int x,
        int y,
        int w,
        int h,
        bool hover,
        const char *text )
{
    // Border position
    const int bx = x - BUTTON_B;
    const int by = y - BUTTON_B;
    const int bw = w + ( BUTTON_B * 2);
    const int bh = h + ( BUTTON_B * 2);
    // Draw border
    SDL_Color color = color_SDL_Color_get( COLOR_BLACK );
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_border = { bx, by, bw, bh };
    SDL_RenderFillRect( renderer, &rect_border );

    // Gets button color
    if ( hover )
        color = color_SDL_Color_get( COLOR_GAME_LIGHTBLUE );
    else
        color = color_SDL_Color_get( COLOR_GAME_BLUE );
    // Draw button
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_button = { x, y, w, h };
    SDL_RenderFillRect( renderer, &rect_button );

    // Gets text color
    if ( hover )
        color = color_SDL_Color_get( COLOR_BLACK );
    else
        color = color_SDL_Color_get( COLOR_WHITE );
    // Render text (CENTERED)
    SDL_Surface *tmp = TTF_RenderText_Blended( font, text, color );
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, tmp );
    const int tx = x + ((w - tmp->w) / 2); // Center text
    const int ty = y + ((h - tmp->h) / 2); // Center text
    SDL_Rect rect_text = { tx, ty, tmp->w, tmp->h };
    SDL_RenderCopy( renderer, texture, NULL, &rect_text);
    SDL_FreeSurface( tmp );
    SDL_DestroyTexture( texture );
}

/******************************************************************************/
