#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include "../grid/board.hpp"
#include "../input/input.hpp"
#include "../colors/customColourPalette.hpp"

const int MAXCANDYCOLORS{6};//red,yellow,green,blue,orange,bomb




const int TILE_SIZE{64};
const int MAXMENUBUTTONS{4}; // newgame , continue, settings , exit

enum ButtonAction
{
    ACTION_NEW_GAME,
    ACTION_LOAD_GAME,
    ACTION_SETTINGS,
    ACTION_EXIT
};

struct Button
{
Rectangle sourceRec;
Rectangle bounds;
char label[32];
bool isClicked;
ButtonAction action;
};
struct Renderer{
    Texture2D candyTexture; // candy sprite sheet
    Texture2D buttonTexture; // button sprite sheet
    Button menuButtons[MAXMENUBUTTONS];
    Rectangle plainCandySourceRecs[MAXCANDYCOLORS];
    Rectangle wrappedCandySourceRecs[MAXCANDYCOLORS-1];
    Rectangle horiStripedCandySourceRecs[MAXCANDYCOLORS-1];
    Rectangle vertStripedCandySourceRecs[MAXCANDYCOLORS-1];
    Vector2 gridOffset; // distance from top-left corner to grid start
};



Renderer initRenderer(int windowWidth, int windowHeight); 
void unloadRenderer(Renderer &renderer);
void drawBoard(const Renderer &renderer, const Board &gameBoard,const SelectedCandy &selection);
void drawButton(const Renderer &renderer, const Button &btn);
void drawMenu(const Renderer &renderer);



#endif