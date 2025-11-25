#include "renderer.hpp"
#include "../utils/CharUtils.hpp"

const float TOP_MARGIN = 0.28f;           // Top margin as a fraction of window height
const float TILE_BORDER_THICKNESS = 1.0f; // Thickness of the border around each tile

Renderer initRenderer()
{
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    Renderer renderer{};
    renderer.candyTexture = LoadTexture("assets/textures/candies.png");     // Load candy sprite sheet
    renderer.buttonTexture = LoadTexture("assets/textures/Menu_Icons.png"); // Load button sprite sheet
    renderer.logoFont = LoadFont("assets/fonts/logo.png");                  // Load logo font

    Rectangle BigPinkButton{};
    BigPinkButton.x = 735;
    BigPinkButton.y = 0;
    BigPinkButton.width = 265;
    BigPinkButton.height = 110;

    Rectangle SmallBlueButton{};
    SmallBlueButton.x = 734;
    SmallBlueButton.y = 510;
    SmallBlueButton.width = 265;
    SmallBlueButton.height = 75;

    Rectangle RED_EXIT_BUTTON{405, 130, 95, 90};
    Rectangle SETTINGS_BUTTON{510, 90, 95, 95};

    // plain candy source rectangles
    renderer.plainCandySourceRecs[Red] = {0.0f, 740.0f, 100.0f, 100.0f};     // location of red candy in sprite sheet
    renderer.plainCandySourceRecs[Yellow] = {500.0f, 640.0f, 85.0f, 100.0f}; // location of yellow candy in sprite sheet
    renderer.plainCandySourceRecs[Green] = {0.0f, 640.0f, 100.0f, 100.0f};   // location of green candy in sprite sheet
    renderer.plainCandySourceRecs[Blue] = {620.0f, 550.0f, 100.0f, 100.0f};  // location of blue candy in sprite sheet
    renderer.plainCandySourceRecs[Orange] = {95.0f, 830.0f, 100.0f, 100.0f}; // location of orange candy in sprite sheet
    renderer.plainCandySourceRecs[Bomb] = {95.0f, 540.0f, 100.0f, 100.0f};   // location of bomb in sprite sheet

    // wrapped candy source rectangles
    renderer.wrappedCandySourceRecs[Red] = {430.0f, 450.0f, 100.0f, 100.0f};    // location of red wrapped candy in sprite sheet
    renderer.wrappedCandySourceRecs[Orange] = {510.0f, 547.0f, 100.0f, 100.0f}; // location of orange wrapped candy in sprite sheet
    renderer.wrappedCandySourceRecs[Yellow] = {630.0f, 90.0f, 100.0f, 100.0f};  // location of yellow wrapped candy in sprite sheet
    renderer.wrappedCandySourceRecs[Green] = {655.0f, 210.0f, 100.0f, 100.0f};  // location of green wrapped candy in sprite sheet
    renderer.wrappedCandySourceRecs[Blue] = {745.0f, 0.0f, 100.0f, 90.0f};      // location of blue wrapped candy in sprite sheet

    // horizontal striped candy source rectangles
    renderer.horiStripedCandySourceRecs[Red] = {200.0f, 740.0f, 100.0f, 100.0f};   // location of red horizontally striped candy in sprite sheet
    renderer.horiStripedCandySourceRecs[Orange] = {380.0f, 740.0f, 90.0f, 100.0f}; // location of orange horizontally striped candy in sprite sheet
    renderer.horiStripedCandySourceRecs[Yellow] = {690.0f, 655.0f, 85.0f, 90.0f};  // location of yellow horizontally striped candy in sprite sheet
    renderer.horiStripedCandySourceRecs[Green] = {295.0f, 740.0f, 100.0f, 100.0f}; // location of green horizontally striped candy in sprite sheet
    renderer.horiStripedCandySourceRecs[Blue] = {300.0f, 635.0f, 100.0f, 100.0f};  // location of blue horizontally striped candy in sprite sheet

    renderer.vertStripedCandySourceRecs[Red] = {400.0f, 640.0f, 100.0f, 100.0f};   // location of red vertically striped candy in sprite sheet
    renderer.vertStripedCandySourceRecs[Orange] = {575.0f, 740.0f, 85.0f, 100.0f}; // location of orange vertically striped candy in sprite sheet
    renderer.vertStripedCandySourceRecs[Yellow] = {837.0f, 95.0f, 85.0f, 90.0f};   // location of yellow vertically striped candy in sprite sheet
    renderer.vertStripedCandySourceRecs[Green] = {95.0f, 740.0f, 100.0f, 100.0f};  // location of green vertically striped candy in sprite sheet
    renderer.vertStripedCandySourceRecs[Blue] = {200.0f, 640.0f, 100.0f, 100.0f};  // location of blue vertically striped candy in sprite sheet

    renderer.gridOffset.x = (windowWidth - (MAX_COLUMNS * TILE_SIZE)) / 2.0f; // center the grid horizontally
    renderer.gridOffset.y = windowHeight * TOP_MARGIN;                        // set the distance from top to grid start
    // menu buttons
    renderer.menuButtons[ACTION_NEW_GAME] =
        {BigPinkButton,
         {windowWidth / 2.0f - 170.0f, windowHeight * 0.51f, 350.0f, 120.0f},
         "NEW GAME",
         false,
         ACTION_NEW_GAME,
         "Start a new game"};

    renderer.menuButtons[ACTION_LOAD_GAME] =
        {SmallBlueButton,
         {windowWidth / 2.0f - 165.0f, windowHeight * 0.665f, 350.0f, 85.0f},
         "LOAD GAME",
         false,
         ACTION_LOAD_GAME,
         "Load a previously saved game"};

    renderer.menuButtons[ACTION_SETTINGS] = {
        SETTINGS_BUTTON,
        {windowWidth - 100.0f, windowHeight - 110.0f, 70.0f, 70.0f},
        "",
        false,
        ACTION_SETTINGS,
        "Open Settings Menu"};

    renderer.menuButtons[ACTION_EXIT] = {
        RED_EXIT_BUTTON,
        {40.0f, windowHeight - 110.0f, 70.0f, 70.0f},
        "",
        false,
        ACTION_EXIT,
        "Save and Exit the game"};

    // in_game buttons
    renderer.gameButtons[0] = {
        SETTINGS_BUTTON,
        {renderer.gridOffset.x + (TILE_SIZE * (MAX_COLUMNS - 1)) + 10, 50, 55.0f, 55.0f},
        "",
        false,
        ACTION_SETTINGS,
        "Open In-Game Settings"};

    renderer.gameButtons[1] = {
        RED_EXIT_BUTTON,
        {renderer.gridOffset.x + 5, 50.0f, 55.0f, 55.0f},
        "",
        false,
        ACTION_EXIT,
        "Save and Exit the game"};
    return renderer;
}

