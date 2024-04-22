#pragma once
#ifndef Location_H
#define Location_H
#include <SDL.H>
#include "Sprite.h"
#include "Loader.h"
#include "ParallaxLayer.h"
/// <summary>
/// Locations control which items are displayed in ParallaxLayers, interacts with hand
/// They hold an array of Sprites for a location and an Array of if they should be rendered for a location
/// 
/// They are created by the loader and the GameManager instructs them when to transition based on distance traveled
/// </summary>
class Location
{
public:
	Location(Sprite _sprites[5], bool _enabled[5]);
	~Location();
    void setFollowingLocation(Location* _follower);
    Location* getFollowingLocation();
    Sprite* getSprite(int index);
    bool getEnabled(int index);
private:
    Sprite sprites[5];
    bool enabled[5];
    Location* follower;
    /*
    Sprite backgroundSprite;
    Sprite cloudSprite;
    Sprite hillSprite;
    Sprite closeSprite;
    Sprite railsSprite;
    Sprite foregroundSprite;
    */
};

#endif
