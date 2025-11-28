#include "game.hpp"
#include "../db/fileHandler.hpp"
#include "../frontend/instructions/instruction.hpp"
#include "../utils/CharUtils.hpp"

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
        switch (currentGame.settings.difficultyMode)
        {
        case 0:
            currentGame.targetScore = 5000;
            break;
        case 1:
            currentGame.targetScore = 10000;
            break;
        case 2:
            currentGame.targetScore = 15000;
            break;
        case 3:
            currentGame.targetScore = 20000;
            break;
        default:
            currentGame.targetScore = 10000;
            break;
        }
        switchAudio(currentGame.currentAudio, currentGame.gameAudio);
        break;

    case ACTION_LOAD_GAME:

        if (loadBoardFromFile(currentGame.gameBoard, currentGame.targetScore, currentGame.score, currentGame.movesLeft, "savefile.txt"))
        {
            currentGame.currentState = INPUT;
            currentGame.currentPage = IN_GAME;
            // switchAudio(currentGame.currentAudio, currentGame.gameAudio);
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
        switchAudio(currentGame.currentAudio, currentGame.introAudio);
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
    newGame.introAudio = initAudio("assets/music/candy_crush_intro2.ogg", newGame.settings.Volume);
    newGame.outroAudio = initAudio("assets/music/candy_crush_outro1.ogg", newGame.settings.Volume);
    newGame.gameAudio = initAudio("assets/music/candy_crush_loop5.ogg", newGame.settings.Volume);
    newGame.fallSpeed = 300.0f;
    newGame.swapSpeed = 300.0f;
    newGame.targetScore = 10000;
    newGame.currentState = INPUT;
    newGame.currentPage = MAIN_MENU;
    newGame.previousPage = MAIN_MENU;
    newGame.score = 0;
    newGame.movesLeft = 20;
    newGame.isGameOver = false;
    newGame.isCloseRequested = false;
    newGame.previousMusicTrack = 0;
    newGame.currentAudio = newGame.introAudio;

    return newGame;
}

