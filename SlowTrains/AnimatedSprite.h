#pragma once
#ifndef AnimatedSprite_H
#define AnimatedSprite_H
#include "Sprite.h"
#include <array>
/// <summary>
/// Handles Animated Sprites based on sprite sheets
/// Inherits from Sprites and shares display method and functionality, however it also updates which section of the sprite is displayed based on xFrames and yFrames
/// </summary>
class AnimatedSprite : public Sprite
{
	public:
		AnimatedSprite(std::string _path, int _width, int _height, int _xFrames, int _yFrames, SDL_Renderer* _renderer);
		AnimatedSprite();
		~AnimatedSprite();
		void render(int xPos, int yPos);

private:
	int currentFrame = 0;
	int numFrames = 0;
	int frameXNum = 0;
	int frameYNum = 0;
	int frameLength = 100; //This is shared so all animations have the same framerate
	int lastFrameUpdate = 0;
};

#endif

