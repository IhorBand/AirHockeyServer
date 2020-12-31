#ifndef MAP_H
#define MAP_H

#include "Wall.h"
#include <vector>

class Map
{
private:
public:
	float width = 0;
	float height = 0;
	float goalWidth = 12.0f;
	std::vector<Wall> walls;

	Map(b2World* world, float width, float height);

};

#endif