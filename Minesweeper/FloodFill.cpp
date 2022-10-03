using namespace std;

#include <vector>
#include "FloodFill.h"
#include "InitializeBoard.h"
#include <iostream>
#include "Main.h"
#include "GameBoardClass.h"

bool FloodFill (GameBoard *board, int pointX, int pointY) {

	if (board -> getHidden(pointX, pointY) == -1) {
		return true;
	}

	if (board -> getHidden(pointX, pointY) == 1) {
		return true;
	}

	if (board -> getBoard(pointX, pointY)> 0) {
		board -> setHidden(pointX, pointY, 1);
		return true;
	}

	board -> setHidden(pointX, pointY, 1);

	FloodFill(board, pointX + 1, pointY);
	FloodFill(board, pointX + 1, pointY + 1);
	FloodFill(board, pointX, pointY + 1);
	FloodFill(board, pointX - 1, pointY + 1);
	FloodFill(board, pointX - 1, pointY);
	FloodFill(board, pointX, pointY - 1);
	FloodFill(board, pointX - 1, pointY - 1);
	FloodFill(board, pointX + 1, pointY - 1);

	return true;
}