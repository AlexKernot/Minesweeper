#pragma once

#include <vector>
#include "Main.h"
#include <SFML/Graphics.hpp>

class GameBoard {
	sf::Texture texture;

	std::vector<std::vector<int>> board = {};
	std::vector<std::vector<int>> hidden = {};
	sf::Sprite sprite[boardHeight][boardWidth];

	bool running = false;
	bool lost = false;

public:
	GameBoard();
	int getBoard(int indexX, int indexY);
	bool setBoard(int indexX, int indexY, int value);

	bool boardIncrement(int indexX, int indexY);

	int getHidden(int indexX, int indexY);
	bool setHidden(int indexX, int indexY, int value);

	bool setSprite(int indexX, int indexY, int spritePosX, int spritePosY, int spriteWidth, int spriteHeight);
	sf::Sprite getSprite(int indexX, int indexY);

	bool getRunning();
	bool setRunning(bool value);
	
	bool getLost();
	bool setLost(bool value);

};
