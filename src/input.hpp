#ifndef INPUT_HPP
#define INPUT_HPP

#include "raylib.h"

// Forward declaration
struct Board;

//struct to keep track of selected candy
struct SelectedCandy
{
    int row;
    int coloumn;
    bool isSelected;
};
//struct to keep track of swapped candies
struct swappedCandies
{
    int candy1row;
    int candy1column;
    int candy2row;
    int candy2column;
};
//function to swap candy
void swapCandies (Board &gameBoard,int row1,int coloumn1,int row2,int coloumn2);

//function to check if two candies are adjacent
bool isAdjacent (int row1,int coloumn1,int row2,int coloumn2);

//function to handle mouse input
bool handleMouseInput (Board &gameBoard,SelectedCandy &selection, Vector2 gridOffSet, int TILE_SIZE);

swappedCandies getSwappedCandies();

#endif
