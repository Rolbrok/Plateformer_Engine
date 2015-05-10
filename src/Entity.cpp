#include <iostream> /* for std::cout, std::endl */
#include "Entity.h"

int signof(float v)
{
	// If v is negative, returns -1
	// else returns 1
	return (v < 0) ? -1 : 1;
}

void Entity::setPosition(float x, float y)
{
	// Changes the position of the Entity
	position.x = x;
	position.y = y;
}

void Entity::setPosition(sf::Vector2f pos)
{
	// Changes the position of the Entity
	position = pos;
}

void Entity::setGround(float y)
{
	// Changes the position of the ground
	ground_position = y;
}

void Entity::setSpeed(float new_speed, Vector2b axis)
{
	// Checks the axis given and updates the speed to the new_speed
	speed.x = (axis.x) ? new_speed : speed.x;
	speed.y = (axis.y) ? new_speed : speed.y;
}

void Entity::setAcceleration(float new_accel, Vector2b axis)
{
	// Checks the axis given and updates the acceleration to the new_accel
	// MATH_R is a experimental constant that convert real values into game values
	// ex: gravity=-9.81m/s^-2, MATH_R=70, so the in-game gravity will be -686.7
	// X-Axis: new_accel * MATH_R
	// Y-Axis: (new_accel + GRAVITY) * MATH_R
	// Adds the gravity to the given acceleration
	acceleration.x = (axis.x) ? new_accel*MATH_R : acceleration.x;
	acceleration.y = (axis.y) ? (new_accel + GRAVITY)*MATH_R : acceleration.y;
}

void Entity::update(float dt)
{
	// Next speed value
	// speed = speed0 + acceleration*t
	speed += acceleration*dt;

	// Changes the position
	// position = position0 + speed*t + (acceleration * t^2) / 2 
	position += speed*dt + (acceleration *dt*dt) / 2.0f;

	// If the position if over the ground limit, resets it to the ground limit
	if (position.y > ground_position) {
		position.y = ground_position;
	}
}

sf::Vector2f Entity::getPosition()
{
	// Returns the current Entity position
	return position;
}

float Entity::getGround()
{
	// Returns the current ground position
	return ground_position;
}

float Entity::getSpeedLength()
{
	// Returns the length of the speed vector
	return floor(sqrt(speed.x*speed.x + speed.y*speed.y));
}

float Entity::getAccelerationLength()
{
	// Returns the length of the acceleration vector
	return floor(sqrt(acceleration.x*acceleration.x + acceleration.y*acceleration.y));
}

sf::Vector2f Entity::getSpeed()
{
	// Returns the speed vector
	return speed;
}

sf::Vector2f Entity::getAcceleration()
{
	// Returns the acceleration vector
	return acceleration;
}

void Entity::setAngle(float new_angle)
{
    angle = new_angle;
}

float Entity::getAngle()
{
    return angle;
}
