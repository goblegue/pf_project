#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "frontend/renderer.hpp"
#include "grid/board.hpp"
#include "input/input.hpp"
#include "audio/audio.hpp"
#include "db/fileHandler.hpp"
#include "frontend/settings/settings.hpp"
#include "frontend/instructions/instruction.hpp"

#define dev;

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
    GameSettings settings;
    int targetScore;
    int score;
    int movesLeft;
    bool isGameOver;
    bool isCloseRequested;
};

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
        currentGame.currentPage = SETTINGS;
        break;
    default:
        break;
    }
}

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
    Game currentGame{};
    currentGame.renderer = initRenderer();                                             // Initialize graphics
    initializeGrid(currentGame.gameBoard, currentGame.renderer.gridOffset, TILE_SIZE); // Initialize game logic
    initAudio(currentGame.gameAudio, "assets/music/candy_crush_intro2.mp3", volume);   // Initialize audio
    currentGame.settings = initGameSettings("assets/styles/style_lavanda.rgs");                      // Initialize settings UI style
    SelectedCandy selection{};       // To track selected candy
    swappedCandies swappedcandies{}; // To track swapped candies
    currentGame.targetScore = 50000;
    currentGame.movesLeft = totalMoves;
    currentGame.currentState = INPUT;
    currentGame.currentPage = MAIN_MENU;

    playMusic(currentGame.gameAudio);
    // --- Main Game Loop ---
    while (!WindowShouldClose())
    {
        fallSpeed =(currentGame.settings.animationSpeed) * 50.0f;
        updateAudioStream(currentGame.gameAudio);
        if(currentGame.settings.isMusicOn==0 ){
            pauseMusic(currentGame.gameAudio);
        }
        else if(currentGame.settings.isMusicOn==1 ){
            playMusic(currentGame.gameAudio);
        }

        changeVolume(currentGame.gameAudio, currentGame.settings.Volume);

        if (currentGame.currentPage == MAIN_MENU)
        {
            // Draw Menu
            BeginDrawing();
            ClearBackground(CC_BG_DARK);
            drawMenu(currentGame.renderer);

            // handle button clicks
            for (int i = 0; i < MAX_MENU_BUTTONS; ++i)
            {
                if (isButtonPressed(currentGame.renderer.menuButtons[i]))
                {
                    handleOnClickFunction(currentGame.renderer.menuButtons[i].action, currentGame);
                }
            }
            EndDrawing();
            if (currentGame.isCloseRequested)
            {
                break;
            }
        }
        else if (currentGame.currentPage == SETTINGS)
        {
            BeginDrawing();
            ClearBackground(CC_BG_DARK);
            int nextPage=drawSettingsPage(currentGame.settings, currentGame.renderer);
            if (nextPage != SETTINGS) {
                currentGame.currentPage = (GamePage)nextPage;
            }
            EndDrawing();
        }
        else if (currentGame.currentPage == INSTRUCTION_PAGE)
        {
            BeginDrawing();
            ClearBackground(CC_BG_DARK);
            DrawInstructionPopup(currentGame.renderer.logoFont,screenWidth, screenHeight);
            // back to main menu button
            if (GuiButton({screenWidth / 2 - 100, screenHeight - 110, 200, 50}, "BACK TO MENU"))
            {
                currentGame.currentPage = MAIN_MENU;
            }
            EndDrawing();
        }
        else if (currentGame.currentPage == IN_GAME)
        {
            // --- Update ---
            float currAniSpeed = fallSpeed;

            if (currentGame.currentState == SWAPPING || currentGame.currentState == REVERSING)
            {
                currAniSpeed = SWAP_SPEED;
            }

            bool isMoving = animatBoard(currentGame.gameBoard, currentGame.renderer.gridOffset, TILE_SIZE, currAniSpeed);

            switch (currentGame.currentState)
            {
            case INPUT:
                if (!isMoving)
                {
                    if (handleMouseInput(selection, currentGame.renderer.gridOffset, TILE_SIZE))
                    {
                        swappedcandies = getSwappedCandies();
                        swapCandies(currentGame.gameBoard, swappedcandies.candy1row, swappedcandies.candy1column, swappedcandies.candy2row, swappedcandies.candy2column);
                        currentGame.currentState = SWAPPING;
                    }
                }
                break;
            case SWAPPING:
                if (!isMoving)
                {
                    if (handleSpecialInteraction(currentGame.gameBoard, swappedcandies))
                    {
                        currentGame.currentState = PROCESSING_MATCHES;
                    }
#ifndef Testing
                    else if (isPartOfMatch(currentGame.gameBoard, swappedcandies.candy1row, swappedcandies.candy1column) || isPartOfMatch(currentGame.gameBoard, swappedcandies.candy2row, swappedcandies.candy2column))
                    {
                        currentGame.movesLeft--;
                        currentGame.currentState = PROCESSING_MATCHES;
                    }
#endif

#ifdef Testing
                    else if (true) // Always true for testing purposes
                    {
                        currentGame.currentState = PROCESSING_MATCHES;
                    }
#endif
                    else
                    {
                        swapCandies(currentGame.gameBoard, swappedcandies.candy1row, swappedcandies.candy1column, swappedcandies.candy2row, swappedcandies.candy2column);
                        currentGame.currentState = REVERSING;
                    }
                }
                break;
            case REVERSING:
                if (!isMoving)
                {
                    currentGame.currentState = INPUT;
                }
                break;
            case PROCESSING_MATCHES:
            {
                bool deletedPresent = isDeletedPresent(currentGame.gameBoard);
                bool matchFound = findAndMarkFiveMatches(currentGame.gameBoard, swappedcandies) || findAndMarkFourMatches(currentGame.gameBoard, swappedcandies) || findAndMarkLorTshapeMatches(currentGame.gameBoard) || findAndMarkThreeMatches(currentGame.gameBoard);
                if (matchFound || deletedPresent)
                {
                    currentGame.score += getScoreFromMarkedCandies(currentGame.gameBoard);
                    applyGravity(currentGame.gameBoard, currentGame.renderer.gridOffset, TILE_SIZE);
                    refillBoard(currentGame.gameBoard, currentGame.renderer.gridOffset, TILE_SIZE);
                    currentGame.currentState = ANIMATING_FALL;
                }
                else
                {
                    saveBoardToFile(currentGame.gameBoard, currentGame.targetScore, currentGame.score, currentGame.movesLeft, "savefile.txt");
                    currentGame.currentState = INPUT;
                }
                break;
            }
            case ANIMATING_FALL:
            {

                if (!isMoving)
                {
                    currentGame.currentState = PROCESSING_MATCHES;
                }
                break;
            }
            default:

                break;
            }

            // Drawing
            BeginDrawing();
            ClearBackground(CC_BG_DARK);
            // handle button clicks
            for (int i = 0; i < MAX_IN_GAME_BUTTONS; ++i)
            {
                if (isButtonPressed(currentGame.renderer.gameButtons[i]))
                {
                    handleOnClickFunction(currentGame.renderer.gameButtons[i].action, currentGame);
                }
            }
            drawGameScreen(currentGame.renderer, currentGame.gameBoard, selection, currentGame.score, currentGame.movesLeft, currentGame.targetScore);
            EndDrawing();
            if (currentGame.isCloseRequested)
            {
                break;
            }
        }
    }

    // --- Teardown ---
    handleGameClosure(currentGame);

    return 0;
}