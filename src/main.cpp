#include "raylib.h"
#include "board.hpp"
#include "renderer.hpp"
#include "input.hpp"

int main() {
    const int screenWidth = 545;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Candy Crush");
    SetTargetFPS(60);

    // --- Setup ---
    Board gameBoard;
    initalizeGrid(gameBoard); // Initialize game logic

    Renderer renderer = initRenderer(screenWidth, screenHeight); // Initialize graphics

    SelectedCandy selection{}; // To track selected candy

    // --- Main Game Loop ---
    while (!WindowShouldClose()) {
        // Handle input here...
        HandleMouseInput(gameBoard, selection, renderer.gridOffset.x, renderer.gridOffset.y);
        
        // --- Drawing ---
        BeginDrawing();
        ClearBackground(DARKBROWN);
        
        // Pass both the game state and renderer to the draw function
        drawBoard(renderer, gameBoard, selection);


        EndDrawing();
    }

    // --- Teardown ---
    unloadRenderer(renderer); // Unload graphics
    CloseWindow();

    return 0;
}