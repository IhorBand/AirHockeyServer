#include "Wall.h"

Wall::Wall(b2World* world, float width, float height, b2Vec2 position)
{
    this->width = width;
    this->height = height;

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(position.x, position.y);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    body = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(width, height);

    // Add the ground fixture to the ground body.
    body->CreateFixture(&groundBox, 0.0f);
}