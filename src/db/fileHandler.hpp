#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include "grid/board.hpp"


bool saveBoardToFile(const Board& board,int targetScore ,int score, int moves, const char filename[]);
bool loadBoardFromFile(Board& board, int& targetScore, int& score, int& moves, const char filename[]);

#endif