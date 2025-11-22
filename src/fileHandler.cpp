#include <fstream>
#include "fileHandler.hpp"

using namespace std;

bool saveBoardToFile(const Board& board,int targetScore ,int score, int moves, const char filename[])
{
    ofstream file(filename); 
    if (!file.is_open()) {
        return false;
    }

    file << targetScore << " " << score << " " << moves << "\n";
    file << MAX_ROWS << " " << MAX_COLUMNS << "\n";

    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLUMNS; c++) {
            const Candy& candy = board.candyGrid[r][c];
            file << (int)candy.color << " "
                 << (int)candy.type << " "
                 << candy.currentPos.x << " "
                 << candy.currentPos.y;
            
            if (c < MAX_COLUMNS - 1) file << " ";
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool loadBoardFromFile(Board& board, int& score, int& moves, const char filename[])
{
    ifstream file(filename); 
    if (!file.is_open()) {
        return false;
    }

    file >> score >> moves;

    int rows, cols;
    file >> rows >> cols; 

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int color, type;
            float px, py;
            
            file >> color >> type >> px >> py;

            board.candyGrid[r][c].color = (CandyColor)color;
            board.candyGrid[r][c].type = (CandyType)type;
            board.candyGrid[r][c].currentPos = { px, py };
            board.candyGrid[r][c].isMarkedDeletion = false; 
        }
    }

    file.close();
    return true;
}