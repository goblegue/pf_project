#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../renderer.hpp"
#include "../../utils/raygui.h"

struct GameSettings
{
    int isMusicOn;
    float animationSpeed;
    float Volume;
    int difficultyMode;
    int gameMusicTrack;
    bool dropDownEditModeDifficulty;
    bool dropDownEditModeTrack;
};

/**
 * @brief draws the settings page
 * @param settings the game settings
 * @param renderer the renderer
 * @param previousPage the previous page
 * @returns the next page
 */
int drawSettingsPage(GameSettings &settings, Renderer &renderer, int previousPage);

/**
 * @brief initializes the game settings
 * @param stylePath the path to the style file
 * @returns the initialized game settings
 */
GameSettings initGameSettings(char stylePath[]);

#endif