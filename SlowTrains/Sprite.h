#pragma once
#ifndef Sprite_H
#define Sprite_H
#include <SDL.H>
#include <SDL_image.h>
#include <string>

class Sprite
{
public:
	Sprite(std::string _path, int _width, int _height, int _xOffset, int _yOffset, SDL_Renderer* _renderer);
	~Sprite();
	Sprite(const Sprite& _other);
	Sprite();
	void render(int xPos,int yPos);
	int width, height;
protected:
	std::string path;
	int xOffset, yOffset;
	SDL_Renderer* renderer;
	SDL_Surface* imageSurface = NULL;
	SDL_Texture* imageTexture = NULL;
	SDL_Rect rect;
};

#endif