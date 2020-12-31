#include "Map.h"


Map::Map(b2World* world, float width, float height)
{
    this->width = width;
    this->height = height;

    float wallWidth = 0.9f;

    //top wall
    Wall* wall = new Wall(world, width / 2.0f, wallWidth / 2.0f, b2Vec2(width / 2.0f, wallWidth / 2.0f));
    this->walls.push_back(*wall);

    //bottom wall
    wall = new Wall(world, width / 2.0f, wallWidth / 2.0f, b2Vec2(width / 2.0f, this->height - (wallWidth / 2.0f)));
    this->walls.push_back(*wall);


    float sideWall_height = (this->height / 2.0f) - (this->goalWidth / 2.0f) - wallWidth;

    //left top wall 
    wall = new Wall(world, wallWidth / 2.0f, sideWall_height / 2.0f, b2Vec2(wallWidth / 2.0f, (sideWall_height / 2.0f) + wallWidth));
    this->walls.push_back(*wall);

    //left bottom wall 
    wall = new Wall(world, wallWidth / 2.0f, sideWall_height / 2.0f, b2Vec2(wallWidth / 2.0f, this->height - (sideWall_height / 2.0f) - wallWidth));
    this->walls.push_back(*wall);

    //right top wall
    wall = new Wall(world, wallWidth / 2.0f, sideWall_height / 2.0f, b2Vec2(this->width - (wallWidth / 2.0f), (sideWall_height / 2.0f) + wallWidth));
    this->walls.push_back(*wall);

    //right bottom wall 
    wall = new Wall(world, wallWidth / 2.0f, sideWall_height / 2.0f, b2Vec2(this->width - (wallWidth / 2.0f), this->height - (sideWall_height / 2.0f) - wallWidth));
    this->walls.push_back(*wall);
}