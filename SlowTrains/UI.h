#pragma once
#ifndef UI_H
#define UI_H
#include "Sprite.h"
#include <string>
/// <summary>
/// Displays a UI with 3 possible states, each being a sprite.
/// Designed for displaying the speed control
/// </summary>
class UI
{
public:
	UI(Sprite* _state0, Sprite* _state1, Sprite* _state2, int _xPos, int _yPos);
	void render(SDL_Renderer* renderer);
	void setState(int newState);
private:
	int state = 0;
	int xpos = 0;
	int ypos = 0;
	Sprite* state0;
	Sprite* state1;
	Sprite* state2;
};

#endif