#include "ParallaxLayer.h"

//Construct a Parallax layer, setting its speedFactor and sprites
// Sprites are duplicated to allow for smooth scrolling 
//Currently assumes all sprites rendered are the same height as the screen size
ParallaxLayer::ParallaxLayer(float _speedFactor, Sprite* _sprite)
{
	speedFactor = _speedFactor;
	leftSprite = _sprite;
	rightSprite = _sprite;
}

ParallaxLayer::ParallaxLayer()
{
	leftSprite = NULL;
	rightSprite = NULL;
}

void ParallaxLayer::render()
{
	leftSprite->render(xpos, 0);
	rightSprite->render(xpos + rightSprite->width, 0);
	if (lastFrameUpdate + frameLength < SDL_GetTicks64()) {
		lastFrameUpdate = SDL_GetTicks64();
		xpos -= speed * speedFactor;//this might need a delay to help speed not be way too small, but we'll see
									//Current issues: Limited speed range, precision lost with int conversion, certain slow speeds loose continuity of motion
		if (xpos < -rightSprite->width) { //At the moment this makes it scroll infinitely, a likely extension is to make a queue of background layers for infinite changing journies
			xpos = 0;
		}
	}
}

void ParallaxLayer::SetSpeed(int _speed)
{
	speed = _speed;
}
