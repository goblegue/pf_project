#include "input.hpp"
#include "board.hpp"
#include "raylib.h"
static bool getPositionOfMouse (int &row,int &coloumn, Vector2 gridOffset, int TILE_SIZE)
{
    Vector2 mouse_position=GetMousePosition();
    coloumn=(mouse_position.x - gridOffset.x)/TILE_SIZE;//  converts mouse position y to grid position
    row=(mouse_position.y - gridOffset.y)/TILE_SIZE;//  converts mouse position x to grid position
    //  checks if the position is within the grid
    if(row<0 || row>=MAX_ROWS || coloumn<0 || coloumn>=MAX_COLUMNS)
    {
        return false;
    }
    return true;
}


//  function to checking adjancy of two candies
bool isAdjacent (int row1,int coloumn1,int row2,int coloumn2)
{
    if((row1==row2 && (coloumn1==coloumn2+1 || coloumn1==coloumn2-1)) || (coloumn1==coloumn2 && (row1==row2+1 || row1==row2-1)))
    {
        return true;
    }
    return false;
}

//  handles mouse input and swaps two candies
bool handleMouseInput (Board &gameBoard,SelectedCandy &selection, Vector2 gridOffSet , int TILE_SIZE)
{
    int row1,coloumn1,row2,coloumn2;


    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(!getPositionOfMouse(row1,coloumn1, gridOffSet, TILE_SIZE))
        {
            return false ;
        }
        if(!selection.isSelected)
        {
            selection.row=row1;
            selection.coloumn=coloumn1;
            selection.isSelected=true;
        }
        else
        {
            row2=selection.row;
            coloumn2=selection.coloumn;
            selection.isSelected=false;
            if(row1==row2 && coloumn1==coloumn2)
            {
                return false;
            }
            if(isAdjacent(row1,coloumn1,row2,coloumn2))
            {
                return trySwapping(gameBoard,row1,coloumn1,row2,coloumn2);
            }
        }
    }
    return false ;
}