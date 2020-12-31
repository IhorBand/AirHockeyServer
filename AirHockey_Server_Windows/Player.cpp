#include "Player.h"

class QueryCallback : public b2QueryCallback
{
public:
    QueryCallback(const b2Vec2& point)
    {
        m_point = point;
        m_fixture = NULL;

    }

    bool ReportFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody)

        {

            bool inside = fixture->TestPoint(m_point);
            if (inside)
            {
                m_fixture = fixture;

                // We are done, terminate the query.
                return false;
            }
        }

        // Continue the query.
        return true;
    }

    b2Vec2 m_point;
    b2Fixture* m_fixture;
};

Player::Player(b2World* world, b2Vec2 spawnPosition)
{
    // Define the dynamic body. We set its position and call the body factory.
    bodyDef.type = b2_dynamicBody;
    //bodyDef.position.Set(0.0f, 10.0f);
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.linearDamping = 5.0f;

    body = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 2.3f;
    this->width = circleShape.m_radius * 2;
    this->height = this->width;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.1f;

    // Override the default friction.
    fixtureDef.friction = 0.0f; //0.3
    fixtureDef.restitution = 0;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    body->SetTransform(spawnPosition, 0);
    mouseJoint = NULL;
}

void Player::MoveTo(b2World* world, b2Vec2 position)
{
    /*if (mouseJoint != NULL)
    {
        mouseJoint->SetTarget(position);
        return;
    }


    b2MouseJointDef md;
    md.maxForce = 10000.0f * body->GetMass();
    md.collideConnected = true;
    md.damping = 0.0f;
    md.target.Set(position.x, position.y);
    mouseJoint = (b2MouseJoint*)world->CreateJoint(&md);
    body->SetAwake(true);*/
    b2Vec2 curPosition = body->GetPosition();
    b2Vec2 moveTo(position.x - curPosition.x, position.y - curPosition.y);

    body->SetLinearVelocity(moveTo);
}

void Player::StopMoving(b2World* world)
{
    /*if (mouseJoint != NULL)
    {
        world->DestroyJoint(mouseJoint);
        mouseJoint = NULL;
    }*/
    body->SetLinearVelocity(b2Vec2(0, 0));
}

void Player::Update()
{

}