#include "input.hpp"
#include "board.hpp"
#include "raylib.h"

swappedCandies swappedcandies; // global variable to keep track of swapped candies

 bool getPositionOfMouse (int &row,int &column, Vector2 gridOffset, int TILE_SIZE)
{
    Vector2 mouse_position=GetMousePosition();
    column=(mouse_position.x - gridOffset.x)/TILE_SIZE;//  converts mouse position y to grid position
    row=(mouse_position.y - gridOffset.y)/TILE_SIZE;//  converts mouse position x to grid position
    //  checks if the position is within the grid
    if(row<0 || row>=MAX_ROWS || column<0 || column>=MAX_COLUMNS)
    {
        return false;
    }
    return true;
}


//  function to checking adjancy of two candies
bool isAdjacent (int row1,int column1,int row2,int column2)
{
    if((row1==row2 && (column1==column2+1 || column1==column2-1)) || (column1==column2 && (row1==row2+1 || row1==row2-1)))
    {
        return true;
    }
    return false;
}

//  handles mouse input and swaps two candies
bool handleMouseInput (Board &gameBoard,SelectedCandy &selection, Vector2 gridOffSet , const int TILE_SIZE)
{
    int row1,column1,row2,column2;

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(!getPositionOfMouse(row1,column1, gridOffSet, TILE_SIZE))
        {
            return false ;
        }
        if(!selection.isSelected)
        {
            selection.row=row1;
            selection.column=column1;
            selection.isSelected=true;
           
        }
        else
        {
            row2=selection.row;
            column2=selection.column;
            selection.isSelected=false;
             //to keep track of first candy
            swappedcandies.candy1row=selection.row;
            swappedcandies.candy1column=selection.column;
            swappedcandies.candy2row=row1;
            swappedcandies.candy2column=column1;
            if(row1==row2 && column1==column2)
            {
                return false;
            }
            if(isAdjacent(row1,column1,row2,column2))
            {
                return trySwapping(gameBoard,row1,column1,row2,column2);
            }
        }
    }
    return false ;
}

swappedCandies getSwappedCandies(){
    return swappedcandies;
}

