#include "audio.hpp"

Audio initAudio(const char musicFilePath[], float initialVolume)
{
    Audio gameAudio{};
    gameAudio.music = LoadMusicStream(musicFilePath);
    gameAudio.music.looping = true;
    gameAudio.volume = initialVolume;
    gameAudio.isPlaying = false;
    SetMusicVolume(gameAudio.music, gameAudio.volume);
    return gameAudio;
}

void changeMusic(Audio &gameAudio, const char musicFilePath[])
{
    UnloadMusicStream(gameAudio.music);
    gameAudio.music = LoadMusicStream(musicFilePath);
    gameAudio.music.looping = true;
    SetMusicVolume(gameAudio.music, gameAudio.volume);
    gameAudio.isPlaying = false;
}

void playMusic(Audio &gameAudio)
{
    if (!gameAudio.isPlaying)
    {
        PlayMusicStream(gameAudio.music);
        gameAudio.isPlaying = true;
    }
}

void pauseMusic(Audio &gameAudio)
{
    if (gameAudio.isPlaying)
    {
        PauseMusicStream(gameAudio.music);
        gameAudio.isPlaying = false;
    }
}

void changeVolume(Audio &gameAudio, float newVolume)
{
    gameAudio.volume = newVolume;
    SetMusicVolume(gameAudio.music, gameAudio.volume);
}

void updateAudioStream(Audio &gameAudio)
{
    UpdateMusicStream(gameAudio.music);
}

void unloadAudio(Audio &gameAudio)
{
    UnloadMusicStream(gameAudio.music);
}

