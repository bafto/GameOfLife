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
			case sf::Event::KeyPressed:
			{
				switch (e.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					wnd.setView(sf::View(wnd.getView().getCenter() + sf::Vector2f(0.f, -cellSize), wnd.getView().getSize()));
					break;
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					wnd.setView(sf::View(wnd.getView().getCenter() + sf::Vector2f(-cellSize, 0.f), wnd.getView().getSize()));
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					wnd.setView(sf::View(wnd.getView().getCenter() + sf::Vector2f(0.f, cellSize), wnd.getView().getSize()));
					break;
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					wnd.setView(sf::View(wnd.getView().getCenter() + sf::Vector2f(cellSize, 0.f), wnd.getView().getSize()));
					break;
				default: break;
				}
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				wnd.setView(sf::View(wnd.getView().getCenter(), sf::Vector2f(wnd.getView().getSize() + sf::Vector2f(cellSize * -e.mouseWheelScroll.delta * 2, cellSize * -e.mouseWheelScroll.delta * 2))));
				break;
			}
			default: break;
			}
		}
		mousePosWnd = sf::Mouse::getPosition(wnd);
		mousePosView = wnd.mapPixelToCoords(mousePosWnd);

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
	
	sf::RectangleShape shape(sf::Vector2f(150, 150));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setFillColor(sf::Color::Red);
	wnd.draw(shape);
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
	sf::View lastView = wnd.getView();
	sf::View tempView = lastView;
	tempView.setCenter(sf::Vector2f(0.f + tempView.getSize().x / 2, 0.f + tempView.getSize().y / 2));
	wnd.setView(tempView);
	sf::Vector2f mousePosView = wnd.mapPixelToCoords(mousePosWnd);
	for (unsigned int y = 0; y < (int)(tempView.getSize().y / cellSize); y++)
	{
		for (unsigned int x = 0; x < (int)(tempView.getSize().x / cellSize); x++)
		{
			shape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
			if (shape.getGlobalBounds().contains((sf::Vector2f)mousePosView))
				shape.setFillColor(sf::Color(170, 170, 170));
			wnd.draw(shape);
			shape.setFillColor(sf::Color::Transparent);
		}
	}
	wnd.setView(lastView);
}