void drawGame(Game &currentGame)
{

    currentGame.fallSpeed = (currentGame.settings.animationSpeed) * 50.0f;
    updateAudioStream(currentGame.currentAudio);
    if (currentGame.previousMusicTrack != currentGame.settings.gameMusicTrack)
    {
        char selectedMusicPath[60];

        if (currentGame.settings.gameMusicTrack == 0)
        {
            charAssignment(selectedMusicPath, "assets/music/candy_crush_loop5.ogg");
        }
        else if (currentGame.settings.gameMusicTrack == 1)
        {
            charAssignment(selectedMusicPath, "assets/music/candy_crush_soundtrack2.ogg");
        }
        else if (currentGame.settings.gameMusicTrack == 2)
        {
            charAssignment(selectedMusicPath, "assets/music/candy_crush_soundtrack3.ogg");
        }
        else if (currentGame.settings.gameMusicTrack == 3)
        {
            charAssignment(selectedMusicPath, "assets/music/candy_crush_soundtrack4.ogg");
        }
        else if (currentGame.settings.gameMusicTrack == 4)
        {
            charAssignment(selectedMusicPath, "assets/music/SA_Game_mode_mixed_modes_loop.ogg");
        }

        changeMusic(currentGame.gameAudio, selectedMusicPath);
        if (currentGame.currentPage == IN_GAME || currentGame.previousPage == IN_GAME)
        {
            currentGame.currentAudio = currentGame.gameAudio;
        }
        currentGame.previousMusicTrack = currentGame.settings.gameMusicTrack;
    }

    if (currentGame.settings.isMusicOn == 0)
    {
        pauseMusic(currentGame.currentAudio);
    }
    else if (currentGame.settings.isMusicOn == 1)
    {
        playMusic(currentGame.currentAudio);
    }

    changeVolume(currentGame.currentAudio, currentGame.settings.Volume);

    if (currentGame.currentPage == MAIN_MENU)
    {
        drawMenu(currentGame.renderer);

        // handle button clicks
        for (int i = 0; i < MAX_MENU_BUTTONS; ++i)
        {
            if (isButtonPressed(currentGame.renderer.menuButtons[i]))
            {
                handleOnClickFunction(currentGame.renderer.menuButtons[i].action, currentGame);
            }
        }
    }
    else if (currentGame.currentPage == SETTINGS)
    {
        int nextPage = drawSettingsPage(currentGame.settings, currentGame.renderer, currentGame.previousPage);
        if (nextPage != SETTINGS)
        {
            currentGame.currentPage = (GamePage)nextPage;
        }
    }
    else if (currentGame.currentPage == INSTRUCTION_PAGE)
    {
        currentGame.currentPage = static_cast<GamePage>(DrawInstructionPopup(currentGame.renderer.logoFont, currentGame.previousPage));
    }
    else if (currentGame.currentPage == IN_GAME)
    {
        // --- Update ---
        float currAniSpeed = currentGame.fallSpeed;

        if (currentGame.currentState == SWAPPING || currentGame.currentState == REVERSING)
        {
            currAniSpeed = currentGame.swapSpeed;
        }

        bool isMoving = animatBoard(currentGame.gameBoard, currentGame.renderer.gridOffset, TILE_SIZE, currAniSpeed);

        switch (currentGame.currentState)
        {
        case INPUT:
            if (!isMoving)
            {
                if (handleMouseInput(currentGame.selection, currentGame.renderer.gridOffset, TILE_SIZE))
                {
                    currentGame.swappedcandies = getSwappedCandies();
                    swapCandies(currentGame.gameBoard, currentGame.swappedcandies.candy1row, currentGame.swappedcandies.candy1column, currentGame.swappedcandies.candy2row, currentGame.swappedcandies.candy2column);
                    currentGame.currentState = SWAPPING;
                }
            }
            break;
        case SWAPPING:
            if (!isMoving)
            {
                if (handleSpecialInteraction(currentGame.gameBoard, currentGame.swappedcandies))
                {
                    currentGame.currentState = PROCESSING_MATCHES;
                }
#ifndef Testing
                else if (isPartOfMatch(currentGame.gameBoard, currentGame.swappedcandies.candy1row, currentGame.swappedcandies.candy1column) || isPartOfMatch(currentGame.gameBoard, currentGame.swappedcandies.candy2row, currentGame.swappedcandies.candy2column))
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
                    swapCandies(currentGame.gameBoard, currentGame.swappedcandies.candy1row, currentGame.swappedcandies.candy1column, currentGame.swappedcandies.candy2row, currentGame.swappedcandies.candy2column);
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
            bool matchFound = findAndMarkFiveMatches(currentGame.gameBoard, currentGame.swappedcandies) || findAndMarkFourMatches(currentGame.gameBoard, currentGame.swappedcandies) || findAndMarkLorTshapeMatches(currentGame.gameBoard) || findAndMarkThreeMatches(currentGame.gameBoard);
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
                if (currentGame.score < currentGame.targetScore && currentGame.movesLeft <= 0)
                {
                    currentGame.currentPage = LOSE_PAGE;
                    switchAudio(currentGame.currentAudio, currentGame.outroAudio);
                }
                else if (currentGame.score >= currentGame.targetScore)
                {
                    currentGame.currentPage = WIN_PAGE;
                    switchAudio(currentGame.currentAudio, currentGame.outroAudio);
                }
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
        // handle button clicks
        for (int i = 0; i < MAX_IN_GAME_BUTTONS; ++i)
        {
            if (isButtonPressed(currentGame.renderer.gameButtons[i]))
            {
                handleOnClickFunction(currentGame.renderer.gameButtons[i].action, currentGame);
            }
        }
        drawGameScreen(currentGame.renderer, currentGame.gameBoard, currentGame.selection, currentGame.score, currentGame.movesLeft, currentGame.targetScore);
    }
    else if (currentGame.currentPage == WIN_PAGE)
    {
        drawWinScreen(currentGame.renderer, currentGame.score);

        // handle button clicks
        for (int i = 0; i < MAX_WIN_BUTTONS; ++i)
        {
            if (isButtonPressed(currentGame.renderer.winButtons[i]))
            {
                handleOnClickFunction(currentGame.renderer.winButtons[i].action, currentGame);
            }
        }
    }
    else if (currentGame.currentPage == LOSE_PAGE)
    {
        drawLoseScreen(currentGame.renderer);

        // handle button clicks
        for (int i = 0; i < MAX_LOSE_BUTTONS; ++i)
        {
            if (isButtonPressed(currentGame.renderer.loseButtons[i]))
            {
                handleOnClickFunction(currentGame.renderer.loseButtons[i].action, currentGame);
            }
        }
    }
}
