#include "renderer.hpp"

const int TILE_SIZE{64}; // Size of each candy tile in pixels
const float TOP_MARGIN = 0.25f; // Top margin as a fraction of window height
const float TILE_BORDER_THICKNESS = 1.0f; // Thickness of the border around each tile

Renderer initRenderer(int windowWidth, int windowHeight)
{
    Renderer renderer{};
    renderer.candyTexture = LoadTexture("assets/textures/candies.png"); // Load candy sprite sheet

    renderer .candySourceRecs[Red]    = {0.0f, 740.0f, 100.0f, 100.0f}; // location of red candy in sprite sheet
    renderer .candySourceRecs[Yellow] = {500.0f, 640.0f, 85.0f, 100.0f}; // location of yellow candy in sprite sheet
    renderer .candySourceRecs[Green]  = {0.0f, 640.0f, 100.0f, 100.0f}; // location of green candy in sprite sheet
    renderer .candySourceRecs[Blue]   = {620.0f, 550.0f, 100.0f, 100.0f}; // location of blue candy in sprite sheet
    renderer .candySourceRecs[Orange] = {95.0f, 830.0f, 100.0f, 100.0f}; // location of orange candy in sprite sheet

    renderer.gridOffset.x = (windowWidth - (MAX_COLUMNS * TILE_SIZE)) / 2.0f; // center the grid horizontally
    renderer.gridOffset.y = windowHeight * TOP_MARGIN; // set the distance from top to grid start
    return renderer;
}

void unloadRenderer(Renderer &renderer)
{
    UnloadTexture(renderer.candyTexture);
}

void drawBoard(const Renderer &renderer, const Board &gameBoard,const SelectedCandy &selection)
{
    for (int row = 0; row < MAX_ROWS; ++row)
    {
        for (int col = 0; col < MAX_COLUMNS; ++col)
        {
            Candy candy = gameBoard.candyGrid[row][col];
            Vector2 position;
            position.x = renderer.gridOffset.x + col * TILE_SIZE; 
            position.y = renderer.gridOffset.y + row * TILE_SIZE;
            Rectangle sourceRec = renderer.candySourceRecs[candy.color];
            if(selection.isSelected && selection.row == row && selection.coloumn == col)
            {
                DrawRectangle(position.x-TILE_BORDER_THICKNESS, position.y-TILE_BORDER_THICKNESS, TILE_SIZE+2*TILE_BORDER_THICKNESS, TILE_SIZE+2*TILE_BORDER_THICKNESS, YELLOW);// highlight selected tile
            }
            else{

                DrawRectangle(position.x, position.y, TILE_SIZE, TILE_SIZE, LIGHTGRAY);// tile background
            }
            DrawRectangleLinesEx({position.x - TILE_BORDER_THICKNESS, position.y - TILE_BORDER_THICKNESS, TILE_SIZE + 2 * TILE_BORDER_THICKNESS, TILE_SIZE + 2 * TILE_BORDER_THICKNESS}, TILE_BORDER_THICKNESS, Fade(DARKGRAY, 0.5f));// tile border
            DrawTexturePro(renderer.candyTexture, sourceRec, {position.x, position.y, TILE_SIZE, TILE_SIZE}, {0, 0}, 0.0f, WHITE);// draw candy
        }
    }   
}
