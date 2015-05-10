#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics/Sprite.hpp> /* sf::Sprite */
#include <SFML/Graphics/Texture.hpp> /* sf::Texture */
#include <SFML/Graphics/RenderTarget.hpp> /* sf::RenderTarget */
#include <SFML/Graphics/RenderStates.hpp> /* sf::RenderStates */
#include <SFML/Graphics/Drawable.hpp> /* sf::Drawable */
#include <SFML/Graphics/Rect.hpp> /* sf::FloatRect */
#include <SFML/Graphics/RectangleShape.hpp> /* For collision rectangles */
#include <SFML/Graphics/ConvexShape.hpp> /* For the slide triangle */
#include "vmath.h"

class Block : public sf::Drawable
{
public:
    Block();
    Block(float x, float y, float size = 0);
	~Block();

	void setSize(float new_size);
	float getSize();

	// Changes the position
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);

	// Changes the color
	void setColor(sf::Color new_color);

	// Changes the type of the block (solid/trap)
	void setCollision(bool new_col);
	void setDangerous(bool new_trap);

	void setAngle(float new_angle);

	// Creates a portal (to another DIMENSIOOONN !! oh, wait no, to another point)
	void createPortal(sf::Vector2f pos);

	// Returns important values needed
	// like the teleport point, if the solid is a portal, a solid, or dangerous
	// Or the position, the bounds
	sf::Vector2f getTeleportPoint();

	bool solid();
	bool dangerous();
	bool isPortal();

	float getAngle();
    sf::Vector2f getEquationFactor();

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

	// The draw function
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	// The rectangle that will be drawn
	sf::RectangleShape m_rectangle;
    sf::ConvexShape m_triangle;

	// Some block properties
	bool collides = true;
	bool trap = false;
	bool portal = false;
	sf::Vector2f teleport_to = sf::Vector2f(-1,-1);

	float angle = 0.f;
};

#endif
