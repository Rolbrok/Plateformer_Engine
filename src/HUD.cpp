#include "HUD.h"

HUD::HUD()
{
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < text_objects.size(); i++) {
		target.draw(text_objects[i], states);
	}
}

void HUD::addText(sf::Text text)
{
	text_objects.push_back(text);
}

sf::Text &HUD::getTextObject(size_t i)
{
	return text_objects[i];
}

void HUD::reset()
{
    text_objects.erase(text_objects.begin(), text_objects.end());
}

bool HUD::setFont(std::string filename)
{
    if (!m_font.loadFromFile(filename)) {
        return false;
    } else {
        return true;
    }
}

sf::Font &HUD::getFont()
{
    return m_font;
}
