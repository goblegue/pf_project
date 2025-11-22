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

enum CandyType
{
    Plain,
    Wrapped,
    Striped_horizontal,
    Striped_vertical
};

struct Candy
{
    CandyColor color;
    CandyType type;
    bool isMarkedDeletion;
    Vector2  currentPos;
};

struct Board
{
    Candy candyGrid[MAX_ROWS][MAX_COLUMNS];
};


const int candypoints[5]{30, 30, 40, 50, 60};

void initializeGrid(Board &gameBoard,Vector2 gridOffset,const int tileSize);

int handleMatchAndRefill (Board &gameBoard,swappedCandies swap);


bool animationBoard(Board& gameBoard, Vector2 gridOffset,const int tileSize, float speed);

Vector2 getTargetPos(int row, int col, Vector2 gridOffset, const int tileSize);


int handleMatchAndRefill (Board &gameBoard,swappedCandies swappedcandies,Vector2 gridOffset,const int tileSize);


void swapCandies (Board &gameBoard,int row1,int coloumn1,int row2,int coloumn2);
bool isPartOfMatch(Board &gameBoard, int row, int coloumn);


bool trySwapping (Board &gameBoard, swappedCandies swappedcandies);
bool testSwapping (Board &gameBoard, swappedCandies swappedcandies);

#endif