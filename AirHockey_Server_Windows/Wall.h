#ifndef WALL_H
#define WALL_H

#include "Object.h"

class Wall : Object
{
private:
public:
	float width = 0;
	float height = 0;
	b2Body* body;

	Wall(b2World* world, float width, float height, b2Vec2 position);

	void Update();
};

#endif