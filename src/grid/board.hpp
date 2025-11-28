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
    Vector2 currentPos;
};

struct Board
{
    Candy candyGrid[MAX_ROWS][MAX_COLUMNS];
};

const int candypoints[5]{30, 30, 40, 50, 60};

/**
 * @brief initializes the grid with random candies
 * @param gridOffset the offset of the grid
 * @param tileSize the size of each tile
 * @returns the initialized board
 */
Board initializeGrid(Vector2 gridOffset, const int tileSize);

/**
 * @brief animates the board
 * @param gameBoard the game board
 * @param gridOffset the offset of the grid
 * @param tileSize the size of each tile
 * @param speed the speed of the animation
 * @returns true if the animation is complete
 */
bool animatBoard(Board &gameBoard, Vector2 gridOffset, const int tileSize, float speed);

/**
 * @brief gets the target position of a candy (where it should be)
 * @param row the row of the candy
 * @param col the column of the candy
 * @param gridOffset the offset of the grid
 * @param tileSize the size of each tile
 * @returns the target position
 */
Vector2 getTargetPos(int row, int col, Vector2 gridOffset, const int tileSize);

/**
 * @brief swaps two candies
 * @param gameBoard the game board
 * @param row1 the row of the first candy
 * @param coloumn1 the column of the first candy
 * @param row2 the row of the second candy
 * @param coloumn2 the column of the second candy
 */
void swapCandies(Board &gameBoard, int row1, int coloumn1, int row2, int coloumn2);

/**
 * @brief checks if a candy is part of a match
 * @param gameBoard the game board
 * @param row the row of the candy
 * @param coloumn the column of the candy
 * @returns true if the candy is part of a match
 */
bool isPartOfMatch(Board &gameBoard, int row, int coloumn);

/**
 * @brief gets the score from marked candies
 * @param gameBoard the game board
 * @returns the score
 */
int getScoreFromMarkedCandies(const Board &gameBoard);

/**
 * @brief finds and marks l or t shape matches
 * @param gameBoard the game board
 * @returns true if matches were found
 */
bool findAndMarkLorTshapeMatches(Board &gameBoard);

/**
 * @brief finds and marks four matches
 * @param gameBoard the game board
 * @param swappedcandies the swapped candies
 * @returns true if matches were found
 */
bool findAndMarkFourMatches(Board &gameBoard, swappedCandies swappedcandies);

/**
 * @brief finds and marks five matches
 * @param gameBoard the game board
 * @param swappedcandies the swapped candies
 * @returns true if matches were found
 */
bool findAndMarkFiveMatches(Board &gameBoard, swappedCandies swappedcandies);

/**
 * @brief finds and marks three matches
 * @param gameBoard the game board
 * @returns true if matches were found
 */
bool findAndMarkThreeMatches(Board &gameBoard);

/**
 * @brief refills the board(replaces deleted candies with new ones)
 * @param gameboard the game board
 * @param gridOffset the offset of the grid
 * @param tileSize the size of each tile
 */
void refillBoard(Board &gameboard, Vector2 gridOffset, int tileSize);

/**
 * @brief applies gravity to the board(moves deleted candies to the top)
 * @param gameboard the game board
 * @param gridOffset the offset of the grid
 * @param tileSize the size of each tile
 */
void applyGravity(Board &gameboard, Vector2 gridOffset, int tileSize);

/**
 * @brief handles special interactions
 * @param gameBoard the game board
 * @param swappedcandies the swapped candies
 * @returns true if a special interaction occurred
 */
bool handleSpecialInteraction(Board &gameBoard, swappedCandies swappedcandies);

/**
 * @brief checks if deleted candies are present
 * @param gameBoard the game board
 * @returns true if deleted candies are present
 */
bool isDeletedPresent(Board &gameBoard);
#endif