#ifndef SPEEDUP_H
#define SPEEDUP_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "Interactable.h"

class SpeedUp : public Interactable
{
public:
    SpeedUp();
    SpeedUp(float x, float y);    
    SpeedUp(sf::Vector2f pos);

    void setSize(float size_x, float size_y);

    void setSpeedUp(float x, float y);

    sf::Vector2f interact(sf::FloatRect player, sf::Vector2f speed);

    sf::FloatRect getGlobalBounds();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::RectangleShape m_rectangle;

    float speed_boost = 100.f;    
};


#endif
