#ifndef INPUT_HPP
#define INPUT_HPP

#include "board.hpp"
#include "raylib.h"
//struct to keep track of selected candy
struct SelectedCandy
{
    int row;
    int column;
    bool isSelected;
};


//function to check if two candies are adjacent
bool isAdjacent (int row1,int column1,int row2,int column2);

//function to handle mouse input
bool handleMouseInput (Board &gameBoard,SelectedCandy &selection, Vector2 gridOffSet, int TILE_SIZE);

#endif
