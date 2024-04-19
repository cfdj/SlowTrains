#pragma once
#ifndef ParallaxLayer_H
#define ParallaxLayer_H
#include "Sprite.h"
#include <string>
class ParallaxLayer
{
public:
	ParallaxLayer(float _speedFactor,Sprite* _sprite);
	ParallaxLayer();
	void render(SDL_Renderer* renderer);
	void SetSpeed(int _speed);
	void change(Sprite* _sprite);
private:
	int xpos = 0;
	static float speed; //Shared across all layers
	float speedFactor = 1; //if speed/speed factor < 1, results in no motion
	Sprite* leftSprite;
	Sprite* rightSprite;
	Sprite* buffer;
	int frameLength = 16;
	int lastFrameUpdate = 0;
	bool changing = false; //used to allow for changing image over the journey
	bool buffSet = false;
};

#endif