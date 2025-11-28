#define RAYGUI_IMPLEMENTATION

#include "game/game.hpp"
#include "db/fileHandler.hpp"
#include "frontend/instructions/instruction.hpp"

#define dev ;

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 850;

    const int totalMoves{20};

    const float SWAP_SPEED = 300.0f;
#ifndef Testing
    float fallSpeed = 300.0f;
#endif
#ifdef Testing
    float fallSpeed = 150.0f;
#endif

    float volume{1.0f};
    InitWindow(screenWidth, screenHeight, "Candy Crush");
    InitAudioDevice();
    SetTargetFPS(60);

    // --- Setup ---
    Game currentGame = initializeGame();

    playMusic(currentGame.currentAudio);
    // --- Main Game Loop ---
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(CC_BG_DARK);
        drawGame(currentGame);
        EndDrawing();
        if (currentGame.isCloseRequested)
        {
            break;
        }
    }

    // --- Teardown ---
    handleGameClosure(currentGame);

    return 0;
}