#include "utils/Random.hpp"
#include "utils/Vector2Utills.hpp"
#include "board.hpp"
#include "input.hpp"
#include "raylib.h"

// points associated with each candy color
void initializeGrid(Board &gameBoard,Vector2 gridOffset,const int tileSize)
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
            newCandy.currentPos.y= gridOffset.y;
            newCandy.currentPos.x= gridOffset.x + j * tileSize;
            gameBoard.candyGrid[i][j] = newCandy;
        }
    }
}

// Helper to calculate where a candy SHOULD be based on the grid
Vector2 getTargetPos(int row, int col, Vector2 gridOffset, const int tileSize)
{
    return {
        gridOffset.x + col * tileSize,
        gridOffset.y + row * tileSize};
}

bool animatBoard(Board &gameBoard, Vector2 gridOffset, const int tileSize, float speed)
{
    bool isAnimating = false;
    float step = speed * GetFrameTime();
    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (gameBoard.candyGrid[r][c].isMarkedDeletion)
                continue;
            Vector2 target = getTargetPos(r, c, gridOffset, tileSize);
            Vector2 &current = gameBoard.candyGrid[r][c].currentPos;

            float dist = Vector2Distance(current, target);
            if (dist > 0.01f)
            { // If not at target
                isAnimating = true;

                Vector2 direction = Vector2Subtract(target, current);
                direction = Vector2Normalize(direction);
                current = Vector2Add(current, Vector2Scale(direction, step));

                // Snap if close
                if (Vector2Distance(current, target) < step)
                {
                    current = target;
                }
            }
        }
    }
    return isAnimating;
}



// function for swapping candies
void swapCandies(Board &gameBoard, int row1, int column1, int row2, int column2)
{
    Candy temp = gameBoard.candyGrid[row1][column1];
    gameBoard.candyGrid[row1][column1] = gameBoard.candyGrid[row2][column2];
    gameBoard.candyGrid[row2][column2] = temp;

    // Vector2 pos1 = gameBoard.candyGrid[row1][column1].currentPos;
    // Vector2 pos2 = gameBoard.candyGrid[row2][column2].currentPos;

    // gameBoard.candyGrid[row1][column1].currentPos = pos2;
    // gameBoard.candyGrid[row2][column2].currentPos = pos1;
}

// function to check if candy is part of match

bool checkHorizontalMatch(Board &gameBoard, int row, int coloumn)
{
    CandyColor color = gameBoard.candyGrid[row][coloumn].color;
    int count = 1;
    for (int i = coloumn - 1; i >= 0 && gameBoard.candyGrid[row][i].color == color; i--)
    {
        count++;
    }
    for (int i = coloumn + 1; i < MAX_COLUMNS && gameBoard.candyGrid[row][i].color == color; i++)
    {
        count++;
    }
    return count >= 3;
}

bool checkVerticalMatch(Board &gameBoard, int row, int coloumn)
{
    CandyColor color = gameBoard.candyGrid[row][coloumn].color;
    int count = 1;
    for (int i = row - 1; i >= 0 && gameBoard.candyGrid[i][coloumn].color == color; i--)
    {
        count++;
    }
    for (int i = row + 1; i < MAX_ROWS && gameBoard.candyGrid[i][coloumn].color == color; i++)
    {
        count++;
    }
    return count >= 3;
}

// function to check if candy is part of match
bool isPartOfMatch(Board &gameBoard, int row, int coloumn)
{
    return checkHorizontalMatch(gameBoard, row, coloumn) || checkVerticalMatch(gameBoard, row, coloumn);
}



// for testing purposes only
bool testSwapping(Board &gameBoard, swappedCandies swappedcandies)

{
    swapCandies(gameBoard, swappedcandies.candy1row, swappedcandies.candy1column, swappedcandies.candy2row, swappedcandies.candy2column);
    return true;
}

