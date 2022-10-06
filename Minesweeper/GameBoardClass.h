#pragma once

#include <vector>
#include "Main.h"
#include <SFML/Graphics.hpp>

const int numBombs = 30;

class GameBoard {
	sf::Texture texture;

	std::vector<std::vector<int>> board = {};
	std::vector<std::vector<int>> hidden = {};
	sf::Sprite sprite[boardWidth][boardHeight];
	sf::Sprite counters[6];

	sf::Sprite button;

	sf::Clock clock;

	bool running = false;
	bool lost = false;

	int numBomb = numBombs;
	int revealedSquare = 0;

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

	sf::Sprite getButton();
	bool setButton(int spritePosX, int spritePosY, int spriteWidth, int spriteHeight);

	int getTime();
	bool resetClock();

	bool newBoard();

	sf::Sprite getCounter(int index);
	bool setCounter(int index, int number);

	bool decrementBombs();
	bool incrementBombs();

	int getBombs();

	bool incrementRevealed();
	bool addRevealed(int num);
	int getRevealed();
};
