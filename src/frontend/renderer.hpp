#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include "../grid/board.hpp"
#include "../input/input.hpp"
#include "../colors/customColourPalette.hpp"
#include "../colors/candyCrushPalette.hpp"

const int MAXCANDYCOLORS{6};

const int TILE_SIZE{64};
const int MAX_IN_GAME_BUTTONS{2};
const int MAX_MENU_BUTTONS{4};
const int MAX_WIN_BUTTONS{2};
const int MAX_LOSE_BUTTONS{2};

enum ButtonAction
{
    ACTION_NEW_GAME,
    ACTION_LOAD_GAME,
    ACTION_SETTINGS,
    ACTION_EXIT,
    ACTION_BACK_TO_MAIN_MENU,
    ACTION_RETRY,     // New
    ACTION_NEXT_LEVEL // New
};

struct Button
{
    Rectangle sourceRec;
    Rectangle bounds;
    char label[32];
    bool isClicked;
    ButtonAction action;
    char buttonInstruction[128];
};

struct Renderer
{
    Texture2D candyTexture;
    Texture2D buttonTexture;
    Texture2D characterTexture;
    Font logoFont;
    Button menuButtons[MAX_MENU_BUTTONS];
    Button gameButtons[MAX_IN_GAME_BUTTONS];
    Button winButtons[MAX_WIN_BUTTONS];
    Button loseButtons[MAX_LOSE_BUTTONS];
    Rectangle plainCandySourceRecs[MAXCANDYCOLORS];
    Rectangle wrappedCandySourceRecs[MAXCANDYCOLORS - 1];
    Rectangle horiStripedCandySourceRecs[MAXCANDYCOLORS - 1];
    Rectangle vertStripedCandySourceRecs[MAXCANDYCOLORS - 1];
    Rectangle winPanelRect[5];
    Rectangle losePanelRect[1];
    Vector2 gridOffset;
};

/**
 * @brief initializes the renderer
 * @returns the initialized renderer
 */
Renderer initRenderer();

/**
 * @brief unloads the renderer
 * @param renderer the renderer
 */
void unloadRenderer(Renderer &renderer);

/**
 * @brief draws the board
 * @param renderer the renderer
 * @param gameBoard the game board
 * @param selection the selected candy
 */
void drawBoard(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection);

/**
 * @brief draws a button
 * @param renderer the renderer
 * @param btn the button
 */
void drawButton(const Renderer &renderer, const Button &btn);

/**
 * @brief draws the menu
 * @param renderer the renderer
 */
void drawMenu(const Renderer &renderer);

/**
 * @brief draws the colored logo
 * @param logoText the text of the logo
 * @param renderer the renderer
 * @param fontSizeMultiplier the font size multiplier
 * @param startingPos the starting position
 */
void drawColoredLogo(const char logoText[], Renderer renderer, float fontSizeMultiplier, Vector2 startingPos);

/**
 * @brief draws the game screen
 * @param renderer the renderer
 * @param gameBoard the game board
 * @param selection the selected candy
 * @param score the current score
 * @param movesLeft the remaining moves
 * @param targetScore the target score
 */
void drawGameScreen(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection, int score, int movesLeft, int targetScore);

/**
 * @brief draws the win screen
 * @param renderer the renderer
 * @param finalScore the final score
 */
void drawWinScreen(const Renderer &renderer, int finalScore);

/**
 * @brief draws the lose screen
 * @param renderer the renderer
 */
void drawLoseScreen(const Renderer &renderer);
#endif