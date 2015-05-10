#include "Collision.h"

std::pair<Collision::Side, sf::Vector2f>Collision::getMovingPoint(sf::FloatRect player, Block block)
{
	// If the block is not a solid, do not check the collision
	// returns no move
	if (!block.solid()) {
		return std::make_pair(Side::none, sf::Vector2f(0, 0));
	}

	// return_point is the point that will be added to the player's position
	// The area is the area of the player in the block
	sf::Vector2f return_point(0, 0);
	sf::FloatRect area;

	// If there is no intersection between the block and the player
	// returns no move
	if (!player.intersects(block.getGlobalBounds(), area)) {
		return std::make_pair(Side::none, return_point);
	}

	// Define the side of the collision
	Side col_side = Side::none;

	// If the area width is greater than the area height,
	// it means that the collision is either on the top side, or the down side of the player
	// else if the area height is greater than the area width,
	// then the collision is on the side of the player
	if (area.width >= area.height) {

		// If the area of the collision contains the top side of the player,
		// The collision is a Top collision
		// Else, the collision is a Down collision, which will set the ground for the player
		if (area.contains({ area.left, player.top })) {
			return_point.y += area.height;
			col_side = Side::top;
		} else {
			return_point.y -= area.height;
			col_side = Side::down;
		}
	} else if (area.height > area.width) {

		// If the area of the collision contains the left side of the player,
		// The collision is a Left collision
		// else, it's a Right collision
		if (area.contains({ player.left, area.top })) {
			return_point.x += area.width;
			col_side = Side::left;
		} else {
			return_point.x -= area.width;
			col_side = Side::right;
		}
	}

	// Returns the collision side and the moves the player needs to make
	return std::make_pair(col_side, return_point);
}