void unloadRenderer(Renderer &renderer)
{
    UnloadTexture(renderer.candyTexture);
    UnloadTexture(renderer.buttonTexture);
    UnloadFont(renderer.logoFont);
}

void drawBoard(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection)
{
    for (int row = 0; row < MAX_ROWS; ++row)
    {
        for (int col = 0; col < MAX_COLUMNS; ++col)
        {
            Candy candy = gameBoard.candyGrid[row][col];
            Vector2 drawPos = candy.currentPos;

            Vector2 position = getTargetPos(row, col, renderer.gridOffset, TILE_SIZE);

            DrawRectangle(position.x, position.y, TILE_SIZE, TILE_SIZE, CC_GRID_BG);
            DrawRectangleLines(position.x, position.y, TILE_SIZE, TILE_SIZE, Fade(WHITE, 0.2f));

            if (selection.isSelected && selection.row == row && selection.column == col)
            {
                // Make it a glowing white box instead of solid Yellow
                DrawRectangle(position.x, position.y, TILE_SIZE, TILE_SIZE, CC_SELECTION);
                DrawRectangleLinesEx({position.x, position.y, (float)TILE_SIZE, (float)TILE_SIZE}, 3.0f, WHITE);
            }

            if (!candy.isMarkedDeletion)
            {
                Rectangle sourceRec;
                switch (candy.type)
                {
                case Wrapped:
                    sourceRec = renderer.wrappedCandySourceRecs[candy.color];
                    break;
                case Striped_horizontal:
                    sourceRec = renderer.horiStripedCandySourceRecs[candy.color];
                    break;
                case Striped_vertical:
                    sourceRec = renderer.vertStripedCandySourceRecs[candy.color];
                    break;
                default:
                    sourceRec = renderer.plainCandySourceRecs[candy.color];
                    break;
                }
                DrawTexturePro(renderer.candyTexture, sourceRec, {drawPos.x, drawPos.y, (float)TILE_SIZE, (float)TILE_SIZE}, {0, 0}, 0.0f, WHITE);
            }
        }
    }
}