// function to find and mark three matches on the board
bool findAndMarkThreeMatches(Board &gameBoard)
{
    bool isFound{};
    // checks horizontally 3 plain candies
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS - 2; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion &&
                !gameBoard.candyGrid[i][j+1].isMarkedDeletion &&
                !gameBoard.candyGrid[i][j+2].isMarkedDeletion &&
                color == gameBoard.candyGrid[i][j + 1].color &&
                color == gameBoard.candyGrid[i][j + 2].color)
            {
                isFound = true;
                gameBoard.candyGrid[i][j].isMarkedDeletion = true;
                gameBoard.candyGrid[i][j + 1].isMarkedDeletion = true;
                gameBoard.candyGrid[i][j + 2].isMarkedDeletion = true;
            }
        }
    }
    // checks vertically 3 plain candies
    for (int i = 0; i < MAX_ROWS - 2; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && 
                color == gameBoard.candyGrid[i + 1][j].color && 
                color == gameBoard.candyGrid[i + 2][j].color)
            {
                isFound = true;
                gameBoard.candyGrid[i][j].isMarkedDeletion = true;
                gameBoard.candyGrid[i + 1][j].isMarkedDeletion = true;
                gameBoard.candyGrid[i + 2][j].isMarkedDeletion = true;
            }
        }
    }
    return isFound;
}
// function to check and mark four matches on board
bool findAndMarkFourMatches(Board &gameBoard, swappedCandies swappedcandies)
{
    bool isFound{};
    // checks horizontally 4 plain candies
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS - 3; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && color == gameBoard.candyGrid[i][j + 1].color && color == gameBoard.candyGrid[i][j + 2].color && color == gameBoard.candyGrid[i][j + 3].color)
            {
                isFound = true;

                for (int k{0}; k < 5; k++)
                {
                    if ((i == swappedcandies.candy1row && j + k == swappedcandies.candy1column) || (i == swappedcandies.candy2row && j + k == swappedcandies.candy2column))
                    {

                        gameBoard.candyGrid[i][j + k].type = (swappedcandies.orientation == Horizontal) ? Striped_horizontal : Striped_vertical;
                    }
                    else
                    {
                        gameBoard.candyGrid[i][j + k].isMarkedDeletion = true;
                    }
                }
            }
        }
    }
    // checks vertically 4 plain candies
    for (int i = 0; i < MAX_ROWS - 3; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && color == gameBoard.candyGrid[i + 1][j].color && color == gameBoard.candyGrid[i + 2][j].color && color == gameBoard.candyGrid[i + 3][j].color)
            {
                isFound = true;
                for (int k{0}; k < 5; k++)
                {
                    if ((i + k == swappedcandies.candy1row && j == swappedcandies.candy1column) || (i + k == swappedcandies.candy2row && j == swappedcandies.candy2column))
                    {
                        gameBoard.candyGrid[i + k][j].type = (swappedcandies.orientation == Horizontal) ? Striped_horizontal : Striped_vertical;
                    }
                    else
                    {
                        gameBoard.candyGrid[i + k][j].isMarkedDeletion = true;
                    }
                }
            }
        }
    }
    return isFound;
}
// function to check and mark five matches on board
bool findAndMarkFiveMatches(Board &gameBoard, swappedCandies swappedcandies)
{
    bool isFound{};
    // checks horizontally 5 plain candies
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS - 4; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && color == gameBoard.candyGrid[i][j + 1].color && color == gameBoard.candyGrid[i][j + 2].color && color == gameBoard.candyGrid[i][j + 3].color && color == gameBoard.candyGrid[i][j + 4].color)
            {
                isFound = true;

                for (int k{0}; k < 5; k++)
                {
                    if ((i == swappedcandies.candy1row && j + k == swappedcandies.candy1column) || (i == swappedcandies.candy2row && j + k == swappedcandies.candy2column))
                    {
                        gameBoard.candyGrid[i][j + k].color = Bomb;
                    }
                    else
                    {
                        gameBoard.candyGrid[i][j + k].isMarkedDeletion = true;
                    }
                }
            }
        }
    }
    // checks vertically 5 plain candies
    for (int i = 0; i < MAX_ROWS - 4; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && color == gameBoard.candyGrid[i + 1][j].color && color == gameBoard.candyGrid[i + 2][j].color && color == gameBoard.candyGrid[i + 3][j].color && color == gameBoard.candyGrid[i + 4][j].color)
            {
                isFound = true;

                for (int k{0}; k < 5; k++)
                {
                    if ((i + k == swappedcandies.candy1row && j == swappedcandies.candy1column) || (i + k == swappedcandies.candy2row && j == swappedcandies.candy2column))
                    {
                        gameBoard.candyGrid[i + k][j].color = Bomb;
                    }
                    else
                    {
                        gameBoard.candyGrid[i + k][j].isMarkedDeletion = true;
                    }
                }
            }
        }
    }
    return isFound;
}

