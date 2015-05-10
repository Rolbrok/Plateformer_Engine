#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include "Player.h"
#include "Tilemap.h"
#include "HUD.h"

#define VERSION "0.0.2"
#define CONCAT(a,b) std::string(a)+std::string(b)

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), CONCAT("Alpha build ", VERSION));

	Tilemap m_tilemap;
	if (!m_tilemap.load("assets/map.txt")) {
		return 1;
	}
	
	Player m_player(16,16);
	m_player.setGround((float)window.getSize().y);
	m_player.setTilemap(m_tilemap);

    HUD m_hud;
    m_player.setHUD(&m_hud);

    m_hud.setFont("assets/font.ttf");

	sf::Clock m_clock;

	while (window.isOpen())
	{
        m_hud.reset();
		float dt = m_clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    clock_t time = clock();
                    std::ostringstream convert;
                    std::string filename;
                    convert << time;
                    filename = convert.str() + ".png";                    

                    std::cout << "Screenshot taken under: " << time << ".png" << std::endl;
                    sf::Image screenshot = window.capture();
                    screenshot.saveToFile(filename);
                }
            }
		}

		m_player.update_player(dt);
        float fps = 1.f / dt;
        std::ostringstream f;
        f << (int)fps;
        sf::Text t_fps(f.str(), m_hud.getFont(), 20);
        t_fps.setPosition((float)window.getSize().x-3*20, 0);
        t_fps.setColor(sf::Color::White);
        m_hud.addText(t_fps);

		///////////////////////
		// Display Code here
		///////////////////////

		window.clear(sf::Color(100,100,100));

		window.draw(m_tilemap);
		window.draw(m_player);
        window.draw(m_hud);

		window.display();

		///////////////////////
        m_hud.reset();
	}

	return 0;
}
