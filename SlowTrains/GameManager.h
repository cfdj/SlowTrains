#pragma once
#ifndef GameManger_H
#define GameManger_H
#include <SDL.h>
#include "UI.h"
#include "ParallaxLayer.h"
#include "SoundPlayer.h"
/// <summary>
/// The GameManager handles player input and changes between gamestate
/// It could be extended further to handle object initialisation
/// </summary>
class GameManager
{
public:	
	GameManager(UI* _ui,ParallaxLayer* _parallax, SoundPlayer* _soundPlayer);
	~GameManager();
	void handleInput(SDL_Event e);
private:
	UI* ui;
	ParallaxLayer* parallax;
	SoundPlayer* soundPlayer;
	//For enabeling Key rebinding
	SDL_Scancode start = SDL_SCANCODE_SPACE;
	SDL_Scancode faster = SDL_SCANCODE_D;
	SDL_Scancode slower = SDL_SCANCODE_A;
	enum gameState { Loading, InStation, Running };
	gameState state = Loading;
	int speed = 5;
};
#endif
