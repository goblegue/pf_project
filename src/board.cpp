#include "utils/Random.hpp"
#include "board.hpp"
#include "input.hpp"
// points associated with each candy color
void initializeGrid(Board &gameBoard)
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
//function for swapping candies
void swapCandies (Board &gameBoard,int row1,int column1,int row2,int column2)
{
    Candy temp = gameBoard.candyGrid[row1][column1];
    gameBoard.candyGrid[row1][column1] = gameBoard.candyGrid[row2][column2];
    gameBoard.candyGrid[row2][column2] = temp;
}
//function to check if candy is part of match
bool isPartOfMatch (Board &gameBoard, int row, int column)
{
    CandyColor color = gameBoard.candyGrid[row][column].color;
    if(gameBoard.candyGrid[row][column].isMarkedDeletion == true)
    {
        return false;
    }
    //checks horizontall match
    int horizontalCount=1;
    for(int i=column-1; i>=0 && gameBoard.candyGrid[row][i].color==color; i--)
    {
        horizontalCount++;
    }
    for(int i=column+1; i<MAX_COLUMNS && gameBoard.candyGrid[row][i].color==color; i++)
    {
        horizontalCount++;
    }
    if(horizontalCount>=3)
    {
        return true;
    }
    //checks vertical match
    int verticalCount=1;
    for(int i=row-1; i>=0 && gameBoard.candyGrid[i][column].color==color; i--)
    {
        verticalCount++;
    }
    for(int i=row+1; i<MAX_ROWS && gameBoard.candyGrid[i][column].color==color; i++)
    {
        verticalCount++;
    }
    if(verticalCount>=3)
    {
        return true;
    }
    return false;
}
// function to try swapping two candies
bool trySwapping (Board &gameBoard, int row1, int column1,int row2, int column2)
{
    swapCandies(gameBoard, row1, column1, row2, column2);
    if(isPartOfMatch(gameBoard, row1, column1) || isPartOfMatch(gameBoard, row2, column2))
    {
        return true;
    }
    else
    {
        swapCandies(gameBoard, row1, column1, row2, column2); //swap back if no match
        return false;
    }
}

// function to find and mark matches on the board
bool findAndMarkMatches (Board &gameBoard)
{
    bool isFound{};
    // checks horizontally 3 plain candies
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
    //checks vertically 3 plain candies
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
// apply gravity
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
// refills board
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
//handle matches and refills
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
