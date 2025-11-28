#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include "grid/board.hpp"

/**
 * @brief saves the board to a file
 * @param board the game board
 * @param targetScore the target score
 * @param score the current score
 * @param moves the remaining moves
 * @param filename the name of the file
 * @returns true if the save was successful
 */
bool saveBoardToFile(const Board &board, int targetScore, int score, int moves, const char filename[]);

/**
 * @brief loads the board from a file
 * @param board the game board
 * @param targetScore the target score
 * @param score the current score
 * @param moves the remaining moves
 * @param filename the name of the file
 * @returns true if the load was successful
 */
bool loadBoardFromFile(Board &board, int &targetScore, int &score, int &moves, const char filename[]);

#endif