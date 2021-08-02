#include "GameOfLife.h"

GameOfLife::GameOfLife()
	:
	wnd(sf::VideoMode(wndSize, wndSize), "Game of Life", sf::Style::Titlebar | sf::Style::Close)
{
	
}

void GameOfLife::run()
{
	while (wnd.isOpen())
	{
		sf::Event e;
		while (wnd.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed: wnd.close(); break;
			default: break;
			}
		}

		update();
		render();
	}
}

void GameOfLife::update()
{
}

void GameOfLife::render()
{
	wnd.clear(sf::Color::White);
	
	drawGrid();

	wnd.display();
}

void GameOfLife::drawGrid()
{
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Transparent);
	shape.setSize(sf::Vector2f(cellSize, cellSize));
	shape.setOutlineColor(sf::Color(128, 128, 128));
	shape.setOutlineThickness(1);
	for (unsigned int y = 0; y < (wndSize / cellSize); y++)
	{
		for (unsigned int x = 0; x < (wndSize / cellSize); x++)
		{
			shape.setPosition(sf::Vector2f(x * (float)cellSize, y * (float)cellSize));
			wnd.draw(shape);
		}
	}
}
