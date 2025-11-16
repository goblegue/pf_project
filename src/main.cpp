#include "raylib.h"
#include "board.hpp"
#include "renderer.hpp"
#include "input.hpp"

enum GameState {
    Playing,
    Animating
};

int main() {
    const int screenWidth = 545;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Candy Crush");
    SetTargetFPS(60);

    // --- Setup ---
    Board gameBoard;
    initializeGrid(gameBoard); // Initialize game logic

    Renderer renderer = initRenderer(screenWidth, screenHeight); // Initialize graphics

    SelectedCandy selection{}; // To track selected candy

    int score{};
    GameState gameState = Playing;

    // --- Main Game Loop ---
    while (!WindowShouldClose()) {
        bool isMoving = animationBoard(gameBoard, renderer.gridOffset, TILE_SIZE);

        if(isMoving) {
            gameState = Animating;
        } else {
            // Finished animating
            gameState = Playing;
        }

        if(gameState==Playing){

            Vector2 gridOffset ={renderer.gridOffset.x, renderer.gridOffset.y};
            
            // Handle inp6ut here...
            bool swapedOccure=handleMouseInput(gameBoard, selection,gridOffset,TILE_SIZE);
            
            if(swapedOccure){
                score+=handleMatchAndRefill(gameBoard, gridOffset, TILE_SIZE);
            }
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