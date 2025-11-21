#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include "board.hpp"
#include "input.hpp"
const int MAXCANDYCOLORS{6};//red,yellow,green,blue,orange,bomb




const int TILE_SIZE{64};
struct Renderer{
    Texture2D candyTexture; // candy sprite sheet
    Rectangle plainCandySourceRecs[MAXCANDYCOLORS];
    Rectangle wrappedCandySourceRecs[MAXCANDYCOLORS-1];
    Rectangle horiStripedCandySourceRecs[MAXCANDYCOLORS-1];
    Rectangle vertStripedCandySourceRecs[MAXCANDYCOLORS-1];
    Vector2 gridOffset; // distance from top-left corner to grid start
};

Renderer initRenderer(int windowWidth, int windowHeight); 
void unloadRenderer(Renderer &renderer);
void drawBoard(const Renderer &renderer, const Board &gameBoard,const SelectedCandy &selection);

#endif