#define RAYGUI_IMPLEMENTATION

#include "game/game.hpp"
#include "db/fileHandler.hpp"
#include "frontend/instructions/instruction.hpp"



int main()
{
    const int screenWidth = 640;
    const int screenHeight = 850;

    const int totalMoves{20};



    InitWindow(screenWidth, screenHeight, "Candy Crush");
    InitAudioDevice();
    SetTargetFPS(60);

    Game currentGame = initializeGame();

    playMusic(currentGame.currentAudio);
    
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

    
    handleGameClosure(currentGame);

    return 0;
}