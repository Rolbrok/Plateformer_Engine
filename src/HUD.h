#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics/Text.hpp> /* Text */
#include <SFML/Graphics/Font.hpp> /* Font */
#include <SFML/Graphics/RenderTarget.hpp> /* RenderTarget */
#include <SFML/Graphics/RenderStates.hpp> /* RenderStates */
#include <SFML/Graphics/Drawable.hpp> /* For Drawable */
#include <vector>
#include <string>

class HUD : public sf::Drawable
{
public:
	HUD();

	void addText(sf::Text object);
	sf::Text &getTextObject(size_t i);

    bool setFont(std::string filename);
    sf::Font &getFont();
    
    void reset();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	std::vector< sf::Text > text_objects;
    sf::Font m_font;

};

#endif
