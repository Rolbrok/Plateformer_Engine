#include "Block_Trap.h"

Block_Trap::Block_Trap()
{
	setColor(sf::Color(0, 0, 0));
	setDangerous(true);
}

Block_Trap::Block_Trap(float x, float y, float size)
{
    setSize(size);
    setColor(sf::Color(0,0,0));
    setDangerous(true);
    setPosition(x, y);
}
