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
	sf::View oldView = wnd.getView();
	int rows = oldView.getSize().x / cellSize;
	int cols = oldView.getSize().y / cellSize;
	// initialize values
	int numLines = rows + cols - 2;
	sf::VertexArray grid(sf::Lines, 2 * (numLines));
	wnd.setView(wnd.getDefaultView());
	auto size = wnd.getView().getSize();
	float rowH = size.y / rows;
	float colW = size.x / cols;
	// row separators
	for (int i = 0; i < rows - 1; i++) {
		int r = i + 1;
		float rowY = rowH * r;
		grid[i * 2].position = { 0, rowY };
		grid[i * 2].color = sf::Color(128, 128, 128);
		grid[i * 2 + 1].position = { size.x, rowY };
		grid[i * 2 + 1].color = sf::Color(128, 128, 128);
	}
	// column separators
	for (int i = rows - 1; i < numLines; i++) {
		int c = i - rows + 2;
		float colX = colW * c;
		grid[i * 2].position = { colX, 0 };
		grid[i * 2].color = sf::Color(128, 128, 128);
		grid[i * 2 + 1].position = { colX, size.y };
		grid[i * 2 + 1].color = sf::Color(128, 128, 128);
	}
	// draw it
	wnd.draw(grid);
	wnd.setView(oldView);
}
