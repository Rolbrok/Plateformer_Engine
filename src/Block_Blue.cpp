#include "Block_Blue.h"

Block_Blue::Block_Blue()
{
	setColor(sf::Color::Blue);
}

Block_Blue::Block_Blue(float x, float y, float size)
{
    setSize(size);
    setPosition(x, y);
    setColor(sf::Color::Blue);
}
