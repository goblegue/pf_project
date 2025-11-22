#include "raylib.h"
#include "renderer.hpp"

#include "board.hpp"
#include "input.hpp"

#define Prod ;

enum GameState
{
    INPUT,
    SWAPPING,
    REVERSING,
    PROCESSING_MATCHES,
    ANIMATING_FALL
};

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 850;

    const float SWAP_SPEED = 300.0f;
    const float FALL_SPEED = 300.0f;
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
                if (handleSpecialInteraction(gameBoard, swappedcandies))
                {
                    currentState = PROCESSING_MATCHES;
                }
#ifdef Prod
                else if (isPartOfMatch(gameBoard, swappedcandies.candy1row, swappedcandies.candy1column) || isPartOfMatch(gameBoard, swappedcandies.candy2row, swappedcandies.candy2column))
                {
                    currentState = PROCESSING_MATCHES;
                }
#endif

#ifdef Testing
                else if (true) // Always true for testing purposes
                {
                    currentState = PROCESSING_MATCHES;
                }
#endif
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
        case PROCESSING_MATCHES:
        {
            bool deletedPresent = isDeletedPresent(gameBoard);
            bool matchFound = findAndMarkFiveMatches(gameBoard, swappedcandies) || findAndMarkFourMatches(gameBoard, swappedcandies) || findAndMarkLorTshapeMatches(gameBoard) || findAndMarkThreeMatches(gameBoard);
            if (matchFound || deletedPresent)
            {
                score += getScoreFromMarkedCandies(gameBoard);
                applyGravity(gameBoard, renderer.gridOffset, TILE_SIZE);
                refillBoard(gameBoard, renderer.gridOffset, TILE_SIZE);
                currentState = ANIMATING_FALL;
            }
            else
            {
                currentState = INPUT;
            }
            break;
        }
        case ANIMATING_FALL:
        {

            if (!isMoving)
            {
                currentState = PROCESSING_MATCHES;
            }
            break;
        }
        default:

            break;
        }

        // --- Drawing ---
        BeginDrawing();
        ClearBackground(DARKBROWN);

        // Pass both the game grid and renderer to the draw function
        drawBoard(renderer, gameBoard, selection);
        DrawText(TextFormat("Score: %i", score), 50, 50, 20, YELLOW);

        EndDrawing();
    }

    // --- Teardown ---
    unloadRenderer(renderer); // Unload graphics
    CloseWindow();

    return 0;
}