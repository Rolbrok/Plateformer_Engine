#include "Block_SlideLeft.h"

Block_SlideLeft::Block_SlideLeft()
{
	setColor(sf::Color::Cyan);
}

Block_SlideLeft::Block_SlideLeft(float x, float y, float size)
{
    setSize(size);
    setPosition(x, y);
    setColor(sf::Color::Cyan);
    setAngle(m_angle);
}
