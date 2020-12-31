#include "Puck.h"

Puck::Puck(b2World* world)
{
    // Define the dynamic body. We set its position and call the body factory.
    bodyDef.type = b2_dynamicBody;
    //bodyDef.position.Set(0.0f, 10.0f);
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.linearDamping = 0.1;

    body = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 1.5f;
    this->width = circleShape.m_radius * 2;
    this->height = this->width;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    fixtureDef.restitutionThreshold = -10000.0f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
}


void Puck::Update()
{

}
