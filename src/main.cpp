#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow wnd(sf::VideoMode(800, 600), "Game of Life");
	sf::Event e;

	while (wnd.isOpen())
	{
		while (wnd.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				wnd.close();
		}

		wnd.clear(sf::Color::Blue);

		wnd.display();
	}

	return 0;
}