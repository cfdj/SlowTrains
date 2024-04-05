#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(std::string _path, int _xStart, int _yStart, int _xMove, int _yMove, int _width, int _height, int _xFrames, int _yFrames, SDL_Renderer* _renderer)
{
	width = _width;
	height = _height;
	path = _path;
	renderer = _renderer;
	xStart = _xStart;
	yStart = _yStart;
	xMove = _xMove;
	yMove = _yMove;
	frameXNum = _xFrames;
	frameYNum = _yFrames;
	imageSurface = IMG_Load(_path.c_str());
	if (imageSurface == NULL) {
		printf("Error: Image not Loaded");
		printf(_path.c_str());
	}
	imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
}

void ParticleSystem::render()
{
	if (numParticles > numSpawned) {
		if (lastSpawn + spawnRate < SDL_GetTicks64()) {
			lastSpawn = SDL_GetTicks64();
			locations[numSpawned].x = xStart;
			locations[numSpawned].y = yStart;
			locations[numSpawned].w = width;
			locations[numSpawned].h = height;
			numSpawned += 1;
		}
	}
	for (int i = 0; i < numSpawned;i++){
		int currentFrame = frameNums[i];
		int x = currentFrame % frameXNum;
		int y = currentFrame / frameXNum;
		SDL_Rect rect = { x * width,y * height,width,height };
		SDL_Rect screenPos = locations[i];
		SDL_RenderCopy(renderer, imageTexture, &rect, &screenPos);
		if (lastFrameMove + moveRate < SDL_GetTicks64()) {
			locations[i].x += xMove;
			locations[i].y += yMove;
		}
	}
	if (lastFrameMove + moveRate < SDL_GetTicks64()) { //Updating the last move frame outside the loop so it fires once all the particles have moved
		lastFrameMove = SDL_GetTicks64();
	}
	if (lastFrameUpdate + frameLength < SDL_GetTicks64()) {
		lastFrameUpdate = SDL_GetTicks64();
		for (int i = 0; i < numSpawned; i++) {
			frameNums[i]+=1;
			if (frameNums[i] >= frameXNum * frameYNum) {
				frameNums[i] = 0;
				locations[i].x = xStart;
				locations[i].y = yStart;
			}
		}
	}
}
