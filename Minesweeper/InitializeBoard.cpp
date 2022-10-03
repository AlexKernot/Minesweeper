using namespace std;

#include <random>
#include <iostream>
#include "InitializeBoard.h"
#include "Main.h"
#include "GameBoardClass.h"

bool InitializeBoard(GameBoard *board, int posX, int posY) {

	mt19937 rand(time(nullptr));
	std::uniform_int_distribution<int> distribution(1, boardSize);

	int x = 0;
	int y = 0;
	int startingX = posX;
	int startingY = posY;

	for (int i = 0; i < numBombs; ++i) {
		x = distribution(rand) - 1;
		y = distribution(rand) - 1;

		if (x == startingX && y == startingY) {
			--i;
			continue;
		}
		if (x == startingX - 1 && y == startingY - 1) {
			--i;
			continue;
		}
		if (x == startingX - 1 && y == startingY) {
			--i;
			continue;
		}
		if (x == startingX - 1 && y== startingY + 1) {
			--i;
			continue;
		}
		if (x == startingX && y == startingY - 1) {
			--i;
			continue;
		}
		if (x == startingX && y == startingY + 1) {
			--i;
			continue;
		}
		if (x == startingX + 1 && y == startingY - 1) {
			--i;
			continue;
		}
		if (x == startingX + 1 && y == startingY) {
			--i;
			continue;
		}
		if (x == startingX + 1 && y == startingY + 1) {
			--i;
			continue;
		}
		if (board -> getBoard(x, y) >= 9) {
			--i;
			continue;
		}

		board -> setBoard(x, y, 9);
		board -> boardIncrement(x - 1, y - 1);
		board -> boardIncrement(x - 1, y + 1);
		board -> boardIncrement(x - 1, y);
		board -> boardIncrement(x, y - 1);
		board -> boardIncrement(x, y + 1);
		board -> boardIncrement(x + 1, y - 1);
		board -> boardIncrement(x + 1, y);
		board -> boardIncrement(x + 1, y + 1);
	}
	for (int i = 0; i < boardHeight; ++i) {
		for (int j = 0; j < boardWidth; ++j) {
			if (board -> getBoard(i, j) >= 9) {
				board -> setBoard(i, j, 9);
			}
		}
	}
	for (int i = 0; i < boardHeight; ++i) {
		for (int j = 0; j < boardWidth; ++j) {
			cout << board -> getBoard(i, j) << " ";
		}
		cout << "\n";
	}
	return true;
}