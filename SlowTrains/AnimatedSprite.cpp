#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string _path, int _width, int _height, int _xFrames, int _yFrames, SDL_Renderer* _renderer)
	:Sprite(_path, _width, _height, _width / _xFrames, _height / _yFrames, _renderer)
{
	frameXNum = _xFrames;
	frameYNum = _yFrames;
	numFrames = frameXNum * frameYNum;
}

AnimatedSprite::AnimatedSprite()
{
	frameXNum = 0;
	frameYNum = 0;
	numFrames = 0;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::render(int xPos, int yPos) 
{
	//Converting linear framecount to position in the sprite sheet
	//Current issue: if the sprite sheet has an uneven end this will create empty frames
	int x = currentFrame%frameXNum;
	int y = currentFrame / frameXNum; 
	rect = { x * width,y * height,width,height };
	SDL_Rect screenPos = { xPos,yPos,width,height };
	SDL_RenderCopy(renderer, imageTexture, &rect, &screenPos);
	if (lastFrameUpdate + frameLength< SDL_GetTicks64()) {
		lastFrameUpdate = SDL_GetTicks64();
		currentFrame += 1;
		if (currentFrame >= numFrames) {
			currentFrame = 0;
		}
	}
}