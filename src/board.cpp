#include "utils/Random.hpp"
#include "board.hpp"
#include "input.hpp"

void initalizeGrid(Board &gameBoard)
{
    Candy newCandy{};

    for (int i{0}; i < MAX_ROWS; i++)
    {
        for (int j{0}; j < MAX_COLUMNS; j++)
        {
            newCandy.isMarkedDeletion = false;
            newCandy.special = None;
            CandyColor candyColor;
            do
            {
                candyColor = static_cast<CandyColor>(getRand(0, 4));
            } while ((j >= 2 && gameBoard.candyGrid[i][j - 2].color == candyColor && gameBoard.candyGrid[i][j - 1].color == candyColor) || (i >= 2 && gameBoard.candyGrid[i - 2][j].color == candyColor && gameBoard.candyGrid[i - 1][j].color == candyColor));
            newCandy.color = candyColor;
            gameBoard.candyGrid[i][j] = newCandy;
        }
    }
}
bool findAndMarkMatches (Board &gameBoard)
{
    bool isFound{};
    for (int i=0; i<MAX_ROWS; i++)
    {
        for(int j=0; j<MAX_COLUMNS-2; j++){

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if(!gameBoard.candyGrid[i][j].isMarkedDeletion && color==gameBoard.candyGrid[i][j+1].color && color==gameBoard.candyGrid[i][j+2].color){
                isFound=true;
                gameBoard.candyGrid[i][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+1].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+2].isMarkedDeletion=true;
            }
        }
    }
    for (int i=0; i<MAX_ROWS-2; i++)
    {
        for(int j=0; j<MAX_COLUMNS; j++){

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if(!gameBoard.candyGrid[i][j].isMarkedDeletion && color==gameBoard.candyGrid[i+1][j].color && color==gameBoard.candyGrid[i+2][j].color){
                isFound=true;
                gameBoard.candyGrid[i][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+1][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+2][j].isMarkedDeletion=true;
            }
        }
    }
    return isFound;
}

void applyGravity(Board &gameBoard){
    for(int i{0};i<MAX_COLUMNS;i++){
        int writeRow= MAX_ROWS-1;
        for(int readRow=writeRow;readRow>=0;readRow--){
            if(gameBoard.candyGrid[readRow][i].isMarkedDeletion==false)
            {
                swapCandies(gameBoard,readRow,i,writeRow,i);
                writeRow--;
            }
        }
    }
}

void refillBoard (Board &gameBoard)
{
    for(int i=0; i<MAX_COLUMNS; i++)
    {
        for(int j=0 ; j<MAX_ROWS; j++)
        {
            if(gameBoard.candyGrid[i][j].isMarkedDeletion == true)
            {
                gameBoard.candyGrid[i][j].color = static_cast<CandyColor>(getRand(0,4));
                gameBoard.candyGrid[i][j].isMarkedDeletion=false;
            }
        }
    }
}
int handleMatchAndRefill (Board &gameBoard)
{
    int score=0;
    while(findAndMarkMatches(gameBoard))
    {
        for(int i=0; i<MAX_ROWS; i++)
        {
            for(int j=0; j<MAX_COLUMNS; j++)
            {
                if(gameBoard.candyGrid[i][j].isMarkedDeletion == true)
                {
                    score += candypoints[gameBoard.candyGrid[i][j].color];
                }
            }
        }
        applyGravity(gameBoard);
        refillBoard(gameBoard);
    }
    return score;
}
