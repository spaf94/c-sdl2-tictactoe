#ifndef TICTACTOE_GUI_H
#define TICTACTOE_GUI_H 

/******************************************************************************/

#include "internal.h"

/******************************************************************************/

typedef struct tictactoe_gui
{
    // Windows
    SDL_Window *win_main;
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

#endif // TICTACTOE_GUI_H
