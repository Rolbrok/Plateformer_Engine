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
    window.setFramerateLimit(120);

	Tilemap m_tilemap;
	if (!m_tilemap.load("assets/map.txt")) {
		return 1;
	}

    sf::Vector2f window_size = sf::Vector2f(window.getSize().x, window.getSize().y);
	
	Player m_player(0, 50);
	m_player.setGround((float)window.getSize().y);
	m_player.setTilemap(&m_tilemap);

    HUD m_hud;
    m_hud.setFont("assets/font.ttf");
    m_player.setHUD(&m_hud);

    sf::View m_view(sf::FloatRect(0, 0, window_size.x, window_size.y));
    m_player.setView(&m_view);

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
        t_fps.setPosition(m_view.getCenter().x+m_view.getSize().x/2-3*20, m_view.getCenter().y-m_view.getSize().y/2);
        t_fps.setColor(sf::Color::White);
        m_hud.addText(t_fps);

		///////////////////////
		// Display Code here
		///////////////////////

		window.clear(sf::Color(100,100,100));

        window.setView(m_view);

		window.draw(m_tilemap);
		window.draw(m_player);
        window.draw(m_hud);

		window.display();

		///////////////////////
        m_hud.reset();
    }

	return 0;
}
