using namespace std;

#include <random>
#include <iostream>
#include "InitializeBoard.h"

bool BoundCheck(int i);

vector<vector<int>> InitializeBoard(vector<vector<int>> board, int posX, int posY) {

	mt19937 rand(time(nullptr));
	std::uniform_int_distribution<int> distribution(1, boardSize);

	vector<vector<int>> newBoard;

	int x = 0;
	int y = 0;
	int startingX = posX;
	int startingY = posY;

	newBoard.resize(boardSize);
	for (int i = 0; i < newBoard.size(); ++i) {

		newBoard[i].resize(boardSize);

		for (int j = 0; j < newBoard[i].size(); ++j) {
			newBoard[i][j] = 0;
		}
	}

	for (int i = 0; i < numBombs; ++i) {
		x = distribution(rand) - 1;
		y = distribution(rand) - 1;

		if (x == startingX && y == startingY) {
			--i;
			continue;
		}
		if (x == startingX - 1 && y == startingY) {
			--i;
			continue;
		}
		if (x == startingX - 1 && y == startingY - 1) {
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
		if (x == startingX && y == startingY - 1) {
			--i;
			continue;
		}
		if (x == startingX && y == startingY + 1) {
			--i;
			continue;
		}
		if (newBoard[x][y] >= 9) {
			--i;
			continue;
		}

		newBoard[x][y] = 9;

			if (BoundCheck(x - 1)) {
				if (BoundCheck(y + 1)) {
					++newBoard[x - 1][y + 1];
				}
				if (BoundCheck(y - 1)) {
					++newBoard[x - 1][y - 1];
				}
				++newBoard[x - 1][y];
			}
			if (BoundCheck(x + 1)) {
				if (BoundCheck(y + 1)) {
					++newBoard[x + 1][y + 1];
				}
				if (BoundCheck(y - 1)) {
					++newBoard[x + 1][y - 1];
				}
				++newBoard[x + 1][y];
			}
			if (BoundCheck(y + 1)) {
				++newBoard[x][y + 1];
			}
			if (BoundCheck(y - 1)) {
				++newBoard[x][y - 1];
			}
	}
	for (int i = 0; i < newBoard.size(); ++i) {
		for (int j = 0; j < newBoard[i].size(); ++j) {
			if (newBoard[i][j] >= 9) {
				newBoard[i][j] = 9;
			}
		}
	}
	for (int i = 0; i < newBoard.size(); ++i) {
		for (int j = 0; j < newBoard.size(); ++j) {
			cout << newBoard[i][j];
		}
		cout << "\n";
	}
	return newBoard;
}

bool BoundCheck(int i) {
	if (i >= boardSize || i < 0) {
		return false;
	}
	return true;
}