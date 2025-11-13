#ifndef BOARD.HPP
#define BOARD.HPP

enum CandyType{
    Empty,Blue,Orange,Red,Green,Yellow,Bomb
};

enum SpecialCandy{
    None,Wrapped,Striped
};

struct Candy{
    CandyType CandyType;
    SpecialCandy SpecialCandy;
    int points;
    bool isMarkedDeletion;
};

const int maxRows{9};
const int maxColumns{9};

Candy Candies[maxRows][maxColumns]{};

void initalizeGrid(Candy [maxRows][maxColumns]);
#endif