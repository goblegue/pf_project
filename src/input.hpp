#ifndef INPUT_HPP
#define INPUT_HPP

#include "board.hpp"
#include "raylib.h"
//struct to keep track of selected candy
struct SelectedCandy
{
    int row;
    int coloumn;
    bool isSelected;
};
//function to swap candy
void swapCandies (Board &gameBoard,int row1,int coloumn1,int row2,int coloumn2);

//function to check if two candies are adjacent
bool isAdjacent (int row1,int coloumn1,int row2,int coloumn2);

//function to handle mouse input
void HandleMouseInput (Board &gameBoard,SelectedCandy &selection, int offsetX, int offsetY);

#endif