// From raylib examples
void drawButtonInstruction(const Button &btn)
{
    int fontSize = 15;
    int padding = 10;
    int distanceFromButton = 2;
    Color boxColor = RAYWHITE;
    Color textColor = BLACK;
    Color borderColor = LIGHTGRAY;

    Vector2 textSize = MeasureTextEx(GetFontDefault(), btn.buttonInstruction, (float)fontSize, 1.0f);

    float posX = btn.bounds.x + (btn.bounds.width / 2) - (textSize.x / 2);
    float posY = btn.bounds.y - textSize.y - (padding * 2) - distanceFromButton;

    if (posX < 20)
        posX = 20;
    if (posY < 0)
        posY = btn.bounds.y + btn.bounds.height + distanceFromButton;
    if (posX + textSize.x + (padding * 2) > GetScreenWidth())
        posX = GetScreenWidth() - textSize.x - (padding * 2) - 10;

    Rectangle boxRect = {
        posX - padding,
        posY - padding,
        textSize.x + (padding * 2),
        textSize.y + (padding * 2)};

    DrawRectangleRec(boxRect, boxColor);
    DrawRectangleLinesEx(boxRect, 2, borderColor);

    DrawTextEx(GetFontDefault(), btn.buttonInstruction, (Vector2){posX, posY}, (float)fontSize, 1.0f, textColor);
}

void drawButton(const Renderer &renderer, const Button &btn)
{
    // check hover and click state
    Vector2 mousePos = GetMousePosition();
    bool isHovering = CheckCollisionPointRec(mousePos, btn.bounds);

    Color tint = WHITE;
    if (btn.isClicked)
        tint = GRAY;
    else if (isHovering){
        tint = LIGHTGRAY;
        drawButtonInstruction(btn);
    }
    else if (isHovering && btn.label == "")
    {
    }
    // draw button background
    DrawTexturePro(renderer.buttonTexture, btn.sourceRec, btn.bounds, {0, 0}, 0.0f, tint);

    // draw button label
    int fontSize = 30;

    int textWidth = MeasureText(btn.label, fontSize);

    int textX = btn.bounds.x + (btn.bounds.width / 2) - (textWidth / 2);
    int textY = btn.bounds.y + (btn.bounds.height / 2) - (fontSize / 2);

    DrawText(btn.label, textX + 2, textY + 2, fontSize, BLACK); // shadow
    DrawText(btn.label, textX, textY, fontSize, GOLD);
}

void drawColoredLogo(const char logoText[], Renderer renderer, float fontSizeMultiplier, Vector2 startingPos)
{
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    float fontSize = renderer.logoFont.baseSize * fontSizeMultiplier;
    Color colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int textLength = lengthOfCharArray(logoText);
    Vector2 currentPos = startingPos;
    for (int i = 0; i < textLength; i++)
    {
        float spaceing = 0.57f;
        char currentChar = logoText[i];
        char charStr[3];
        charToString(currentChar, charStr);
        Color currentColor = WHITE;
        if (currentChar != ' ')
        {
            currentColor = colors[i % 6];
        }
        else
        {
            spaceing = 1.2f;
        }
        DrawTextEx(renderer.logoFont, charStr, currentPos, fontSize, spaceing, currentColor);
        int charWidth = MeasureText(charStr, fontSize);
        currentPos.x += charWidth * spaceing;
    }
}

void drawMenu(const Renderer &renderer)
{
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    // draw logo
    drawColoredLogo("CANDY CRUSH", renderer, 7.0, (Vector2){windowWidth / 2.0f - 260.0f, windowHeight / 2.0f - 300});
    // draw all menu buttons
    for (int i = 0; i < MAX_MENU_BUTTONS; i++)
    {
        drawButton(renderer, renderer.menuButtons[i]);
    }
}

void drawGameScreen(const Renderer &renderer, const Board &gameBoard, const SelectedCandy &selection, int score, int movesLeft, int targetScore)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    for (int i{0}; i < MAX_IN_GAME_BUTTONS; ++i)
    {
        drawButton(renderer, renderer.gameButtons[i]);
    }

    drawColoredLogo("CANDY CRUSH", renderer, 4, (Vector2){screenWidth / 2.0f - 150, 40});
    DrawText(TextFormat("Score: %i", score), renderer.gridOffset.x + 10, renderer.gridOffset.y - 40, 20, CC_TEXT_GOLD);
    DrawText(TextFormat("Target Score: %i", targetScore), renderer.gridOffset.x + 10, renderer.gridOffset.y - 80, 22, CC_TEXT_GOLD);
    DrawText(TextFormat("Moves Left: %i", movesLeft), renderer.gridOffset.x + (TILE_SIZE * (MAX_COLUMNS - 1)) - 100, renderer.gridOffset.y - 40, 20, CC_TEXT_GOLD);
    drawBoard(renderer, gameBoard, selection);
}