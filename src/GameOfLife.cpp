#include "GameOfLife.h"

#pragma warning (disable : 4244)

GameOfLife::GameOfLife()
	:
	wnd(sf::VideoMode(wndSize, wndSize), "Game of Life", sf::Style::Titlebar | sf::Style::Close),
	paused(true)
{}

void GameOfLife::run()
{
	while (wnd.isOpen())
	{
		mousePosWnd = sf::Mouse::getPosition(wnd);
		mousePosView = wnd.mapPixelToCoords(mousePosWnd);
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
				case sf::Keyboard::Space: paused = !paused; break;
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
			case sf::Event::MouseButtonPressed:
			{
				if (paused && e.mouseButton.button == sf::Mouse::Left)
				{
					if (cells.count(getIntPos(mousePosView)) == 0)
						cells.insert(getIntPos(mousePosView));
					else
						cells.erase(getIntPos(mousePosView));
				}
				break;
			}
			default: break;
			}
		}

		update();
		render();
	}
}

void GameOfLife::update()
{
	if (!paused)
	{

	}
}

void GameOfLife::render()
{
	wnd.clear(sf::Color::White);

	drawGrid();
	drawCells();

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
	sf::Vector2f size = wnd.getView().getSize();
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

	sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
	int xPos = mousePosView.x < 0 ? (int)((mousePosView.x - cellSize) / (float)cellSize) : (int)(mousePosView.x / (float)cellSize);
	int yPos = mousePosView.y < 0 ? (int)((mousePosView.y - cellSize) / (float)cellSize) : (int)(mousePosView.y / (float)cellSize);
	shape.setPosition(sf::Vector2f(xPos * cellSize, yPos * cellSize));
	shape.setFillColor(sf::Color(170, 170, 170));
	wnd.draw(shape);
}

void GameOfLife::drawCells()
{
	sf::VertexArray quad(sf::Quads, 4);
	for (int i = 0; i < 4; i++)
		quad[i].color = sf::Color::Black;
	for (auto it = cells.begin(), end = cells.end(); it != end; it++)
	{
		quad[0].position = sf::Vector2f(it->x * cellSize, it->y * cellSize);
		quad[1].position = sf::Vector2f(it->x * cellSize, it->y * cellSize) + sf::Vector2f(cellSize, 0);
		quad[2].position = sf::Vector2f(it->x * cellSize, it->y * cellSize) + sf::Vector2f(cellSize, cellSize);
		quad[3].position = sf::Vector2f(it->x * cellSize, it->y * cellSize) + sf::Vector2f(0, cellSize);
		wnd.draw(quad);
	}
}

sf::Vector2i GameOfLife::getIntPos(sf::Vector2f pos)
{
	int xPos = pos.x < 0 ? (int)((pos.x - cellSize) / (float)cellSize) : (int)((pos.x) / (float)cellSize);
	int yPos = pos.y < 0 ? (int)((pos.y - cellSize) / (float)cellSize) : (int)((pos.y) / (float)cellSize);
	return sf::Vector2i(xPos, yPos);
}
