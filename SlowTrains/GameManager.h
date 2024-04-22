#pragma once
#ifndef GameManger_H
#define GameManger_H
#include <SDL.h>
#include "UI.h"
#include "ParallaxLayer.h"
#include "SoundPlayer.h"
#include "Loader.h"
#include "AnimatedSprite.h"
#include "ParticleSystem.h"
/// <summary>
/// The GameManager handles player input and changes between gamestate, also handles rendering the Train
/// It could be extended further to handle object initialisation
/// </summary>
class GameManager
{
public:	
	GameManager(UI* _ui,ParallaxLayer* _parallax, SoundPlayer* _soundPlayer, Loader* _loader,ParticleSystem* _steam);
	~GameManager();
	void handleInput(SDL_Event e);
	void switchTrain();
	AnimatedSprite* getTrain();
	void render(int _xpos, int _ypos,SDL_Renderer* renderer);
private:
	void updateSpeed();
	UI* ui;
	ParallaxLayer* parallax;
	SoundPlayer* soundPlayer;
	Loader* loader;
	AnimatedSprite* train;
	ParticleSystem* steam;
	//For enabeling Key rebinding
	SDL_Scancode start = SDL_SCANCODE_SPACE;
	SDL_Scancode faster = SDL_SCANCODE_D;
	SDL_Scancode slower = SDL_SCANCODE_A;

	SDL_Scancode nextTrain = SDL_SCANCODE_W;
	SDL_Scancode previousTrain = SDL_SCANCODE_S;
	enum gameState { Loading, InStation, Running };
	gameState state = InStation;
	int speeds[3] = { 4,6,10 };
	int particleSpeeds[3] = { -1, -2 , -4 };
	int currentSpeed = 1;

	int trainId = 0;
};
#endif
