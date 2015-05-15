#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Interactable : public sf::Drawable
{
public:
    enum class Interaction_Type { portal, speed_up, none };

public:
    Interactable();
    Interactable(float x, float y);
    Interactable(sf::Vector2f pos);
    ~Interactable();

    sf::FloatRect getGlobalBounds();

    sf::Vector2f interact(sf::FloatRect player, sf::Vector2f speed);   
    
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void setType(Interaction_Type new_type);
    Interaction_Type getType();

private:
    Interaction_Type m_type = Interaction_Type::none;
};

#endif
