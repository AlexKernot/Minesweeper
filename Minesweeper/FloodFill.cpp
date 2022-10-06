using namespace std;

#include <vector>
#include "FloodFill.h"
#include "InitializeBoard.h"
#include <iostream>
#include "Main.h"
#include "GameBoardClass.h"

int FloodFill (GameBoard *board, int pointX, int pointY) {

	int squares = 0;

	if (board -> getHidden(pointX, pointY) == -1) {
		return squares;
	}

	if (board -> getHidden(pointX, pointY) == 1) {
		return squares;
	}

	if (board -> getBoard(pointX, pointY)> 0) {
		++squares;
		board -> setHidden(pointX, pointY, 1);
		return squares;
	}

	board -> setHidden(pointX, pointY, 1);
	++squares;

	squares += FloodFill(board, pointX + 1, pointY);
	squares += FloodFill(board, pointX + 1, pointY + 1);
	squares += FloodFill(board, pointX, pointY + 1);
	squares += FloodFill(board, pointX - 1, pointY + 1);
	squares += FloodFill(board, pointX - 1, pointY);
	squares += FloodFill(board, pointX, pointY - 1);
	squares += FloodFill(board, pointX - 1, pointY - 1);
	squares += FloodFill(board, pointX + 1, pointY - 1);

	return squares;
}