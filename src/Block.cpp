#include "Block.h"

Block::Block()
{
}

Block::Block(float x, float y, float size)
{
    setPosition(x, y);
    setSize(size);
}

Block::~Block()
{
}

sf::FloatRect Block::getGlobalBounds()
{
    //if (angle == 0.f)
	    return m_rectangle.getGlobalBounds();
    //else 
        //return sf::FloatRect(0, 0, 0, 0);
}

void Block::setPosition(float x, float y)
{
	m_rectangle.setPosition(x, y);
}

void Block::setPosition(sf::Vector2f pos)
{
	m_rectangle.setPosition(pos);
}

sf::Vector2f Block::getPosition()
{
	return m_rectangle.getPosition();
}

void Block::setSize(float size)
{
	m_rectangle.setSize(sf::Vector2f(size, size));
}

float Block::getSize()
{
	return m_rectangle.getSize().x;
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (angle == 0.f)
	    target.draw(m_rectangle, states);
    else
        target.draw(m_triangle, states);
}

void Block::setColor(sf::Color new_color)
{
	m_rectangle.setFillColor(new_color);
    m_triangle.setFillColor(new_color);
}

void Block::setCollision(bool new_col)
{
	collides = new_col;
}

void Block::setDangerous(bool new_trap)
{
	trap = new_trap;
}


bool Block::solid()
{
	return collides;
}

bool Block::dangerous()
{
	return trap;
}

bool Block::isPortal()
{
	return portal;
}

void Block::createPortal(sf::Vector2f pos)
{
	teleport_to = pos;
	portal = true;
}

sf::Vector2f Block::getTeleportPoint()
{
	return teleport_to;
}

void Block::setAngle(float new_angle)
{
    // Changes the angle of the Block and changes the position accordingly
	angle = -new_angle;
    
    sf::Vector2f width = sf::Vector2f(getSize(), 0);
    sf::Vector2f height = sf::Vector2f(0, getSize());
    
    m_triangle.setPointCount(3);
    
    if (angle == 0) {
        return;
    } else if (angle < 0) {       
        sf::Vector2f destination_angle = vector_angle(m_rectangle.getPosition() + height,
                                                      m_rectangle.getPosition() + height + width,
                                                      angle); 
    
        m_triangle.setPoint(0, sf::Vector2f(m_rectangle.getPosition().x, m_rectangle.getPosition().y+getSize())); 
        m_triangle.setPoint(1, destination_angle);
        m_triangle.setPoint(2, m_rectangle.getPosition() + width + height);
    } else if (angle > 0) {
        sf::Vector2f destination_angle = vector_angle(m_rectangle.getPosition() + height + width,
                                                      m_rectangle.getPosition() + height,
                                                      angle);

        m_triangle.setPoint(0, m_rectangle.getPosition() + height + width);
        m_triangle.setPoint(1, m_rectangle.getPosition() + height); 
        m_triangle.setPoint(2, destination_angle);
    }
}

float Block::getAngle()
{
	return angle;
}

sf::Vector2f Block::getEquationFactor()
{
    if (angle == 0.f)
        return sf::Vector2f(0,0);
    else {
        return equation_factor(m_triangle.getPoint(0), m_triangle.getPoint(1));
    } 
}
