#pragma once
#ifndef SoundPlayer_H
#define SoundPlayer_H
#include <SDL_mixer.h>
#include <string>
/// <summary>
/// Handles all sounds and volume
/// Primarily: Wheel sound effect and Whistle
/// Todo features: different sounds for different trains, different whistles
/// Like implemented via an array of strings which is chosen from by the constructor
/// </summary>
class SoundPlayer
{
public:
	SoundPlayer();
	~SoundPlayer();
	void setSpeed(int _speed); //Used to set which speed of train sound should be played, also changes to that track
	void setVolume(int _volume);
	void setSFXVolume(int _volume);
	void startMusic();
	void stopMusic();
	void playWhistle();
	void disableSound(bool _mute);
private:
	Mix_Music* slowSpeed = NULL;
	Mix_Music* mediumSpeed = NULL;
	Mix_Music* fastSpeed = NULL;

	Mix_Chunk* whistle = NULL;
	int musicVolume = 64; //Maxes at 128
	int sfxVolume = 74;//Maxes at 128
	int speed = 0; //Current speed state of the train
	bool mute = false;
	std::string slowPath = "Sounds/slowSpeed.wav";
	std::string mediumPath = "Sounds/mediumSpeed.wav";
	std::string fastPath = "Sounds/fastSpeed.wav";
	std::string whistlePath = "Sounds/whistle1.wav";
};
#endif