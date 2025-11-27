#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include "../grid/board.hpp"
#include "../input/input.hpp"
#include "../colors/customColourPalette.hpp"
#include "../colors/candyCrushPalette.hpp"

const int MAXCANDYCOLORS{6}; // red,yellow,green,blue,orange,bomb

const int TILE_SIZE{64};
const int MAX_IN_GAME_BUTTONS{2};
const int MAX_MENU_BUTTONS{4}; // newgame , continue, settings , exit

enum ButtonAction
{
    ACTION_NEW_GAME,
    ACTION_LOAD_GAME,
    ACTION_SETTINGS,
    ACTION_EXIT,
    ACTION_BACK_TO_MAIN_MENU
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
    Texture2D candyTexture;  // candy sprite sheet
    Texture2D buttonTexture; // button sprite sheet
    Font logoFont;          // logo font
    Button menuButtons[MAX_MENU_BUTTONS]; // array of Buttons for menu
    Button gameButtons[MAX_IN_GAME_BUTTONS];   // array of Buttons for in-game
    Rectangle plainCandySourceRecs[MAXCANDYCOLORS];
    Rectangle wrappedCandySourceRecs[MAXCANDYCOLORS - 1];
    Rectangle horiStripedCandySourceRecs[MAXCANDYCOLORS - 1];
    Rectangle vertStripedCandySourceRecs[MAXCANDYCOLORS - 1];
    Vector2 gridOffset; // distance from top-left corner to grid start
};

Renderer initRenderer();
void unloadRenderer(Renderer &renderer);
void drawBoard(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection);
void drawButton(const Renderer &renderer, const Button &btn);
void drawMenu(const Renderer &renderer);
void drawColoredLogo(const char logoText[], Renderer renderer,float fontSizeMultiplier,Vector2 startingPos);
void drawGameScreen(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection, int score, int movesLeft, int targetScore);
#endif