#pragma once

#include "SFML/Graphics.hpp"
#include <map>
#include <array>

class GameOfLife
{
public:
	GameOfLife();

	void run();
private:
	sf::RenderWindow wnd;

	static constexpr int cellSize = 25; //size of a single cell in pixels
	static constexpr int wndSize = 800; //width and height of the window

private:
	void update();
	void render();

	void drawGrid();
};

