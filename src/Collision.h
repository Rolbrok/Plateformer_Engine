#ifndef COLLISION_H
#define COLLISION_H

#include "Block.h"
#include <utility>

namespace Collision
{
	// Defines the sides that can be detected in a collision
	enum class Side { top, down, left, right, none };

	// The function returns the side of the collision, if there is any, 
	//and the movement that the player needs to make to avoid the collision
	std::pair<Side, sf::Vector2f> getMovingPoint(sf::FloatRect player, sf::FloatRect block);
};

#endif
