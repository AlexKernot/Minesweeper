using namespace std;

#include <vector>
#include "FloodFill.h"
#include "InitializeBoard.h"
#include <iostream>

vector<vector<int>> FloodFill(vector<vector<int>> board, vector<vector<int>> hidden, int pointX, int pointY) {

	static vector<vector<int>> hiding = hidden;

	if (!BoundCheck(pointX) || !BoundCheck(pointY)) {
		return hiding;
	}

	if (hidden[pointX][pointY] == 1) {
		return hiding;
	}

	if (board[pointX][pointY] > 0) {
		hiding[pointX][pointY] = 1;
		return hiding;
	}

	hiding[pointX][pointY] = 1;

	FloodFill(board, hiding, pointX + 1, pointY);
	FloodFill(board, hiding, pointX + 1, pointY + 1);
	FloodFill(board, hiding, pointX, pointY + 1);
	FloodFill(board, hiding, pointX - 1, pointY + 1);
	FloodFill(board, hiding, pointX - 1, pointY);
	FloodFill(board, hiding, pointX, pointY - 1);
	FloodFill(board, hiding, pointX - 1, pointY - 1);
	FloodFill(board, hiding, pointX + 1, pointY - 1);

	return hiding;
}