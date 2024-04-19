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

void AnimatedSprite::render(int xPos, int yPos,SDL_Renderer* _renderer) 
{
	renderer = _renderer;
	//Converting linear framecount to position in the sprite sheet
	//Current issue: if the sprite sheet has an uneven end this will create empty frames
	int x = currentFrame%frameXNum;
	int y = currentFrame / frameXNum; 
	rect = { x * width,y * height,width,height };
	SDL_Rect screenPos = { xPos,yPos,width,height };
	int error = SDL_RenderCopy(renderer, imageTexture, &rect, &screenPos);
	
	if (error != 0) {
		printf(SDL_GetError());
		//One shot fallback
		imageSurface = IMG_Load(path.c_str());
		if (imageSurface == NULL) {
			printf("Error: Image not Loaded in copy ");
			printf(path.c_str());
			printf("\n");
		}
		imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
		SDL_RenderCopy(renderer, imageTexture, &rect, &screenPos);
	}

	if (playing) { //only advance the frames if playing
		if (lastFrameUpdate + frameLength < SDL_GetTicks64()) {
			lastFrameUpdate = SDL_GetTicks64();
			currentFrame += 1;
			if (currentFrame >= numFrames) {
				currentFrame = 0;
			}
		}
	}
}