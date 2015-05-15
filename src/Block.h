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

	bool solid();
	bool dangerous();

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

	float angle = 0.f;
};

#endif