// function to check and mark L or T shape matches on board
bool findAndMarkLorTshapeMatches(Board &gameBoard, swappedCandies swappedcandies)
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
    for (int row{0}; row < MAX_ROWS; row++)
    {
        for (int col{0}; col < MAX_COLUMNS; col++)
        {
            if (gameBoard.candyGrid[row][col].isMarkedDeletion)
                continue;
            bool isverticalMatch{checkVerticalMatch(gameBoard, row, col)};
            bool ishorizontalMatch{checkHorizontalMatch(gameBoard, row, col)};
            if (isverticalMatch && ishorizontalMatch)
            {
                isFound = true;
                CandyColor color = gameBoard.candyGrid[row][col].color;
                gameBoard.candyGrid[row][col].type = Wrapped;

                // mark left
                for (int c = col - 1; c >= 0 && gameBoard.candyGrid[row][c].color == color; c--)
                {
                    gameBoard.candyGrid[row][c].isMarkedDeletion = true;
                }
                // mark right
                for (int c = col + 1; c < MAX_COLUMNS && gameBoard.candyGrid[row][c].color == color; c++)
                {
                    gameBoard.candyGrid[row][c].isMarkedDeletion = true;
                }
                // mark up
                for (int r = row - 1; r >= 0 && gameBoard.candyGrid[r][col].color == color; r--)
                {
                    gameBoard.candyGrid[r][col].isMarkedDeletion = true;
                }
                // mark down
                for (int r = row + 1; r < MAX_ROWS && gameBoard.candyGrid[r][col].color == color; r++)
                {
                    gameBoard.candyGrid[r][col].isMarkedDeletion = true;
                }
            }
        }
    }
    return isFound;
}



void applyGravity(Board& board, Vector2 gridOffset, int tileSize) {
    for (int c = 0; c < MAX_COLUMNS; ++c) {
        int writeRow = MAX_ROWS - 1;
        for (int readRow = MAX_ROWS - 1; readRow >= 0; --readRow) {
            if (board.candyGrid[readRow][c].isMarkedDeletion == false) {

                // If we are moving a candy...
                if (writeRow != readRow) {
                    // Copy data down to the write slot
                    board.candyGrid[writeRow][c] = board.candyGrid[readRow][c];

                    // Mark the old slot as empty so it will be refilled
                    board.candyGrid[readRow][c].isMarkedDeletion = true;
                    board.candyGrid[readRow][c].type = Plain;

                    // KEY: The visual position stays exactly where it was (higher up)
                    // The animation system will slide the candy down to the target.
                }
                writeRow--;
            }
        }

    }
}

void refillBoard(Board& board, Vector2 gridOffset, int tileSize) {
     for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < MAX_COLUMNS; ++c) {
            if (board.candyGrid[r][c].isMarkedDeletion) {
                // Create new candy
                board.candyGrid[r][c].color = static_cast<CandyColor>(getRand(0, 4));
                board.candyGrid[r][c].isMarkedDeletion = false;
                board.candyGrid[r][c].type = Plain;

                // KEY: Spawn it ABOVE the board so it can animate into place
                Vector2 target = getTargetPos(r, c, gridOffset, tileSize);
                board.candyGrid[r][c].currentPos = { target.x, GetScreenHeight()*0.2f }; // Start way above
            }
        }
    }
}

// handle matches and refills
int handleMatchAndRefill(Board &gameBoard, swappedCandies swappedcandies, Vector2 gridOffset, const int tileSize)
{
    int score = 0;
    while (findAndMarkFiveMatches(gameBoard, swappedcandies) || findAndMarkFourMatches(gameBoard, swappedcandies) || findAndMarkLorTshapeMatches(gameBoard, swappedcandies) || findAndMarkThreeMatches(gameBoard))
    {
        for (int i = 0; i < MAX_ROWS; i++)
        {
            for (int j = 0; j < MAX_COLUMNS; j++)
            {
                if (gameBoard.candyGrid[i][j].isMarkedDeletion == true)
                {
                    score += candypoints[gameBoard.candyGrid[i][j].color];
                }
            }
        }
        applyGravity(gameBoard, gridOffset, tileSize);
        refillBoard(gameBoard, gridOffset, tileSize);
    }
    return score;
}
