#include "game.hpp"
#include "../db/fileHandler.hpp"

void handleGameClosure(Game &currentGame)
{
    unloadAudio(currentGame.gameAudio);
    unloadRenderer(currentGame.renderer);
    CloseAudioDevice();
    CloseWindow();
}

void handleOnClickFunction(ButtonAction action, Game &currentGame)
{
    switch (action)
    {
    case ACTION_NEW_GAME:
        initializeGrid(currentGame.gameBoard, currentGame.renderer.gridOffset, TILE_SIZE);
        currentGame.score = 0;
        currentGame.movesLeft = 20;
        currentGame.currentState = INPUT;
        currentGame.currentPage = IN_GAME;
        break;

    case ACTION_LOAD_GAME:

        if (loadBoardFromFile(currentGame.gameBoard, currentGame.targetScore, currentGame.score, currentGame.movesLeft, "savefile.txt"))
        {
            currentGame.currentState = INPUT;
            currentGame.currentPage = IN_GAME;
        }
        else
        {
            DrawText("Failed to load game!", 200, 200, 20, RED);
        }
        break;

    case ACTION_EXIT:
        currentGame.isCloseRequested = true;
        break;

    case ACTION_BACK_TO_MAIN_MENU:
        currentGame.currentPage = MAIN_MENU;
        break;
    case ACTION_SETTINGS:
        currentGame.previousPage = currentGame.currentPage;
        currentGame.currentPage = SETTINGS;
        break;
    default:
        break;
    }
}
