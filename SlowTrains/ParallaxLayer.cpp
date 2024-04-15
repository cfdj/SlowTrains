#include "ParallaxLayer.h"

//Construct a Parallax layer, setting its speedFactor and sprites
// Sprites are duplicated to allow for smooth scrolling 
// change() allows changing the displayed sprite, this works by buffering the right sprite, on reset setting the right sprite, waiting to scroll and then setting the left sprite
// This change always takes two loops round, however this is the minimum safe number of loops
//Currently assumes all sprites rendered are the same height as the screen size
ParallaxLayer::ParallaxLayer(float _speedFactor, Sprite* _sprite)
{
	speedFactor = _speedFactor;
	leftSprite = _sprite;
	rightSprite = _sprite;
	buffer = _sprite;
}

ParallaxLayer::ParallaxLayer()
{
	leftSprite = NULL;
	rightSprite = NULL;
	buffer = NULL;
}

void ParallaxLayer::render()
{
	leftSprite->render(xpos, 0);
	rightSprite->render(xpos + rightSprite->width, 0);
	if (lastFrameUpdate + frameLength < SDL_GetTicks64()) {
		lastFrameUpdate = SDL_GetTicks64();
		xpos -= speed * speedFactor;//this might need a delay to help speed not be way too small, but we'll see
									//Current issues: Limited speed range, precision lost with int conversion, certain slow speeds loose continuity of motion
		if (xpos < -rightSprite->width) {
			xpos = 0;
			if (changing && ! buffSet) {
				changing = false;
				leftSprite = rightSprite;
			}
			if (buffSet) {
				buffSet = false;
				rightSprite = buffer;
			}
		}
	}
}

float ParallaxLayer::speed = 0;
void ParallaxLayer::SetSpeed(int _speed)
{
	speed = _speed;
}

void ParallaxLayer::change(Sprite* _sprite)
{
	changing = true;
	buffSet = true;
	buffer = _sprite;
}
