#include "renderer.hpp"
#include "../utils/CharUtils.hpp"

#define CHARACTER 0
#define RED_STAR 1
#define GREEN_STAR 2
#define YELLOW_STAR 3
#define SCORE_BAR 4

const float TOP_MARGIN = 0.28f;
const float TILE_BORDER_THICKNESS = 1.0f;

Renderer initRenderer()
{
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    Renderer renderer{};
    renderer.candyTexture = LoadTexture("assets/textures/candies.png");
    renderer.buttonTexture = LoadTexture("assets/textures/Menu_Icons.png");
    renderer.characterTexture = LoadTexture("assets/textures/Character.png");
    renderer.logoFont = LoadFont("assets/fonts/logo.png");

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

    renderer.plainCandySourceRecs[Red] = {0.0f, 740.0f, 100.0f, 100.0f};
    renderer.plainCandySourceRecs[Yellow] = {500.0f, 640.0f, 85.0f, 100.0f};
    renderer.plainCandySourceRecs[Green] = {0.0f, 640.0f, 100.0f, 100.0f};
    renderer.plainCandySourceRecs[Blue] = {620.0f, 550.0f, 100.0f, 100.0f};
    renderer.plainCandySourceRecs[Orange] = {95.0f, 830.0f, 100.0f, 100.0f};
    renderer.plainCandySourceRecs[Bomb] = {95.0f, 540.0f, 100.0f, 100.0f};

    renderer.wrappedCandySourceRecs[Red] = {430.0f, 450.0f, 100.0f, 100.0f};
    renderer.wrappedCandySourceRecs[Orange] = {510.0f, 547.0f, 100.0f, 100.0f};
    renderer.wrappedCandySourceRecs[Yellow] = {630.0f, 90.0f, 100.0f, 100.0f};
    renderer.wrappedCandySourceRecs[Green] = {655.0f, 210.0f, 100.0f, 100.0f};
    renderer.wrappedCandySourceRecs[Blue] = {745.0f, 0.0f, 100.0f, 90.0f};

    renderer.horiStripedCandySourceRecs[Red] = {200.0f, 740.0f, 100.0f, 100.0f};
    renderer.horiStripedCandySourceRecs[Orange] = {380.0f, 740.0f, 90.0f, 100.0f};
    renderer.horiStripedCandySourceRecs[Yellow] = {690.0f, 655.0f, 85.0f, 90.0f};
    renderer.horiStripedCandySourceRecs[Green] = {295.0f, 740.0f, 100.0f, 100.0f};
    renderer.horiStripedCandySourceRecs[Blue] = {300.0f, 635.0f, 100.0f, 100.0f};

    renderer.vertStripedCandySourceRecs[Red] = {400.0f, 640.0f, 100.0f, 100.0f};
    renderer.vertStripedCandySourceRecs[Orange] = {575.0f, 740.0f, 85.0f, 100.0f};
    renderer.vertStripedCandySourceRecs[Yellow] = {837.0f, 95.0f, 85.0f, 90.0f};
    renderer.vertStripedCandySourceRecs[Green] = {95.0f, 740.0f, 100.0f, 100.0f};
    renderer.vertStripedCandySourceRecs[Blue] = {200.0f, 640.0f, 100.0f, 100.0f};


    renderer.winPanelRect[CHARACTER] = {0.0f, 0.0f, 400.0f, 400.0f};
    renderer.winPanelRect[GREEN_STAR] = {230.0f, 620.0f, 140.0f, 140.0f};
    renderer.winPanelRect[RED_STAR] = {374.0f, 620.0f, 140.0f, 140.0f};
    renderer.winPanelRect[YELLOW_STAR] = {518.0f, 615.0f, 140.0f, 140.0f};
    renderer.winPanelRect[SCORE_BAR] = {350.0f, 982.0f, 320.0f, 25.0f};

    renderer.gridOffset.x = (windowWidth - (MAX_COLUMNS * TILE_SIZE)) / 2.0f;
    renderer.gridOffset.y = windowHeight * TOP_MARGIN;


    
    renderer.menuButtons[ACTION_NEW_GAME] = {BigPinkButton, {windowWidth / 2.0f - 170.0f, windowHeight * 0.51f, 350.0f, 120.0f}, "NEW GAME", false, ACTION_NEW_GAME, "Start a new game"};
    renderer.menuButtons[ACTION_LOAD_GAME] = {SmallBlueButton, {windowWidth / 2.0f - 165.0f, windowHeight * 0.665f, 350.0f, 85.0f}, "LOAD GAME", false, ACTION_LOAD_GAME, "Load a previously saved game"};
    renderer.menuButtons[ACTION_SETTINGS] = {SETTINGS_BUTTON, {windowWidth - 100.0f, windowHeight - 110.0f, 70.0f, 70.0f}, "", false, ACTION_SETTINGS, "Open Settings Menu"};
    renderer.menuButtons[ACTION_EXIT] = {RED_EXIT_BUTTON, {40.0f, windowHeight - 110.0f, 70.0f, 70.0f}, "", false, ACTION_EXIT, "Save and Exit the game"};

    renderer.gameButtons[0] = {SETTINGS_BUTTON, {renderer.gridOffset.x + (TILE_SIZE * (MAX_COLUMNS - 1)) + 10, 50, 55.0f, 55.0f}, "", false, ACTION_SETTINGS, "Open Settings Menu"};
    renderer.gameButtons[1] = {RED_EXIT_BUTTON, {renderer.gridOffset.x + 5, 50.0f, 55.0f, 55.0f}, "", false, ACTION_BACK_TO_MAIN_MENU, "Go Back to Main Menu"};



    renderer.winButtons[0] = {
        BigPinkButton, 
        (Rectangle){windowWidth/2 - 210, windowHeight/2 +50, 180, 80}, 
        "New Game", 
        false, 
        ACTION_NEW_GAME, 
        "New game"
    };


    renderer.winButtons[1] = {
        BigPinkButton, 
        (Rectangle){windowWidth/2 + 30, windowHeight/2 +50, 180, 80}, 
        "Main menu", 
        false, 
        ACTION_BACK_TO_MAIN_MENU, 
        "Back to Main Menu"
    };

    renderer.loseButtons[0] = {
        BigPinkButton, 
        (Rectangle){windowWidth/2 - 210, windowHeight/2 +50, 180, 80}, 
        "Retry", 
        false, 
        ACTION_NEW_GAME, 
        "Retry Again"
    };

    renderer.loseButtons[1] = {
        BigPinkButton, 
        (Rectangle){windowWidth/2 + 30, windowHeight/2 +50, 180, 80}, 
        "Main menu", 
        false, 
        ACTION_BACK_TO_MAIN_MENU, 
        "Back to Main Menu"
    };

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
    Color colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE};
    int textLength = lengthOfCharArray(logoText);
    Vector2 currentPos = startingPos;
    for (int i = 0; i < textLength; i++)
    {
        float spaceing = 0.57f;
        char currentChar = logoText[i];
        char charStr[2];
        charToString(currentChar, charStr);
        Color currentColor = WHITE;
        if (currentChar != ' ')
        {
            currentColor = colors[i % 5];
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



void drawWinScreen(const Renderer &renderer, int finalScore)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float panelW = 500.0f;
    float panelH = 550.0f;

    Rectangle panelRect = {
        (screenWidth - panelW) / 2.0f,
        (screenHeight - panelH) / 2.0f - 100.0f,
        panelW,
        panelH};
    
    
    DrawRectangleRounded((Rectangle){panelRect.x - 5, panelRect.y - 5, panelRect.width + 10, panelRect.height + 10}, 0.1f, 10, CC_TEXT_GOLD); // Dark Pink
    
    DrawRectangleRounded(panelRect, 0.1f, 10, LITE_PURPLE); // Beige/White

    
    const char title[] = "YOU WIN!";
    int titleSize = renderer.logoFont.baseSize * 4;
    int titleWidth = MeasureText(title, titleSize);
    DrawTextEx(renderer.logoFont,title,(Vector2) {panelRect.x + titleWidth/2-40, panelRect.y + 50}, titleSize,2.0f,LIME);

    DrawTexturePro(renderer.buttonTexture, renderer.winPanelRect[RED_STAR], {panelRect.x + panelRect.width / 2 - 160, panelRect.y + 150, 100, 100}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(renderer.buttonTexture, renderer.winPanelRect[YELLOW_STAR], {panelRect.x + panelRect.width / 2 - 50, panelRect.y + 140, 100, 100}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(renderer.buttonTexture, renderer.winPanelRect[GREEN_STAR], {panelRect.x + panelRect.width / 2 + 60, panelRect.y + 150, 100, 100}, {0, 0}, 0.0f, WHITE);

    DrawText("Score:", panelRect.x + 190, panelRect.y + 270, 35, {0, 150, 255, 255}); // Blue text
    
    DrawTexturePro(renderer.buttonTexture, renderer.winPanelRect[SCORE_BAR], {panelRect.x + panelRect.width / 2 - 205, panelRect.y + 320, 320, 50}, {0, 0}, 0.0f, WHITE);

    DrawText(TextFormat("%i", 15000), panelRect.x +200, panelRect.y + 330, 32, WHITE);

    for(int i = 0; i < MAX_WIN_BUTTONS; i++) {
        drawButton(renderer, renderer.winButtons[i]);
    }

}

void drawLoseScreen(const Renderer &renderer)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float panelW = 500.0f;
    float panelH = 550.0f;

    Rectangle panelRect = {
        (screenWidth - panelW) / 2.0f,
        (screenHeight - panelH) / 2.0f - 100.0f,
        panelW,
        panelH};
    
   
    DrawRectangleRounded((Rectangle){panelRect.x - 5, panelRect.y - 5, panelRect.width + 10, panelRect.height + 10}, 0.1f, 10, CC_TEXT_GOLD); // Dark Pink
    DrawRectangleRounded(panelRect, 0.1f, 10, LITE_PURPLE); 

    const char title[] = "YOU LOSE!";
    int titleSize = renderer.logoFont.baseSize * 5;
    int titleWidth = MeasureText(title, titleSize);
    DrawTextEx(renderer.logoFont,title,(Vector2) {panelRect.x +120, panelRect.y + 120}, titleSize,1.5f,{200, 60, 100, 255});

    const char msg[] = "Better luck next time!";
    int msgSize = renderer.logoFont.baseSize * 3;
    int msgWidth = MeasureText(msg, msgSize);
    DrawTextEx(renderer.logoFont,msg,(Vector2) {panelRect.x +50, panelRect.y + 220}, msgSize,1.0f,{200, 60, 100, 255});

    for(int i = 0; i < MAX_LOSE_BUTTONS; i++) {
        drawButton(renderer, renderer.loseButtons[i]);
    }

}