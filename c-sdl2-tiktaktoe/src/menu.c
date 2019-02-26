#include "menu.h"
#include "color.h"

#define MENU_BUTTON_W   100
#define MENU_BUTTON_H   50
#define MENU_BUTTON_B   2
#define MENU_BUTTON_BW  MENU_BUTTON_W + ( MENU_BUTTON_B * 2)
#define MENU_BUTTON_BH  MENU_BUTTON_H + ( MENU_BUTTON_B * 2)

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
        color = color_SDL_Color_get( COLOR_LIGHTSKYBLUE );
    else
        color = color_SDL_Color_get( COLOR_DARKSLATEBLUE );
    // Draw button
    SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect_button = { x, y, MENU_BUTTON_W, MENU_BUTTON_H };
    SDL_RenderFillRect( menu->renderer, &rect_button );

    // Gets text color
    if ( hover )
        color = color_SDL_Color_get( COLOR_BLACK );
    else
        color = color_SDL_Color_get( COLOR_WHITE );
    // Write text
    SDL_Surface *tmp = TTF_RenderText_Blended( menu->font, text, color );
    menu->texture = SDL_CreateTextureFromSurface( menu->renderer, tmp );

    SDL_Rect rect_text = {
        .x = x,
        .y = y + tmp->h,
        .w = tmp->w,
        .h = tmp->h
    };
    SDL_RenderCopy( menu->renderer, menu->texture, NULL, &rect_text);
    SDL_FreeSurface( tmp );
}

menu_t *menu_new( SDL_Renderer *renderer, TTF_Font *font )
{
    menu_t *menu = calloc( 1, sizeof (*menu) );
    menu->renderer = renderer;
    menu->font = font;
    menu->option = MENU_OPTION_1VS1;
    menu->option_changed = false;
    menu->drawn = false;

    return menu;
}

void menu_free( menu_t *menu )
{
    if ( menu != NULL )
        free( menu );
}

void menu_render( menu_t *menu )
{
    if ( !menu->drawn || menu->option_changed )
    {
        // Set menu background
        SDL_Color color = color_SDL_Color_get( COLOR_GAINSBORO );
        SDL_SetRenderDrawColor( menu->renderer, color.r, color.g, color.b, color.a );
        SDL_RenderClear( menu->renderer );

        // Draw 1VS1 button
        bool hover = (menu->option == MENU_OPTION_1VS1);
        _menu_button_render( menu, 270, 100, hover, "1 VS 1" );
        // Draw 1VSCOM button
        hover = (menu->option == MENU_OPTION_1VSCOM);
        _menu_button_render( menu, 270, 200, hover, "1 VS COM" );
        // Draw QUIT button
        hover = (menu->option == MENU_OPTION_QUIT);
        _menu_button_render( menu, 270, 300, hover, "QUIT" );

        menu->drawn = true;
        menu->option_changed = false;
    }
}
