#pragma once
#ifndef Sprite_H
#define Sprite_H
#include <SDL.H>
#include <SDL_image.h>
#include <string>
/// <summary>
/// Base class for rendering textures to the screen, inherited by AnimatedSprite and used by ParallaxLayer and UI
/// Contains a fallback in its render function when attempts to render fail
/// </summary>
class Sprite
{
public:
	Sprite(std::string _path, int _width, int _height, int _xOffset, int _yOffset, SDL_Renderer* _renderer);
	~Sprite();
	Sprite(const Sprite& _other);
	Sprite();
	void render(int xPos,int yPos,SDL_Renderer* renderer);
	int width, height;
	void textureCopy(SDL_Surface* _surface);
	SDL_Surface* getSurface();
protected:
	std::string path;
	int xOffset, yOffset;
	SDL_Renderer* renderer;
	SDL_Surface* imageSurface = NULL;
	SDL_Texture* imageTexture = NULL;
	SDL_Rect rect;
};

#endif