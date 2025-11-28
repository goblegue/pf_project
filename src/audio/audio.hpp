#include "raylib.h"

struct Audio
{
    Music music;
    float volume;
    bool isPlaying;

};

Audio initAudio(const char musicFilePath[], float initialVolume);
void changeMusic(Audio &gameAudio, const char musicFilePath[]);
void playMusic(Audio &gameAudio);
void pauseMusic(Audio &gameAudio);
void changeVolume(Audio &gameAudio, float newVolume);
void unloadAudio(Audio &gameAudio);
void updateAudioStream(Audio &gameAudio);
void switchAudio(Audio &currentAudio, Audio &newAudio);
