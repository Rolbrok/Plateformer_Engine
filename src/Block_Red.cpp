#include "Block_Red.h"


Block_Red::Block_Red()
{
	setColor(sf::Color::Red);
}

Block_Red::Block_Red(float x, float y, float size)
{
    setSize(size);
    setPosition(x, y);
	setColor(sf::Color::Red);
}
