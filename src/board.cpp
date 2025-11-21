#include "utils/Random.hpp"
#include "board.hpp"
#include "input.hpp"
// points associated with each candy color
void initalizeGrid(Board &gameBoard)
{
    Candy newCandy{};

    for (int i{0}; i < MAX_ROWS; i++)
    {
        for (int j{0}; j < MAX_COLUMNS; j++)
        {
            newCandy.isMarkedDeletion = false;
            newCandy.type = Plain;
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
void swapCandies (Board &gameBoard,int row1,int coloumn1,int row2,int coloumn2)
{
    Candy temp = gameBoard.candyGrid[row1][coloumn1];
    gameBoard.candyGrid[row1][coloumn1] = gameBoard.candyGrid[row2][coloumn2];
    gameBoard.candyGrid[row2][coloumn2] = temp;
}
//function to check if candy is part of match

bool checkHorizontalMatch(Board &gameBoard, int row, int coloumn){
    CandyColor color = gameBoard.candyGrid[row][coloumn].color;
    int count=1;
    for(int i=coloumn-1; i>=0 && gameBoard.candyGrid[row][i].color==color; i--)
    {
        count++;
    }
    for(int i=coloumn+1; i<MAX_COLUMNS && gameBoard.candyGrid[row][i].color==color; i++)
    {
        count++;
    }
    return count>=3;
}

bool checkVerticalMatch(Board &gameBoard, int row, int coloumn){
    CandyColor color = gameBoard.candyGrid[row][coloumn].color;
    int count=1;
    for(int i=row-1; i>=0 && gameBoard.candyGrid[i][coloumn].color==color; i--)
    {
        count++;
    }
    for(int i=row+1; i<MAX_ROWS && gameBoard.candyGrid[i][coloumn].color==color; i++)
    {
        count++;
    }
    return count>=3;
}

bool isPartOfMatch (Board &gameBoard, int row, int coloumn)
{
    return checkHorizontalMatch(gameBoard, row, coloumn) || checkVerticalMatch(gameBoard, row, coloumn);
}
// function to try swapping two candies
bool trySwapping (Board &gameBoard, int row1, int coloumn1,int row2, int coloumn2)
{
    swapCandies(gameBoard, row1, coloumn1, row2, coloumn2);
    if(isPartOfMatch(gameBoard, row1, coloumn1) || isPartOfMatch(gameBoard, row2, coloumn2))
    {
        return true;
    }
    else
    {
        swapCandies(gameBoard, row1, coloumn1, row2, coloumn2); //swap back if no match
        return false;
    }
}

// function to find and mark three matches on the board
bool findAndMarkThreeMatches (Board &gameBoard)
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
//function to check and mark four matches on board
bool findAndMarkFourMatches (Board &gameBoard)
{
     bool isFound{};
    // checks horizontally 4 plain candies
    for (int i=0; i<MAX_ROWS; i++)
    {
        for(int j=0; j<MAX_COLUMNS-3; j++){

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if(!gameBoard.candyGrid[i][j].isMarkedDeletion && color==gameBoard.candyGrid[i][j+1].color && color==gameBoard.candyGrid[i][j+2].color && color==gameBoard.candyGrid[i][j+3].color)
            {
                isFound=true;
                gameBoard.candyGrid[i][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+1].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+2].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+3].isMarkedDeletion=true;
            }

        }
    }
    //checks vertically 4 plain candies
    for (int i=0; i<MAX_ROWS-3; i++)
    {
        for(int j=0; j<MAX_COLUMNS; j++){

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if(!gameBoard.candyGrid[i][j].isMarkedDeletion && color==gameBoard.candyGrid[i+1][j].color && color==gameBoard.candyGrid[i+2][j].color && color==gameBoard.candyGrid[i+3][j].color)
            {
                isFound=true;
                gameBoard.candyGrid[i][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+1][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+2][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+3][j].isMarkedDeletion=true;
            }
        }
    }
    return isFound;
}
//function to check and mark five matches on board
bool findAndMarkFiveMatches (Board &gameBoard)
{
     bool isFound{};
    // checks horizontally 5 plain candies
    for (int i=0; i<MAX_ROWS; i++)
    {
        for(int j=0; j<MAX_COLUMNS-4; j++){

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if(!gameBoard.candyGrid[i][j].isMarkedDeletion && color==gameBoard.candyGrid[i][j+1].color && color==gameBoard.candyGrid[i][j+2].color && color==gameBoard.candyGrid[i][j+3].color && color==gameBoard.candyGrid[i][j+4].color)
            {
                isFound=true;
                gameBoard.candyGrid[i][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+1].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+2].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+3].isMarkedDeletion=true;
                gameBoard.candyGrid[i][j+4].isMarkedDeletion=true;
            }

        }
    }
    //checks vertically 5 plain candies
    for (int i=0; i<MAX_ROWS-4; i++)
    {
        for(int j=0; j<MAX_COLUMNS; j++){

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if(!gameBoard.candyGrid[i][j].isMarkedDeletion && color==gameBoard.candyGrid[i+1][j].color && color==gameBoard.candyGrid[i+2][j].color && color==gameBoard.candyGrid[i+3][j].color && color==gameBoard.candyGrid[i+4][j].color)
            {
                isFound=true;
                gameBoard.candyGrid[i][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+1][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+2][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+3][j].isMarkedDeletion=true;
                gameBoard.candyGrid[i+4][j].isMarkedDeletion=true;
            }
        }
    }
    return isFound;
}

