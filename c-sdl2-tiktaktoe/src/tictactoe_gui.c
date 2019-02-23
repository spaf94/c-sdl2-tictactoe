/******************************************************************************/

#include "tictactoe_gui.h"

/******************************************************************************/

// GUI Main Window
#define GUI_WIN_MAIN_TITLE  "Tic-Tac-Toe"
#define GUI_WIN_MAIN_W      640
#define GUI_WIN_MAIN_H      480

/******************************************************************************/

/**
* @brief Creates game windows
* @param gui    GUI context
*/
static
void _tictactoe_gui_windows_create( tictactoe_gui_t *gui )
{
    gui->win_main = SDL_CreateWindow( GUI_WIN_MAIN_TITLE,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      GUI_WIN_MAIN_W,
                                      GUI_WIN_MAIN_H,
                                      0 );
}

/******************************************************************************/

/**
* @brief Creates a new tictactoe GUI
*/
tictactoe_gui_t *tictactoe_gui_new()
{
    tictactoe_gui_t *gui = calloc( 1, sizeof (*gui) );
    _tictactoe_gui_windows_create( gui );

    return gui;
}

/******************************************************************************/

/**
* @brief Releases tictactoe GUI resources
* @param gui    tictactoe GUI context
*/
void tictactoe_gui_free( tictactoe_gui_t *gui )
{
    if ( gui != NULL )
    {
        if ( gui->win_main != NULL )
            SDL_DestroyWindow( gui->win_main );

        free( gui );
    }
}

/******************************************************************************/
