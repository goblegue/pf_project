#include "raylib.h"
#include "renderer.hpp"

#include "board.hpp"
#include "input.hpp"

enum GameState
{
    INPUT,
    SWAPPING,
    REVERSING,
    PROCESSING
};

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 850;

    const float SWAP_SPEED = 300.0f;
    const float FALL_SPEED = 350.0f;
    InitWindow(screenWidth, screenHeight, "Candy Crush");
    SetTargetFPS(60);

    // --- Setup ---
    Board gameBoard;

    Renderer renderer = initRenderer(screenWidth, screenHeight); // Initialize graphics
    initializeGrid(gameBoard, renderer.gridOffset, TILE_SIZE);   // Initialize game logic

    SelectedCandy selection{};       // To track selected candy
    swappedCandies swappedcandies{}; // To track swapped candies

    int score{};
    GameState currentState = INPUT;

    // --- Main Game Loop ---
    while (!WindowShouldClose())
    {
        float currAniSpeed = FALL_SPEED;

        if (currentState == SWAPPING || currentState == REVERSING)
        {
            currAniSpeed = SWAP_SPEED;
        }

        bool isMoving = animatBoard(gameBoard, renderer.gridOffset, TILE_SIZE, currAniSpeed);

        switch (currentState)
        {
        case INPUT:
            if (!isMoving)
            {
                if (handleMouseInput(gameBoard, selection, renderer.gridOffset, TILE_SIZE))
                {
                    swappedcandies = getSwappedCandies();
                    swapCandies(gameBoard, swappedcandies.candy1row, swappedcandies.candy1column, swappedcandies.candy2row, swappedcandies.candy2column);
                    currentState = SWAPPING;
                }
            }
            break;
        case SWAPPING:
            if (!isMoving)
            {
                if (isPartOfMatch(gameBoard, swappedcandies.candy1row, swappedcandies.candy1column) || isPartOfMatch(gameBoard, swappedcandies.candy2row, swappedcandies.candy2column))
                {
                    currentState = PROCESSING;
                }
                else
                {
                    swapCandies(gameBoard, swappedcandies.candy1row, swappedcandies.candy1column, swappedcandies.candy2row, swappedcandies.candy2column);
                    currentState = REVERSING;
                }
            }
            break;
        case REVERSING:
            if (!isMoving)
            {
                currentState = INPUT;
            }
            break;
        case PROCESSING:
            score += handleMatchAndRefill(gameBoard, swappedcandies, renderer.gridOffset, TILE_SIZE);
            currentState = INPUT;
            break;
        default:
            break;
        }

        // if(isMoving) {
        //     gameState = Animating;
        // } else {
        //     // Finished animating
        //     gameState = Playing;
        // }

        // if(gameState==Playing){

        //     Vector2 gridOffset ={renderer.gridOffset.x, renderer.gridOffset.y};

        //     // Handle input here...
        //     bool swapedOccure=handleMouseInput(gameBoard, selection,gridOffset,TILE_SIZE);
        //     swappedcandies=getSwappedCandies();

        //     if(swapedOccure){
        //         score+=handleMatchAndRefill(gameBoard, swappedcandies, gridOffset, TILE_SIZE);
        //     }
        // }

        // --- Drawing ---
        BeginDrawing();
        ClearBackground(DARKBROWN);

        // Pass both the game state and renderer to the draw function
        drawBoard(renderer, gameBoard, selection);
        DrawText(TextFormat("Score: %i", score), 50, 50, 20, YELLOW);

        EndDrawing();
    }

    // --- Teardown ---
    unloadRenderer(renderer); // Unload graphics
    CloseWindow();

    return 0;
}