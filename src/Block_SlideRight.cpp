#include "Block_SlideRight.h"

Block_SlideRight::Block_SlideRight()
{
	setColor(sf::Color::Cyan);
}

Block_SlideRight::Block_SlideRight(float x, float y, float size)
{
    setSize(size);
    setPosition(x, y);
    setColor(sf::Color::Cyan);
    setAngle(m_angle);
}
