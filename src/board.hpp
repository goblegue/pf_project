#ifndef BOARD_HPP
#define BOARD_HPP

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
};

struct Board
{
    Candy candyGrid[MAX_ROWS][MAX_COLUMNS];
};

const int candypoints[5]{30, 30, 40, 50, 60};

void initalizeGrid(Board &gameBoard);

int handleMatchAndRefill (Board &gameBoard);

bool trySwapping (Board &gameBoard, int row1, int coloumn1,int row2, int coloumn2);

#endif