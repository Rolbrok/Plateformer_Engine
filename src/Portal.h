#ifndef PORTAL_H
#define PORTAL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "Interactable.h"

class Portal : public Interactable
{
public:
    Portal();
    Portal(float x, float y);    
    Portal(sf::Vector2f pos);
    ~Portal();

    void setSize(float size_x, float size_y);

    sf::Vector2f getPosition();

    void setPortal(float x, float y);

    sf::Vector2f interact(sf::FloatRect player, sf::Vector2f speed);

    void setDestination(sf::Vector2f pos);
    void setDestination(float x, float y);

    sf::Vector2f getDestination();

    sf::FloatRect getGlobalBounds();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::RectangleShape m_rectangle;

    sf::Vector2f destination_point; 
};

#endif