//function to check and mark L or T shape matches on board
bool findAndMarkLorTshapeMatches (Board &gameBoard, swappedCandies swappedcandies)
{
     bool isFound{};
//       CandyColor color1 = gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].color;
//        CandyColor color2 = gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].color;
       
//      if(gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion == true || gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion == true)
//     {
//         return false;
//     }
//    if(//check left T shape for first swapped candy
//        (swappedcandies.candy1row>=1 && swappedcandies.candy1row<=7 && swappedcandies.candy1column>=0 && swappedcandies.candy1column<=6 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+2].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+2].isMarkedDeletion=true;
//     }
//     else if (//check right T shape for first swapped candy
//        (swappedcandies.candy1row>=1 && swappedcandies.candy1row<=7 && swappedcandies.candy1column>=2 && swappedcandies.candy1column<=8 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-2].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-2].isMarkedDeletion=true;
//     }
//     else if (//check up T shape for first swapped candy
//         (swappedcandies.candy1row>=0 && swappedcandies.candy1row<=6 && swappedcandies.candy1column>=1 && swappedcandies.candy1column<=7 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+2][swappedcandies.candy1column].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+2][swappedcandies.candy1column].isMarkedDeletion=true;
//     }
//     else if (//check down T shape for first swapped candy
//         (swappedcandies.candy1row>=2 && swappedcandies.candy1row<=8 && swappedcandies.candy1column>=1 && swappedcandies.candy1column<=7 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-2][swappedcandies.candy1column].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-2][swappedcandies.candy1column].isMarkedDeletion=true;
//     }


//    //checks for second swapped candy
//     else if(//check left T shape for second swapped candy
//        (swappedcandies.candy2row>=1 && swappedcandies.candy2row<=7 && swappedcandies.candy2column>=0 && swappedcandies.candy2column<=6 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+2].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+2].isMarkedDeletion=true;
//     }
//     else if (//check right T shape for second swapped candy
//        (swappedcandies.candy2row>=1 && swappedcandies.candy2row<=7 && swappedcandies.candy2column>=2 && swappedcandies.candy2column<=8 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-2].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-2].isMarkedDeletion=true;
//     }
//     else if (//check up T shape for second swapped candy
//         (swappedcandies.candy2row>=0 && swappedcandies.candy2row<=6 && swappedcandies.candy2column>=1 && swappedcandies.candy2column<=7 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+2][swappedcandies.candy2column].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+2][swappedcandies.candy2column].isMarkedDeletion=true;
//     }
//     else if (//check down T shape for second swapped candy
//         (swappedcandies.candy2row>=2 && swappedcandies.candy2row<=8 && swappedcandies.candy2column>=1 && swappedcandies.candy2column<=7 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-2][swappedcandies.candy2column].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-2][swappedcandies.candy2column].isMarkedDeletion=true;
//     }
//     // checks for L shape for first swapped candy
//     else if (//check right upper L shape for first swapped candy
//         (swappedcandies.candy1row>=2 && swappedcandies.candy1row<=8 && swappedcandies.candy1column>=0 && swappedcandies.candy1column<=6 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+2].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-2][swappedcandies.candy1column].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+-2][swappedcandies.candy1column].isMarkedDeletion=true;
//     }
//     else if (//check left upper L shape for first swapped candy
//         (swappedcandies.candy1row>=2 && swappedcandies.candy1row<=8 && swappedcandies.candy1column>=2 && swappedcandies.candy1column<=8 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-2].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row-2][swappedcandies.candy1column].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-2][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row-2][swappedcandies.candy1column].isMarkedDeletion=true;
//     }
//     else if (//check right lower L for first swapped candy
//         (swappedcandies.candy1row>=0 && swappedcandies.candy1row<=6 && swappedcandies.candy1column>=0 && swappedcandies.candy1column<=6 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+2].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+2][swappedcandies.candy1column].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column+2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+2][swappedcandies.candy1column].isMarkedDeletion=true;
//     }
//     else if(//check for left lower L for first swapped candy
//         (swappedcandies.candy1row>=0 && swappedcandies.candy1row<=6 && swappedcandies.candy1column>=2 && swappedcandies.candy1column<=8 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-2].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].color==color1 &&
//         gameBoard.candyGrid[swappedcandies.candy1row+2][swappedcandies.candy1column].color==color1)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column-2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+1][swappedcandies.candy1column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy1row+2][swappedcandies.candy1column].isMarkedDeletion=true;
//     }
//         // checks for L shape for second swapped candy
//     else if (//check right upper L shape for second swapped candy
//         (swappedcandies.candy2row>=2 && swappedcandies.candy2row<=8 && swappedcandies.candy2column>=0 && swappedcandies.candy2column<=6 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+2].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-2][swappedcandies.candy2column].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+-2][swappedcandies.candy2column].isMarkedDeletion=true;
//     }
//     else if (//check left upper L shape for second swapped candy
//         (swappedcandies.candy2row>=2 && swappedcandies.candy2row<=8 && swappedcandies.candy2column>=2 && swappedcandies.candy2column<=8 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-2].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row-2][swappedcandies.candy2column].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-2][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row-2][swappedcandies.candy2column].isMarkedDeletion=true;
//     }
//     else if (//check right lower L for second swapped candy
//         (swappedcandies.candy2row>=0 && swappedcandies.candy2row<=6 && swappedcandies.candy2column>=0 && swappedcandies.candy2column<=6 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+2].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+2][swappedcandies.candy2column].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column+2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+2][swappedcandies.candy2column].isMarkedDeletion=true;
//     }
//     else if(//check for left lower L for second swapped candy
//         (swappedcandies.candy2row>=0 && swappedcandies.candy2row<=6 && swappedcandies.candy2column>=2 && swappedcandies.candy2column<=8 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-2].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].color==color2 &&
//         gameBoard.candyGrid[swappedcandies.candy2row+2][swappedcandies.candy2column].color==color2)
//       )
//     {
//         isFound=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-1].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column-2].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+1][swappedcandies.candy2column].isMarkedDeletion=true;
//         gameBoard.candyGrid[swappedcandies.candy2row+2][swappedcandies.candy2column].isMarkedDeletion=true;
//     }
//     return isFound;
    for(int row{0}; row<MAX_ROWS; row++){
        for(int col{0}; col<MAX_COLUMNS; col++){
            if (gameBoard.candyGrid[row][col].isMarkedDeletion) continue;
            bool isverticalMatch{checkVerticalMatch(gameBoard, row, col)};
            bool ishorizontalMatch{checkHorizontalMatch(gameBoard, row, col)};
            if(isverticalMatch && ishorizontalMatch){
                isFound=true;
                CandyColor color = gameBoard.candyGrid[row][col].color;
                gameBoard.candyGrid[row][col].type = Wrapped;
                
                //mark left
                for (int c = col -1; c >=0 && gameBoard.candyGrid[row][c].color == color; c--){
                    gameBoard.candyGrid[row][c].isMarkedDeletion = true;
                }
                //mark right
                for (int c = col +1; c < MAX_COLUMNS && gameBoard.candyGrid[row][c].color == color; c++){
                    gameBoard.candyGrid[row][c].isMarkedDeletion = true;
                }
                //mark up
                for (int r = row -1; r >=0 && gameBoard.candyGrid[r][col].color == color; r--){
                    gameBoard.candyGrid[r][col].isMarkedDeletion = true;
                }
                //mark down
                for (int r = row +1; r < MAX_ROWS && gameBoard.candyGrid[r][col].color == color; r++){
                    gameBoard.candyGrid[r][col].isMarkedDeletion = true;
                }

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
    for(int i=0; i<MAX_ROWS; i++)
    {
        for(int j=0 ; j<MAX_COLUMNS; j++)
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
int handleMatchAndRefill (Board &gameBoard,swappedCandies swappedcandies)
{
    int score=0;
    while(findAndMarkFiveMatches(gameBoard)||findAndMarkFourMatches(gameBoard)||findAndMarkLorTshapeMatches(gameBoard,swappedcandies)||findAndMarkThreeMatches(gameBoard))
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
