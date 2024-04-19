#pragma once
#ifndef Loader_H
#define Loader_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Sprite.h"
#include "AnimatedSprite.h"
/// <summary>
/// Parses CSVs for available Trains, Carriges, Backgrounds, Foregrounds, and Close terrain
/// Also parses in the structure of valid environments and valid following environments
/// Maybe needs to utilise SDL_GetBasePath
/// This is probably going to be the most intensive class to use, due to its use of Vector and memory access
/// </summary>
class Loader
{
public:
	Loader(SDL_Renderer* renderer);
	~Loader();
	AnimatedSprite* getTrain(int trainNum);
	Sprite getCarrige(int carrigeNum);
	int getNumTrains();
	int getFunnelX(int trainNum);
	int getFunnelY(int trainNum);
private:
	std::vector<AnimatedSprite> trains;
	std::vector<Sprite> carriges;
	int width = 82; //Has to be shared between train sprites, aligned on the left
	int height = 28;
	std::vector<int> funnelXposes;
	std::vector<int> funnelYposes;
	std::string trainPath = "Sprites/Trains/";
};

#endif
