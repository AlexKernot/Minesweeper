#include "Main.h"
#include "GameBoardClass.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

GameBoard::GameBoard() {
    board.resize(boardWidth);
    hidden.resize(boardWidth);
    for (int i = 0; i < boardWidth; ++i) {

        board[i].resize(boardHeight);
        hidden[i].resize(boardHeight);

        for (int j = 0; j < boardHeight; ++j) {
            board[i][j] = 0;
            hidden[i][j] = 0;
        }
    }

    if (!texture.loadFromFile("sprites.png")) {
        std::cout << "The texture could not be loaded";
    }

    button.setTexture(texture);
    button.setTextureRect(sf::IntRect(0, 24, 24, 24));
    button.scale(sf::Vector2f(scaleFactor, scaleFactor));
    button.setPosition((windowWidth / 2) - 24, topOffset - (25 * scaleFactor));

    for (int i = 0; i < 3; ++i) {
        counters[i].setTexture(texture);
        counters[i].setPosition(windowWidth - rightOffset - (13 * (i + 1)) * scaleFactor, topOffset - (25 * scaleFactor));
        counters[i].scale(sf::Vector2f(scaleFactor, scaleFactor));
    }

    for (int i = 0; i < 3; ++i) {
        counters[i + 3].setTexture(texture);
        counters[i + 3].setPosition(leftOffset + 13 * i * scaleFactor, topOffset - (25 * scaleFactor));
        counters[i + 3].scale(sf::Vector2f(scaleFactor, scaleFactor));
    }

    for (int i = 0; i < boardWidth; ++i)
    {
        for (int j = 0; j < boardHeight; j++)
        {
            sprite[i][j].setTexture(texture);
            sprite[i][j].setTextureRect(sf::IntRect(0, 49, 16, 16));
            sprite[i][j].setPosition(16.0f * i * scaleFactor + leftOffset, 16.0f * j * scaleFactor + topOffset);
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

int GameBoard::getTime() {
    sf::Time elapsed = clock.getElapsedTime();
    return elapsed.asSeconds();
}
bool GameBoard::resetClock() {
    clock.restart();
    return true;

}

sf::Sprite GameBoard::getButton() {
    return button;
}

bool GameBoard::setButton(int spritePosX, int spritePosY, int spriteWidth, int spriteHeight) {
    button.setTextureRect(sf::IntRect(spritePosX, spritePosY, spriteWidth, spriteHeight));
    return true;
}

bool GameBoard::newBoard() {

    for (int i = 0; i < boardWidth; ++i) {
        for (int j = 0; j < boardHeight; ++j) {
            board[i][j] = 0;
            hidden[i][j] = 0;
            sprite[i][j].setTextureRect(sf::IntRect(0, 49, 16, 16));

            button.setTextureRect(sf::IntRect(0, 24, 24, 24));
        }
    }
    running = false;
    lost = false;

    numBomb = numBombs;
    revealedSquare = 0;

    return true;
}

sf::Sprite GameBoard::getCounter(int index) {
    return counters[index];
}

bool GameBoard::setCounter(int index, int number) {
    if (number < 10 && number > 0) {
        counters[index].setTextureRect(sf::IntRect(14 * (number - 1), 0, 13, 23));
        return true;
    }
    if (number == 0) {
        counters[index].setTextureRect(sf::IntRect(126, 0, 13, 23));
        return true;
    }
    if (number == 10) {
        counters[index].setTextureRect(sf::IntRect(140, 0, 13, 23));
        return true;
    }

    return false;
}

bool GameBoard::decrementBombs() {
    --numBomb;
    return true;
}

bool GameBoard::incrementBombs() {
    ++numBomb;
    return true;
}

int GameBoard::getBombs() {
    return numBomb;
}

bool GameBoard::incrementRevealed() {
    ++revealedSquare;
    return true;
}

int GameBoard::getRevealed() {
    return revealedSquare;
}

bool GameBoard::addRevealed(int num) {
    revealedSquare += num;
    return true;
}