#include "raylib.h"
#include "board.hpp"
#include "renderer.hpp"
#include "input.hpp"

int main() {
    const int screenWidth = 545;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Candy Crush");
    SetTargetFPS(15);

    // --- Setup ---
    Board gameBoard;
    initalizeGrid(gameBoard); // Initialize game logic

    Renderer renderer = initRenderer(screenWidth, screenHeight); // Initialize graphics

    SelectedCandy selection{}; // To track selected candy

    int score{};

    // --- Main Game Loop ---
    while (!WindowShouldClose()) {
        // Handle inp6ut here...
        bool swapedOccure=handleMouseInput(gameBoard, selection, {renderer.gridOffset.x, renderer.gridOffset.y},TILE_SIZE);
        
        if(swapedOccure){
            score+=handleMatchAndRefill(gameBoard);
        }
        
        
        // --- Drawing ---
        BeginDrawing();
        ClearBackground(DARKBROWN);
        
        // Pass both the game state and renderer to the draw function
        drawBoard(renderer, gameBoard, selection);
        DrawText(TextFormat("Score:,%i",score),50,50,20,YELLOW);


        EndDrawing();
    }

    // --- Teardown ---
    unloadRenderer(renderer); // Unload graphics
    CloseWindow();

    return 0;
}