/******************************************************************************/

#include "tictactoe_gui.h"

/******************************************************************************/

// GUI Main Window
#define GUI_WIN_MAIN_TITLE  "Tic-Tac-Toe"
#define GUI_WIN_MAIN_W      640
#define GUI_WIN_MAIN_H      480

// GUI Images
#define GUI_IMG_MENU_1VS1   "../c-sdl2-tiktaktoe/img/1_menu_1vs1.png"
#define GUI_IMG_MENU_1VSCOM "../c-sdl2-tiktaktoe/img/2_menu_1vsCOM.png"
#define GUI_IMG_MENU_QUIT   "../c-sdl2-tiktaktoe/img/3_menu_quit.png"

/******************************************************************************/

/**
* @brief Creates game textures
* @param gui    GUI context
*/
static
void _tictactoe_gui_textures_create( tictactoe_gui_t *gui )
{
    SDL_Surface *surface = NULL;

    // Load menu 1vs1
    surface = IMG_Load( GUI_IMG_MENU_1VS1 );
    if( surface != NULL )
        gui->images[TTT_IMG_MENU_1VS1] = SDL_CreateTextureFromSurface( gui->ren_main, surface );

    // Load menu 1vsCOM
    surface = IMG_Load( GUI_IMG_MENU_1VSCOM );
    if( surface != NULL )
        gui->images[TTT_IMG_MENU_1VSCOM] = SDL_CreateTextureFromSurface( gui->ren_main, surface );

    // Load menu quit
    surface = IMG_Load( GUI_IMG_MENU_QUIT );
    if( surface != NULL )
        gui->images[TTT_IMG_MENU_QUIT] = SDL_CreateTextureFromSurface( gui->ren_main, surface );

    SDL_FreeSurface( surface );
}

/******************************************************************************/

/**
* @brief Creates game renderers
* @param gui    GUI context
*/
static
void _tictactoe_gui_renderers_create( tictactoe_gui_t *gui )
{
    // Main window render
    uint32_t flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gui->ren_main = SDL_CreateRenderer( gui->win_main, -1, flags );
}

/******************************************************************************/

/**
* @brief Creates game windows
* @param gui    GUI context
*/
static
void _tictactoe_gui_windows_create( tictactoe_gui_t *gui )
{
    // Main window
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
    _tictactoe_gui_renderers_create( gui );
    _tictactoe_gui_textures_create( gui );

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
        if ( gui->ren_main != NULL )
            SDL_DestroyRenderer( gui->ren_main );

        for ( unsigned i = 0; i < GUI_IMG_ARR_LEN; i++ )
        {
            if ( gui->images[i] != NULL )
                SDL_DestroyTexture( gui->images[i] );
        }

        free( gui );
    }
}

/******************************************************************************/

/**
* @brief Renderizes menu game GUI
* @param gui    GUI context
* @param img    image option
*/
void tictactoe_gui_menu_renderize( tictactoe_gui_t *gui, ttt_img_t img )
{
    const bool ok = (img != TTT_IMG_NONE);

    if ( ok )
    {
        // Draw menu image
        SDL_Rect rec_board = { .w = GUI_WIN_MAIN_W, .h = GUI_WIN_MAIN_H };
        SDL_RenderCopy( gui->ren_main, gui->images[img], NULL, &rec_board );
    }
}

/******************************************************************************/
