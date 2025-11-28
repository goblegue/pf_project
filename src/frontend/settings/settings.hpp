#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../renderer.hpp"
#include "../../utils/raygui.h"

struct GameSettings {
    int isMusicOn;         
    float animationSpeed;
    float Volume;
    int difficultyMode;
    int gameMusicTrack;
    bool dropDownEditModeDifficulty;
    bool dropDownEditModeTrack;
};


int drawSettingsPage(GameSettings &settings, Renderer &renderer,int previousPage);

GameSettings initGameSettings(char stylePath[]);


#endif