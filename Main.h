#pragma once

const int boardHeight = 16;
const int boardWidth = 16;

const int scaleFactor = 2;

const int topOffset = 60;
const int bottomOffset = 5;
const int leftOffset = 5;
const int rightOffset = 5;

const int windowHeight = boardHeight * 16 * scaleFactor + topOffset + bottomOffset;
const int windowWidth = boardWidth * 16 * scaleFactor + leftOffset + rightOffset;

int main();

