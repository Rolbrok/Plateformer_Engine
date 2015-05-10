#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Transform.hpp> /* For sf::Vector2 */
#include "Constants.h"

// Type and function definition
typedef sf::Vector2<bool> Vector2b;
int signof(float v);

class Entity
{
public:
	// Sets the position
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);

	// Sets the speed
	void setSpeed(float speed, Vector2b axis = Vector2b(1,1));
	// Sets the acceleration
	void setAcceleration(float accel, Vector2b axis = Vector2b(1, 1));

	// Sets the ground limit
	void setGround(float y);

    // Sets the angle
    void setAngle(float new_angle);

	// Updates the values
	void update(float dt);

	// Returns the position vector
	sf::Vector2f getPosition();
	// Returns the speed vector
	sf::Vector2f getSpeed();
	// Returns the acceleration vector
	sf::Vector2f getAcceleration();

	// Returns the ground limit
	float getGround();

	// Returns the length of the speed and acceleration vectors
	float getSpeedLength();
	float getAccelerationLength();

    // Returns the angle
    float getAngle();

private:
	// Basic physics values
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f acceleration;

	// The ground_position
	float ground_position;
  
    // The angle of the object
    float angle;
};

#endif
