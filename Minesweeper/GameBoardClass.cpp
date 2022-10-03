#include "Main.h"
#include "GameBoardClass.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

GameBoard::GameBoard() {
    board.resize(boardWidth);
    hidden.resize(boardHeight);
    for (int i = 0; i < boardWidth; ++i) {

        board[i].resize(boardWidth);
        hidden[i].resize(boardWidth);

        for (int j = 0; j < boardWidth; ++j) {
            board[i][j] = 0;
            hidden[i][j] = 0;
        }
    }

    if (!texture.loadFromFile("sprites.png")) {
        std::cout << "The texture could not be loaded";
    }

    for (int i = 0; i < boardHeight; ++i)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            sprite[i][j].setTexture(texture);
            sprite[i][j].setTextureRect(sf::IntRect(0, 49, 17, 17));
            sprite[i][j].setPosition(17.0f * i * scaleFactor + leftOffset, 17.0f * j * scaleFactor + topOffset);
            sprite[i][j].scale(sf::Vector2f(scaleFactor, scaleFactor));
        }
    }
}
int GameBoard::getBoard(int indexX, int indexY) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        return board[indexX][indexY];
    }
    return -1;
}

bool GameBoard::setBoard(int indexX, int indexY, int value) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        board[indexX][indexY] = value;
        return true;
    }
    return false;
}

int GameBoard::getHidden(int indexX, int indexY) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        return hidden[indexX][indexY];
    }
    return -1;
}

bool GameBoard::setHidden(int indexX, int indexY, int value) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        hidden[indexX][indexY] = value;
        return true;
    }
    return false;
}

bool GameBoard::boardIncrement(int indexX, int indexY) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        ++board[indexX][indexY];
        return true;
    }
    return false;
}

bool GameBoard::setSprite(int indexX, int indexY, int spritePosX, int spritePosY, int spriteWidth, int spriteHeight) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        sprite[indexX][indexY].setTextureRect(sf::IntRect(spritePosX, spritePosY, spriteWidth, spriteHeight));
        return true;
    }
    return false;
}

sf::Sprite GameBoard::getSprite(int indexX, int indexY) {
    if (indexX < boardWidth && indexY < boardHeight && indexX > -1 && indexY > -1) {
        return sprite[indexX][indexY];
    }
    sf::Sprite nullSprite;
    return nullSprite;
}

bool GameBoard::getRunning() {
    return running;
}

bool GameBoard::setRunning(bool value) {
    running = value;
    return true;
}

bool GameBoard::getLost() {
    return lost;
}

bool GameBoard::setLost(bool value) {
    lost = value;
    return true;
}