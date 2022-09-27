using namespace std;

#include <vector>
#include "FloodFill.h"
#include "InitializeBoard.h"

vector<vector<int>> FloodFill(static vector<vector<int>> board, static vector<vector<int>> hidden, int pointX, int pointY) {

	if (!BoundCheck(pointX) || !BoundCheck(pointY)) {
		return hidden;
	}

	if (hidden[pointX][pointY] == 1) {
		return hidden;
	}

	if (board[pointX][pointY] != 0) {
		hidden[pointX][pointY] = 1;
		return hidden;
	}

	hidden[pointX][pointY] = 1;

	FloodFill(board, hidden, pointX + 1, pointY);
	FloodFill(board, hidden, pointX + 1, pointY + 1);
	FloodFill(board, hidden, pointX, pointY + 1);
	FloodFill(board, hidden, pointX - 1, pointY + 1);
	FloodFill(board, hidden, pointX - 1, pointY);
	FloodFill(board, hidden, pointX, pointY - 1);
	FloodFill(board, hidden, pointX - 1, pointY - 1);
	FloodFill(board, hidden, pointX + 1, pointY - 1);

	return hidden;
}