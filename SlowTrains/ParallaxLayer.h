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
	void render();
	void SetSpeed(int _speed);
private:
	int xpos = 0;
	float speed = 5; //Shared across all layers
	float speedFactor = 1; //if speed/speed factor < 1, results in no motion
	Sprite* leftSprite;
	Sprite* rightSprite;
	int frameLength = 16;
	int lastFrameUpdate = 0;
};

#endif