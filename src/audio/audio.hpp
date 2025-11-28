#include "raylib.h"

struct Audio
{
    Music music;
    float volume;
    bool isPlaying;
};

/**
 * @brief initializes the audio
 * @param musicFilePath the path to the music file
 * @param initialVolume the initial volume
 * @returns the initialized audio
 */
Audio initAudio(const char musicFilePath[], float initialVolume);

/**
 * @brief changes the music
 * @param gameAudio the game audio
 * @param musicFilePath the path to the new music file
 */
void changeMusic(Audio &gameAudio, const char musicFilePath[]);

/**
 * @brief plays the music
 * @param gameAudio the game audio
 */
void playMusic(Audio &gameAudio);

/**
 * @brief pauses the music
 * @param gameAudio the game audio
 */
void pauseMusic(Audio &gameAudio);

/**
 * @brief changes the volume
 * @param gameAudio the game audio
 * @param newVolume the new volume
 */
void changeVolume(Audio &gameAudio, float newVolume);

/**
 * @brief unloads the audio
 * @param gameAudio the game audio
 */
void unloadAudio(Audio &gameAudio);

/**
 * @brief updates the audio stream
 * @param gameAudio the game audio
 */
void updateAudioStream(Audio &gameAudio);

/**
 * @brief switches the audio
 * @param currentAudio the current audio
 * @param newAudio the new audio
 */
void switchAudio(Audio &currentAudio, Audio &newAudio);
