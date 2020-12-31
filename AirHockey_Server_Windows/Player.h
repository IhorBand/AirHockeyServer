#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : Object
{
private:
	b2BodyDef bodyDef;
	b2MouseJoint* mouseJoint;
public:
	float width;
	float height;

	b2Body* body;

	Player(b2World* world, b2Vec2 spawnPosition);

	void MoveTo(b2World* world, b2Vec2 position);
	void StopMoving(b2World* world);

	void Update();
};

#endif