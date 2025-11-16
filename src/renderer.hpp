#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include "board.hpp"
#include "input.hpp"
const int MAXCANDYCOLORS{6};//red,yellow,green,blue,orange,bomb

const float TILE_SIZE{50};
struct Renderer{
    Texture2D candyTexture; // candy sprite sheet
    Rectangle candySourceRecs[MAXCANDYCOLORS];
    Vector2 gridOffset; // distance from top-left corner to grid start
};

Renderer initRenderer(int windowWidth, int windowHeight); 
void unloadRenderer(Renderer &renderer);
void drawBoard(const Renderer &renderer, const Board &gameBoard,const SelectedCandy &selection);

#endif