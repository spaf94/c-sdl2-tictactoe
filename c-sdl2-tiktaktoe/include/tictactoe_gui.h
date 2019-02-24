#ifndef TICTACTOE_GUI_H
#define TICTACTOE_GUI_H 

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

#define GUI_IMG_ARR_LEN 4

/******************************************************************************/

typedef enum tictactoe_images
{
    TTT_IMG_NONE        = -1,
    TTT_IMG_MENU_1VS1   = 0,
    TTT_IMG_MENU_1VSCOM = 1,
    TTT_IMG_MENU_QUIT   = 2
} ttt_img_t;

typedef struct tictactoe_gui
{
    // Windows
    SDL_Window *win_main;
    // Renderers
    SDL_Renderer *ren_main;
    // Images
    SDL_Texture *images[GUI_IMG_ARR_LEN];
} tictactoe_gui_t;

/******************************************************************************/

/**
* Creates a new tictactoe GUI
*/
tictactoe_gui_t *tictactoe_gui_new();

/******************************************************************************/

/**
* Releases tictactoe GUI resources
* @param gui    tictactoe GUI context
*/
void tictactoe_gui_free( tictactoe_gui_t *gui );

/******************************************************************************/

/**
* @brief Renderizes menu game GUI
* @param gui    GUI context
* @param img    image option
*/
void tictactoe_gui_menu_renderize( tictactoe_gui_t *gui, ttt_img_t img );

/******************************************************************************/

#endif // TICTACTOE_GUI_H
