#ifndef OBJECT_H
#define OBJECT_H

#include <box2d/box2d.h>

class Object
{
private:
public:
	float width;
	float height;

	b2Body* body;

	void Update();

};

#endif