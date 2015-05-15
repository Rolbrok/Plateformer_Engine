#include "Portal.h"
#include <iostream>

Portal::Portal()
{
}

Portal::Portal(float x, float y)
{
    setPortal(x, y);
}

Portal::Portal(sf::Vector2f pos)
{
    setPortal(pos.x, pos.y);
}

Portal::~Portal()
{
}

sf::Vector2f Portal::interact(sf::FloatRect player, sf::Vector2f speed)
{
    return getDestination();
}

void Portal::setPortal(float x, float y)
{
    m_rectangle.setPosition(x, y);
    m_rectangle.setFillColor(sf::Color(134, 43, 128));
    setType(Interactable::Interaction_Type::portal);
}

void Portal::setSize(float size_x, float size_y)
{
    m_rectangle.setSize(sf::Vector2f(size_x, size_y));
}

sf::Vector2f Portal::getPosition()
{
    return m_rectangle.getPosition();
}

void Portal::setDestination(sf::Vector2f pos)
{
    destination_point = pos;
}

void Portal::setDestination(float x, float y)
{
    destination_point = sf::Vector2f(x, y);
}

sf::FloatRect Portal::getGlobalBounds()
{
    /*std::cout << m_rectangle.getGlobalBounds().left << ", " << 
                 m_rectangle.getGlobalBounds().top << ", " <<
                 m_rectangle.getGlobalBounds().width << ", " <<
                 m_rectangle.getGlobalBounds().height << std::endl;*/
    return m_rectangle.getGlobalBounds();
}

sf::Vector2f Portal::getDestination()
{
    return destination_point;
}

void Portal::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rectangle, states);
}
