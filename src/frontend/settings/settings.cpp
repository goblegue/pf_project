#include "raylib.h"

#include "settings.hpp"

#include "../../colors/candyCrushPalette.hpp"
#include "../../colors/customColourPalette.hpp"
#include "../../utils/CharUtils.hpp"

GameSettings initGameSettings(char stylePath[])
{
    GuiLoadStyle(stylePath);
    GameSettings settings{};
    settings.isMusicOn = 1;
    settings.animationSpeed = 5.0f;
    settings.Volume = 0.5f;
    settings.difficultyMode = 1;
    settings.gameMusicTrack = 0;
    settings.dropDownEditModeDifficulty = false;
    settings.dropDownEditModeTrack = false;
    return settings;
}

int drawSettingsPage(GameSettings &settings, Renderer &renderer, int previousPage)
{

    const int windowWidth{GetScreenWidth()},
        windowHeight{GetScreenHeight()},
        panelWidth{500},
        panelHeight{650};

    float panelX = (windowWidth - panelWidth) / 2.0f;
    float panelY = (windowHeight - panelHeight) / 2.0f - 50;

    float elementSpacingY = 25.0f;

    Color fontColor = {91, 91, 129, 255};
    DrawRectangle(panelX, panelY, panelWidth, panelHeight, LITE_PURPLE);
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, CC_TEXT_GOLD);

    Vector2 settingTitleSize = MeasureTextEx(renderer.logoFont, "SETTINGS", renderer.logoFont.baseSize * 3.5, 1);
    DrawTextEx(renderer.logoFont, "SETTINGS", (Vector2){(panelX) + (panelWidth / 2) - settingTitleSize.x / 2 + 10, panelY + elementSpacingY}, renderer.logoFont.baseSize * 3, 1, fontColor);

    float toggleSliderY = panelY + 2 * elementSpacingY + settingTitleSize.y + 10;
    DrawTextEx(renderer.logoFont, "Music", (Vector2){panelX + 50, toggleSliderY}, renderer.logoFont.baseSize * 2.2, 1, fontColor);
    GuiToggleSlider({panelX + panelWidth - 175, toggleSliderY + 5, 140, 35}, "OFF;ON", &settings.isMusicOn);

    DrawTextEx(renderer.logoFont, "Volume", (Vector2){panelX + 50, toggleSliderY + elementSpacingY + 40}, renderer.logoFont.baseSize * 2.2, 1, fontColor);
    GuiSliderBar({panelX + panelWidth - 175, toggleSliderY + elementSpacingY + 50, 140, 30}, "", "", &settings.Volume, 0.0f, 1.0f);
    DrawTextEx(renderer.logoFont, TextFormat("%i%%", (int)(settings.Volume * 100)), (Vector2){panelX + panelWidth - 200, toggleSliderY + elementSpacingY + 55}, renderer.logoFont.baseSize, 1.2, fontColor);

    DrawTextEx(renderer.logoFont, "Animation Speed", (Vector2){panelX + 50, toggleSliderY + 2 * elementSpacingY + 85}, renderer.logoFont.baseSize * 2.2, 1, fontColor);
    GuiSliderBar({panelX + panelWidth - 175, toggleSliderY + 2 * elementSpacingY + 92, 140, 30}, "", "", &settings.animationSpeed, 1, 10);
    DrawTextEx(renderer.logoFont, TextFormat("%i", (int)(settings.animationSpeed * 50)), (Vector2){panelX + panelWidth - 200, toggleSliderY + 2 * elementSpacingY + 97}, renderer.logoFont.baseSize, 1.2, fontColor);

    // Back Button

    char backButtonLabel[20] = "BACK TO MENU";
    if (previousPage == 1)
    {
        charAssignment(backButtonLabel, "BACK TO GAME");
    }

    if (GuiButton({panelX + panelWidth / 2 - 100, panelY + panelHeight - 100, 200, 50}, backButtonLabel))
    {
        return previousPage; // MAIN_MENU
    }

    // Instruction page Button
    if (GuiButton({panelX + panelWidth / 2 - 100, panelY + panelHeight - 160, 200, 50}, "INSTRUCTIONS"))
    {
        return 3; // INSTRUCTION_PAGE
    }

    // difficulty and music track dropdown Box (
    const char musicOptions[] = "Track 1;Track 2;Track 3;Track 4;Track 5";
    DrawTextEx(renderer.logoFont, "Music Track", (Vector2){panelX + 50, toggleSliderY + 4 * elementSpacingY + 165}, renderer.logoFont.baseSize * 2.2, 1, fontColor);
    if (GuiDropdownBox({panelX + panelWidth - 175, toggleSliderY + 4 * elementSpacingY + 170, 140, 35}, musicOptions, &settings.gameMusicTrack, settings.dropDownEditModeTrack))
    {
        settings.dropDownEditModeTrack = !settings.dropDownEditModeTrack;
    }
    const char options[] = "CAKEWALK;STANDARD;NIGHTMARE;CRACKHEAD";
    DrawTextEx(renderer.logoFont, "Difficulty", (Vector2){panelX + 50, toggleSliderY + 3 * elementSpacingY + 125}, renderer.logoFont.baseSize * 2.2, 1, fontColor);
    if (previousPage == 1)
        GuiDisable();
    if (GuiDropdownBox({panelX + panelWidth - 175, toggleSliderY + 3 * elementSpacingY + 130, 140, 35}, options, &settings.difficultyMode, settings.dropDownEditModeDifficulty))
    {
        settings.dropDownEditModeDifficulty = !settings.dropDownEditModeDifficulty;
    }
    if (previousPage == 1)
        GuiEnable();

    return 2; // SETTINGS
}