#include "utils/Random.hpp"
#include "utils/Vector2Utills.hpp"
#include "board.hpp"
#include "input.hpp"
#include "raylib.h"

void triggerCandyEffect(Board &gameboard, int row, int col);

// points associated with each candy color
void initializeGrid(Board &gameBoard, Vector2 gridOffset, const int tileSize)
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
            newCandy.currentPos.y = gridOffset.y;
            newCandy.currentPos.x = gridOffset.x + j * tileSize;
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
                !gameBoard.candyGrid[i][j + 1].isMarkedDeletion &&
                !gameBoard.candyGrid[i][j + 2].isMarkedDeletion &&
                color == gameBoard.candyGrid[i][j + 1].color &&
                color == gameBoard.candyGrid[i][j + 2].color)
            {
                isFound = true;
                triggerCandyEffect(gameBoard, i ,j);
                triggerCandyEffect(gameBoard, i ,j + 1);
                triggerCandyEffect(gameBoard, i ,j + 2);
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
                triggerCandyEffect(gameBoard, i ,j);
                triggerCandyEffect(gameBoard, i + 1 ,j);
                triggerCandyEffect(gameBoard, i + 2 ,j);
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

                for (int k{0}; k < 4; k++)
                {
                    if ((i == swappedcandies.candy1row && j + k == swappedcandies.candy1column) || (i == swappedcandies.candy2row && j + k == swappedcandies.candy2column))
                    {

                        gameBoard.candyGrid[i][j + k].type = (swappedcandies.orientation == Horizontal) ? Striped_horizontal : Striped_vertical;
                    }
                    else
                    {
                        triggerCandyEffect(gameBoard, i ,j + k);
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
                for (int k{0}; k < 4; k++)
                {
                    if ((i + k == swappedcandies.candy1row && j == swappedcandies.candy1column) || (i + k == swappedcandies.candy2row && j == swappedcandies.candy2column))
                    {
                        gameBoard.candyGrid[i + k][j].type = (swappedcandies.orientation == Horizontal) ? Striped_horizontal : Striped_vertical;
                    }
                    else
                    {
                        triggerCandyEffect(gameBoard, i + k ,j);
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
                        triggerCandyEffect(gameBoard, i ,j + k);
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
                        triggerCandyEffect(gameBoard, i + k ,j);
                    }
                }
            }
        }
    }
    return isFound;
}

// function to check and mark L or T shape matches on board
bool findAndMarkLorTshapeMatches(Board &gameBoard)
{
    bool isFound{};
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

void applyGravity(Board &board, Vector2 gridOffset, int tileSize)
{
    for (int c = 0; c < MAX_COLUMNS; ++c)
    {
        int writeRow = MAX_ROWS - 1;
        for (int readRow = MAX_ROWS - 1; readRow >= 0; --readRow)
        {
            if (board.candyGrid[readRow][c].isMarkedDeletion == false)
            {

                // If we are moving a candy...
                if (writeRow != readRow)
                {
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

void refillBoard(Board &board, Vector2 gridOffset, int tileSize)
{
    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (board.candyGrid[r][c].isMarkedDeletion)
            {
                // Create new candy
                board.candyGrid[r][c].color = static_cast<CandyColor>(getRand(0, 4));
                board.candyGrid[r][c].isMarkedDeletion = false;
                board.candyGrid[r][c].type = Plain;

                // KEY: Spawn it ABOVE the board so it can animate into place
                Vector2 target = getTargetPos(r, c, gridOffset, tileSize);
                board.candyGrid[r][c].currentPos = {target.x, GetScreenHeight() * 0.2f}; // Start way above
            }
        }
    }
}

int getScoreFromMarkedCandies(const Board &gameBoard)
{
    int currentMoveScore = 0;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            // Only count candies that are about to be removed
            if (gameBoard.candyGrid[i][j].isMarkedDeletion)
            {
                // Add points based on color
                currentMoveScore += candypoints[gameBoard.candyGrid[i][j].color];
            }
        }
    }
    return currentMoveScore;
}

// for horizontal striped candy effect
void destroyRow(Board &gameBoard, int row)
{
    for (int col = 0; col < MAX_COLUMNS; ++col)
    {
        triggerCandyEffect(gameBoard, row, col);
    }
}

// for vertical striped candy effect
void destroyColumn(Board &gameBoard, int column)
{
    for (int row = 0; row < MAX_ROWS; ++row)
    {
        triggerCandyEffect(gameBoard, row, column);
    }
}

// for wrapped candy effect
void destroyArea(Board &gameBoard, int centerRow, int centerCol, int squareLenght)
{
    int radius = (squareLenght - 1) / 2;

    for (int r = centerRow - radius; r <= centerRow + radius; ++r)
    {
        for (int c = centerCol - radius; c <= centerCol + radius; ++c)
        {
            if (r >= 0 && r < MAX_ROWS && c >= 0 && c < MAX_COLUMNS)
            {
                triggerCandyEffect(gameBoard, r, c);
            }
        }
    }
}

// candy bomb
void destroyColor(Board &gameBoard, CandyColor color)
{
    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (gameBoard.candyGrid[r][c].color == color)
            {
                triggerCandyEffect(gameBoard, r, c);
            }
        }
    }
}

