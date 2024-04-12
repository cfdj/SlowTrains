#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    slowSpeed = Mix_LoadMUS(slowPath.c_str());
    mediumSpeed = Mix_LoadMUS(mediumPath.c_str());
    fastSpeed = Mix_LoadMUS(fastPath.c_str());

    if (slowSpeed == NULL) {
        printf("Slow speed missing");
    }
    if (mediumSpeed == NULL) {
        printf("medium speed missing");
    }
    if (fastSpeed == NULL) {
        printf("fast speed missing");
    }
    //Waiting for the Whistle path
    whistle = Mix_LoadWAV(whistlePath.c_str());
    if (whistle == NULL) {
        printf("Whistle missing");
    }
}

SoundPlayer::~SoundPlayer()
{
    Mix_FreeMusic(slowSpeed);
    Mix_FreeMusic(mediumSpeed);
    Mix_FreeMusic(fastSpeed);
    Mix_Music* slowSpeed = NULL;
    Mix_Music* mediumSpeed = NULL;
    Mix_Music* fastSpeed = NULL;

    //Freeing whistle
    Mix_FreeChunk(whistle);
    Mix_Chunk* whistle = NULL;
    Mix_Quit();
}

void SoundPlayer::setSpeed(int _speed)
{
    speed = _speed;
    startMusic();
}

void SoundPlayer::setVolume(int _volume)
{
    musicVolume = _volume;
    Mix_VolumeMusic(musicVolume);
}

void SoundPlayer::setSFXVolume(int _volume)
{
    sfxVolume = _volume;
    Mix_MasterVolume(sfxVolume); //In theory per channel volume setting is possible to break down different sound effects
}

void SoundPlayer::startMusic()
{
    int loopnum = -1;
    if (!mute) {
        switch (speed) {
        case 0:
            Mix_PlayMusic(slowSpeed, loopnum);
            break;
        case 1:
            Mix_PlayMusic(mediumSpeed, loopnum);
            break;
        case 2:
            Mix_PlayMusic(fastSpeed,loopnum);
            break;
        }
    }
}

void SoundPlayer::stopMusic()
{
    Mix_PauseMusic();
}

//currently waits for the whistle to finish before it can be played again
//allowing the player to cut the whistle short would require de-bouncing functionality
void SoundPlayer::playWhistle()
{
    if (!mute) {
        if (whistleChannel != NULL) {
            if (!Mix_Playing(whistleChannel)) {
                whistleChannel = Mix_PlayChannel(-1, whistle, 0);
            }
        }
        else { //enabling first time play
            whistleChannel = Mix_PlayChannel(-1, whistle, 0);
        }
    }
}

void SoundPlayer::disableSound(bool _mute)
{
    mute = _mute;
    if (mute) {
        stopMusic();
    }
    else {
        startMusic();
    }
}
