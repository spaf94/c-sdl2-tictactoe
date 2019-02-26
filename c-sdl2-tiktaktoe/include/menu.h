#ifndef MENU_H
#define MENU_H

#include "internal.h"

typedef enum
{
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
    // Menu
    menu_option_t option;
    bool option_changed;
    bool drawn;
} menu_t;

menu_t *menu_new( SDL_Renderer *renderer, TTF_Font *font );

void menu_free( menu_t *menu );

void menu_render( menu_t *menu );

#endif // MENU_H
