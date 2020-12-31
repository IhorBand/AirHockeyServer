#ifndef PUCK_H
#define PUCK_H

#include "Object.h"

class Puck : Object
{
private:
    b2BodyDef bodyDef;
public:
    float width = 0.0f;
    float height = 0.0f;

    b2Body* body;

    Puck(b2World* world);

    void Update();
};

#endif