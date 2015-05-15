#include "SpeedUp.h"

SpeedUp::SpeedUp()
{
    setType(Interactable::Interaction_Type::speed_up);
}

SpeedUp::SpeedUp(float x, float y)
{
    setSpeedUp(x, y);
    setType(Interactable::Interaction_Type::speed_up);
}

SpeedUp::SpeedUp(sf::Vector2f pos)
{
    setSpeedUp(pos.x,  pos.y);
    setType(Interactable::Interaction_Type::speed_up);
}

void SpeedUp::setSpeedUp(float x, float y)
{
    m_rectangle.setPosition(x, y);
    m_rectangle.setFillColor(sf::Color(255,255,255));
}

void SpeedUp::setSize(float size_x, float size_y)
{
    m_rectangle.setSize(sf::Vector2f(size_x, size_y));
}

sf::FloatRect SpeedUp::getGlobalBounds()
{
    return m_rectangle.getGlobalBounds();
}

sf::Vector2f SpeedUp::interact(sf::FloatRect player, sf::Vector2f speed)
{
    return speed + sf::Vector2f(speed_boost, 0);
}

void SpeedUp::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rectangle, states);
}
