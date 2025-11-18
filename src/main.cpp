#include "raylib.h"
#include "renderer.hpp"

#include "board.hpp"
#include "input.hpp"


int main() {
    const int screenWidth = 640;
    const int screenHeight = 850;
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