#pragma once

const int boardSize = 16;
const int numBombs = 40;

vector<vector<int>> InitializeBoard(vector<vector<int>> board, int posX, int posY);
bool BoundCheck(int i);