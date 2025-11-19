#ifndef BOARD_HPP
#define BOARD_HPP
#include "raylib.h"
// Forward declaration to avoid circular dependency
struct SelectedCandy;
struct swappedCandies;

const int MAX_ROWS{9};
const int MAX_COLUMNS{9};

enum CandyColor
{
    Red,
    Yellow,
    Green,
    Blue,
    Orange,
    Bomb
};

enum SpecialCandy
{
    None,
    Wrapped,
    Striped
};

struct Candy
{
    CandyColor color;
    SpecialCandy special;
    bool isMarkedDeletion;
    Vector2  currentPos;
};

struct Board
{
    Candy candyGrid[MAX_ROWS][MAX_COLUMNS];
};

const int ANIMATION_SPEED = 5;
const int candypoints[5]{30, 30, 40, 50, 60};

void initializeGrid(Board &gameBoard,Vector2 gridOffset,const int tileSize);

int handleMatchAndRefill (Board &gameBoard,swappedCandies swap);


bool animationBoard(Board& gameBoard, Vector2 gridOffset,const int tileSize);

Vector2 getTargetPos(int row, int col, Vector2 gridOffset, const int tileSize);


int handleMatchAndRefill (Board &gameBoard,swappedCandies swappedcandies,Vector2 gridOffset,const int tileSize);

bool trySwapping (Board &gameBoard, int row1, int column1,int row2, int column2);


#endif