#ifndef INPUT_HPP
#define INPUT_HPP

#include "raylib.h"

struct Button;

enum SwapOrientation
{
    Horizontal,
    Vertical
};

// struct to keep track of selected candy
struct SelectedCandy
{
    int row;
    int column;
    bool isSelected;
};

// struct to keep track of swapped candies
struct swappedCandies
{
    int candy1row;
    int candy1column;
    int candy2row;
    int candy2column;
    SwapOrientation orientation;
};

// function to check if two candies are adjacent
/**
 * @brief checks if two candies are adjacent
 * @param row1 the row of the first candy
 * @param column1 the column of the first candy
 * @param row2 the row of the second candy
 * @param column2 the column of the second candy
 * @returns true if the candies are adjacent
 */
bool isAdjacent(int row1, int column1, int row2, int column2);

// function to handle mouse input
/**
 * @brief handles mouse input
 * @param selection the selected candy
 * @param gridOffSet the offset of the grid
 * @param TILE_SIZE the size of each tile
 * @returns true if a candy was selected
 */
bool handleMouseInput(SelectedCandy &selection, Vector2 gridOffSet, const int TILE_SIZE);

/**
 * @brief gets the swapped candies
 * @returns the swapped candies
 */
swappedCandies getSwappedCandies();

/**
 * @brief checks if a button is pressed
 * @param btn the button
 * @returns true if the button is pressed
 */
bool isButtonPressed(Button &btn);

#endif
