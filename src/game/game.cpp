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
        currentGame.gameBoard = initializeGrid(currentGame.renderer.gridOffset, TILE_SIZE);
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

Game initializeGame()
{
    Game newGame{};
    newGame.renderer = initRenderer();
    newGame.gameBoard = initializeGrid(newGame.renderer.gridOffset, TILE_SIZE);
    newGame.settings = initGameSettings("assets/styles/style_lavanda.rgs");
    newGame.introAudio = initAudio("assets/music/candy_crush_intro2.mp3", newGame.settings.Volume);
    newGame.fallSpeed = 300.0f;
    newGame.swapSpeed = 300.0f;
    newGame.targetScore= 10000;
    newGame.currentState = INPUT;
    newGame.currentPage = MAIN_MENU;
    newGame.previousPage = MAIN_MENU;
    newGame.score = 0;
    newGame.movesLeft = 20;
    newGame.isGameOver = false;
    newGame.isCloseRequested = false;
    newGame.currentAudio = newGame.introAudio;

    return newGame;
}


