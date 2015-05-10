#include "Block_Green.h"

Block_Green::Block_Green()
{
	setColor(sf::Color::Green);
}

Block_Green::Block_Green(float x, float y, float size)
{
    setSize(size);
    setPosition(x, y);
    setColor(sf::Color::Green);
}
