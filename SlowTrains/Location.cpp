#include "Location.h"

Location::Location(Sprite _sprites[5], bool _enabled[5])
{

}

Location::~Location()
{
}

void Location::setFollowingLocation(Location* _follower)
{
}

Location* Location::getFollowingLocation()
{
    return follower;
}

Sprite* Location::getSprite(int index)
{
    return nullptr;
}

bool Location::getEnabled(int index)
{
    return false;
}
