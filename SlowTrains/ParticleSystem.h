#pragma once
#ifndef ParticleSystem_H
#define ParticleSystem_H
#include "AnimatedSprite.h"
#include <string>
/// <summary>
/// Particle system
/// Renders up to 10 particles from a sprite sheet at moving locations
/// Has two render logics: 
///		Startup - when not all particles are being rendered
///		Loop - when all particles are being rendered
/// </summary>
class ParticleSystem
{
public:
	ParticleSystem(std::string _path, int _xStart, int _yStart, int _xMove, int _yMove, int _width, int _height, int _xFrames, int _yFrames, SDL_Renderer * _renderer);

	void render();
	void setyMove(int y);
	void setxMove(int x);
	void setPlaying(bool _playing);
	void setXStart(int x);
	void setYStart(int y);
private:
	bool playing = false;
	int numParticles = 10;
	int xStart,yStart,xMove, yMove, width, height, frameXNum, frameYNum; //This currently duplicates a lot from animated sprite
	SDL_Rect locations [10] = {};
	int frameNums[10] = { 0,0,0,0,0,0,0,0,0,0 };
	std::string path;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* imageSurface = NULL;
	SDL_Texture* imageTexture = NULL;
	int frameLength = 100; //This is shared so all animations have the same framerate
	int spawnRate = 100;
	int lastSpawn = 0;
	int numSpawned;
	int lastFrameUpdate = 0;
	int lastFrameMove = 0;//Seperating Movement and Animation advancing for that sweet sweet overlapping motion
	int moveRate = 33;
};

#endif