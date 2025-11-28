#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "../frontend/renderer.hpp"
#include "../grid/board.hpp"
#include "../input/input.hpp"
#include "../audio/audio.hpp"
#include "../frontend/settings/settings.hpp"


enum GameState
{
    INPUT,
    SWAPPING,
    REVERSING,
    PROCESSING_MATCHES,
    ANIMATING_FALL
};

enum GamePage
{
    MAIN_MENU,
    IN_GAME,
    SETTINGS,
    INSTRUCTION_PAGE
};

struct Game
{
    Board gameBoard;
    Audio gameAudio;
    Renderer renderer;
    GameState currentState;
    GamePage currentPage;
    GamePage previousPage;
    GameSettings settings;
    int targetScore;
    int score;
    int movesLeft;
    bool isGameOver;
    bool isCloseRequested;
};

void handleGameClosure(Game &currentGame);
void handleOnClickFunction(ButtonAction action, Game &currentGame);

#endif
