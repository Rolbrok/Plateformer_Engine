#include "Interactable.h"
#include <iostream>

Interactable::Interactable()
{}
Interactable::Interactable(float x, float y)
{}
Interactable::Interactable(sf::Vector2f pos)
{}
Interactable::~Interactable()
{}

sf::Vector2f Interactable::interact(sf::FloatRect player, sf::Vector2f speed)
{
}

sf::FloatRect Interactable::getGlobalBounds()
{   
    std::cout << "RAAAAAAHHHHH" << std::endl;
}

void Interactable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    std::cout << "DRAWING" << std::endl;
} 

void Interactable::setType(Interactable::Interaction_Type new_type)
{
    m_type = new_type;
}

Interactable::Interaction_Type Interactable::getType()
{
    return m_type;
}
