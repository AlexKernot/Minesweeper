#pragma once

const int boardHeight = 16;
const int boardWidth = 16;

const int scaleFactor = 2;

const int topOffset = 109;
const int bottomOffset = 5;
const int leftOffset = 5;
const int rightOffset = 5;

const int windowHeight = boardHeight * 17 * scaleFactor + topOffset + bottomOffset;
const int windowWidth = boardWidth * 17 * scaleFactor + leftOffset + rightOffset;

int main();