void triggerCandyEffect(Board &gameboard, int row, int col)
{
    if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLUMNS)
        return;
    if (gameboard.candyGrid[row][col].isMarkedDeletion)
        return;
    gameboard.candyGrid[row][col].isMarkedDeletion = true;
    switch (gameboard.candyGrid[row][col].type)
    {
    case Striped_horizontal:
        destroyRow(gameboard, row);
        break;
    case Striped_vertical:
        destroyColumn(gameboard, col);
        break;
    case Wrapped:
        destroyArea(gameboard, row, col, 3);
        break;
    case Bomb:
        destroyColor(gameboard, static_cast<CandyColor>(getRand(0, 4)));
        break;
    default:
        break;
    }
}

// bomb candy interactions

void handleBombBomb(Board &gameboard)
{
    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {

            triggerCandyEffect(gameboard, r, c);
        }
    }
}

void handleBombStriped(Board &gameboard,swappedCandies swappedcandies){
    Candy candy1=gameboard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column];
    Candy candy2=gameboard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column];
    CandyColor targetColor=(candy1.color==Bomb)?candy2.color:candy1.color;

    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (gameboard.candyGrid[r][c].color == targetColor)
            {
                gameboard.candyGrid[r][c].type=(getRand(0,1)==0)?Striped_horizontal:Striped_vertical;
            }
        }
    }

    // explode that color
    destroyColor(gameboard, targetColor);

    //destroy the original 2
    triggerCandyEffect(gameboard, swappedcandies.candy1row, swappedcandies.candy1column);
    triggerCandyEffect(gameboard, swappedcandies.candy2row, swappedcandies.candy2column);
}

void handleBombWrapped(Board &gameboard,swappedCandies swappedcandies){
    Candy candy1=gameboard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column];
    Candy candy2=gameboard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column];
    CandyColor targetColor=(candy1.color==Bomb)?candy2.color:candy1.color;

    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (gameboard.candyGrid[r][c].color == targetColor)
            {
                gameboard.candyGrid[r][c].type=Wrapped;
            }
        }
    }

    // explode that color
    destroyColor(gameboard, targetColor);

    //destroy the original 2
    triggerCandyEffect(gameboard, swappedcandies.candy1row, swappedcandies.candy1column);
    triggerCandyEffect(gameboard, swappedcandies.candy2row, swappedcandies.candy2column);

}

void handleBombPlain(Board &gameboard,swappedCandies swappedcandies){
    Candy candy1=gameboard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column];
    Candy candy2=gameboard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column];
    CandyColor targetColor=(candy1.color==Bomb)?candy2.color:candy1.color;

    // explode that color
    destroyColor(gameboard, targetColor);

    //destroy the original 2
    triggerCandyEffect(gameboard, swappedcandies.candy1row, swappedcandies.candy1column);
    triggerCandyEffect(gameboard, swappedcandies.candy2row, swappedcandies.candy2column);
}

bool handleSpecialInteraction(Board &gameBoard, swappedCandies swappedcandies)
{
    Candy candy1 = gameBoard.candyGrid[swappedcandies.candy1row][swappedcandies.candy1column];
    Candy candy2 = gameBoard.candyGrid[swappedcandies.candy2row][swappedcandies.candy2column];

    // BOMB CANDY INTERACTION

    if (candy1.color == Bomb && candy2.color == Bomb)
    {
        handleBombBomb(gameBoard);
        return true;
    }
    
    if(candy1.color==Bomb || candy2.color==Bomb){
        CandyType otherType=(candy1.color==Bomb)?candy2.type:candy1.type;
        if(otherType==Plain){
            handleBombPlain(gameBoard,swappedcandies);
            return true;
        }
        else if(otherType==Striped_horizontal || otherType==Striped_vertical){
            handleBombStriped(gameBoard,swappedcandies);
            return true;
        }
        else if(otherType==Wrapped){
            handleBombWrapped(gameBoard,swappedcandies);
            return true;
        }
    }
    return false;
}

bool isDeletedPresent(Board &gameBoard){
    for (int r = 0; r < MAX_ROWS; ++r)
    {
        for (int c = 0; c < MAX_COLUMNS; ++c)
        {
            if (gameBoard.candyGrid[r][c].isMarkedDeletion)
            {
                return true;
            }
        }
    }
    return false;
}