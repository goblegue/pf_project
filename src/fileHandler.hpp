#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include "board.hpp"


bool saveBoardToFile(const Board& board, int score, int moves, const char filename[]);
bool loadBoardFromFile(Board& board, int& score, int& moves, const char filename[]);

#endif