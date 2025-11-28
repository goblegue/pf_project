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
    ACTION_RETRY,      // New
    ACTION_NEXT_LEVEL  // New
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

Renderer initRenderer();
void unloadRenderer(Renderer &renderer);
void drawBoard(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection);
void drawButton(const Renderer &renderer, const Button &btn);
void drawMenu(const Renderer &renderer);
void drawColoredLogo(const char logoText[], Renderer renderer,float fontSizeMultiplier,Vector2 startingPos);
void drawGameScreen(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection, int score, int movesLeft, int targetScore);
void drawWinScreen(const Renderer &renderer, int finalScore); 
void drawLoseScreen(const Renderer &renderer);
#endif