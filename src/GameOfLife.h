#pragma once

#include "VectorHash.h"

class GameOfLife
{
public:
	GameOfLife();

	void run();
private:
	sf::RenderWindow wnd;

	static constexpr int cellSize = 25; //size of a single cell in pixels
	static constexpr int wndSize = 800; //width and height of the window

	sf::Vector2i mousePosWnd;
	sf::Vector2f mousePosView;
private:
	void update();
	void render();

	void drawGrid();
	void drawCells();

	sf::Vector2i getIntPos(sf::Vector2f pos);
private:
	std::unordered_set<sf::Vector2i> cells;
	bool paused;
};

