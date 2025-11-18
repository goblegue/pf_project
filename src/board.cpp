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
            newCandy.special = None;
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

bool animationBoard(Board &gameBoard, Vector2 gridOffset, const int tileSize)
{
    bool isAnimating = false;
    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (gameBoard.candyGrid[r][c].isMarkedDeletion)
                continue;
            Vector2 target = getTargetPos(r, c, gridOffset, tileSize);
            Vector2 &current = gameBoard.candyGrid[r][c].currentPos;

            float dist = Vector2Distance(current, target);
            if (dist > 0.5f)
            { // If not at target
                isAnimating = true;
                // Move current towards target
                // Use simple linear interpolation or constant speed
                Vector2 direction = Vector2Subtract(target, current);
                direction = Vector2Normalize(direction);
                current = Vector2Add(current, Vector2Scale(direction, ANIMATION_SPEED));

                // Snap if close
                if (Vector2Distance(current, target) < ANIMATION_SPEED)
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

    Vector2 pos1 = gameBoard.candyGrid[row1][column1].currentPos;
    Vector2 pos2 = gameBoard.candyGrid[row2][column2].currentPos;

    gameBoard.candyGrid[row1][column1].currentPos = pos2;
    gameBoard.candyGrid[row2][column2].currentPos = pos1;
}

// function to check if candy is part of match

bool isPartOfMatch(Board &gameBoard, int row, int column)
{
    CandyColor color = gameBoard.candyGrid[row][column].color;
    if (gameBoard.candyGrid[row][column].isMarkedDeletion == true)
    {
        return false;
    }
    // checks horizontall match
    int horizontalCount = 1;
    for (int i = column - 1; i >= 0 && gameBoard.candyGrid[row][i].color == color; i--)
    {
        horizontalCount++;
    }
    for (int i = column + 1; i < MAX_COLUMNS && gameBoard.candyGrid[row][i].color == color; i++)
    {
        horizontalCount++;
    }
    if (horizontalCount >= 3)
    {
        return true;
    }
    // checks vertical match
    int verticalCount = 1;
    for (int i = row - 1; i >= 0 && gameBoard.candyGrid[i][column].color == color; i--)
    {
        verticalCount++;
    }
    for (int i = row + 1; i < MAX_ROWS && gameBoard.candyGrid[i][column].color == color; i++)
    {
        verticalCount++;
    }
    if (verticalCount >= 3)
    {
        return true;
    }
    return false;
}
// function to try swapping two candies
bool trySwapping(Board &gameBoard, int row1, int column1, int row2, int column2)
{
    swapCandies(gameBoard, row1, column1, row2, column2);
    if (isPartOfMatch(gameBoard, row1, column1) || isPartOfMatch(gameBoard, row2, column2))
    {
        return true;
    }
    else
    {
        swapCandies(gameBoard, row1, column1, row2, column2); // swap back if no match
        return false;
    }
}

// function to find and mark matches on the board
bool findAndMarkMatches(Board &gameBoard)
{
    bool isFound{};
    // checks horizontally 3 plain candies
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS - 2; j++)
        {

            CandyColor color = gameBoard.candyGrid[i][j].color;
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && color == gameBoard.candyGrid[i][j + 1].color && color == gameBoard.candyGrid[i][j + 2].color)
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
            if (!gameBoard.candyGrid[i][j].isMarkedDeletion && color == gameBoard.candyGrid[i + 1][j].color && color == gameBoard.candyGrid[i + 2][j].color)
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
// // apply gravity
// void applyGravity(Board &gameBoard)
// {
//     for (int i{0}; i < MAX_COLUMNS; i++)
//     {
//         int writeRow = MAX_ROWS - 1;
//         for (int readRow = writeRow; readRow >= 0; readRow--)
//         {
//             if (gameBoard.candyGrid[readRow][i].isMarkedDeletion == false)
//             {
//                 swapCandies(gameBoard, readRow, i, writeRow, i);
//                 writeRow--;
//             }
//         }
//     }
// }
// // refills board
// void refillBoard(Board &gameBoard)
// {
//     for (int i = 0; i < MAX_COLUMNS; i++)
//     {
//         for (int j = 0; j < MAX_ROWS; j++)
//         {
//             if (gameBoard.candyGrid[i][j].isMarkedDeletion == true)
//             {
//                 gameBoard.candyGrid[i][j].color = static_cast<CandyColor>(getRand(0, 4));
//                 gameBoard.candyGrid[i][j].isMarkedDeletion = false;
//             }
//         }
//     }
// }

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
                    board.candyGrid[readRow][c].special = None;

                    // KEY: The visual position stays exactly where it was (higher up)
                    // The animation system will slide the candy down to the target.
                }
                writeRow--;
            }
        }

    }
}

static void refillBoard(Board& board, Vector2 gridOffset, int tileSize) {
     for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < MAX_COLUMNS; ++c) {
            if (board.candyGrid[r][c].isMarkedDeletion) {
                // Create new candy
                board.candyGrid[r][c].color = static_cast<CandyColor>(getRand(0, 4));
                board.candyGrid[r][c].isMarkedDeletion = false;
                board.candyGrid[r][c].special = None;

                // KEY: Spawn it ABOVE the board so it can animate into place
                Vector2 target = getTargetPos(r, c, gridOffset, tileSize);
                board.candyGrid[r][c].currentPos = { target.x, GetScreenHeight()*0.2f }; // Start way above
            }
        }
    }
}

// handle matches and refills
int handleMatchAndRefill(Board &gameBoard, Vector2 gridOffset, const int tileSize)
{
    int score = 0;
    while (findAndMarkMatches(gameBoard))
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
