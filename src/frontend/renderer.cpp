#include "renderer.hpp"

const float TOP_MARGIN = 0.25f;           // Top margin as a fraction of window height
const float TILE_BORDER_THICKNESS = 1.0f; // Thickness of the border around each tile

Renderer initRenderer(int windowWidth, int windowHeight)
{
    Renderer renderer{};
    renderer.candyTexture = LoadTexture("assets/textures/candies.png");     // Load candy sprite sheet
    renderer.buttonTexture = LoadTexture("assets/textures/Menu_Icons.png"); // Load button sprite sheet

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

    // menu buttons
    renderer.menuButtons[ACTION_NEW_GAME] =
        {BigPinkButton,
         {windowWidth / 2.0f - 132.5f, windowHeight * 0.4f, 265.0f, 110.0f},
         "NEW GAME",
         false,
         ACTION_NEW_GAME};

    renderer.menuButtons[ACTION_LOAD_GAME] =
        {SmallBlueButton,
         {windowWidth / 2.0f - 132.5f, windowHeight * 0.55f, 265.0f, 75.0f},
         "LOAD GAME",
         false,
         ACTION_LOAD_GAME};

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
    return renderer;
}

void unloadRenderer(Renderer &renderer)
{
    UnloadTexture(renderer.candyTexture);
    UnloadTexture(renderer.buttonTexture);
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

void drawButton(const Renderer &renderer, const Button &btn)
{
    // check hover and click state
    Vector2 mousePos = GetMousePosition();
    bool isHovering = CheckCollisionPointRec(mousePos, btn.bounds);

    Color tint = WHITE;
    if (btn.isClicked)
        tint = GRAY;
    else if (isHovering)
        tint = LIGHTGRAY;

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

void drawMenu(const Renderer &renderer)
{
    // draw all menu buttons
    for (int i = 0; i < MAXMENUBUTTONS; i++)
    {
        drawButton(renderer, renderer.menuButtons[i]);
    }
}