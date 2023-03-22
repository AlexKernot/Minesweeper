using namespace std;

#include <iostream>
#include <SFML/Graphics.hpp>
#include "InitializeBoard.h"
#include <cmath>
#include "FloodFill.h"
#include "Main.h"
#include "GameBoardClass.h"

bool RevealSquare(GameBoard* gameBoard, int pointX, int pointY, bool recursion);
bool ShowBombs(GameBoard* gameBoard, int pointX, int pointY);
bool MouseClick(sf::Event* event, GameBoard* gameBoard);
bool InsideBoard(int mouseX, int mouseY);
bool UpdateTimer(GameBoard* gameBoard);

int main()
{
    int mouseX = 0;
    int mouseY = 0;
    int numberInSquare = 0;

    sf::RenderWindow window(sf::VideoMode(16 * boardWidth * scaleFactor + leftOffset + rightOffset, 16 * boardHeight * scaleFactor + topOffset + bottomOffset), "Minesweeper", sf::Style::Close);

    sf::RectangleShape shape(sf::Vector2f(windowWidth, windowHeight));
    shape.setFillColor(sf::Color(181, 181, 181));

    GameBoard gameBoard;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                MouseClick(&event, &gameBoard);
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(gameBoard.getButton());

        UpdateTimer(&gameBoard);

        for (int i = 0; i < 6; ++i) {
            // 1-3, gets timer number, 4-6 gets bomb number
            window.draw(gameBoard.getCounter(i));
        }


        for (int i = 0; i < boardWidth; ++i) {
            for (int j = 0; j < boardHeight; ++j) {
                sf::Sprite sprite = gameBoard.getSprite(i, j);
                window.draw(sprite);
            }
        }

        window.display();
    }

    return 0;
}

bool MouseClick(sf::Event* event, GameBoard* gameBoard) {

    sf::Mouse::Button mouse = event->mouseButton.button;
    int mouseX = event->mouseButton.x;
    int mouseY = event->mouseButton.y;

    bool running = gameBoard->getRunning();
    bool lost = gameBoard->getLost();

    if (mouseX > (windowWidth / 2) - 24 && mouseX < windowWidth / 2 + 24 * (scaleFactor - 1)) {
        if (mouseY > topOffset - (25 * scaleFactor) && mouseY < 20 * scaleFactor + topOffset - (25 * scaleFactor)) {
            gameBoard->newBoard();
        }
    }

    if (!InsideBoard(mouseX, mouseY)) {
        return false;
    }

    if (mouse == sf::Mouse::Right && running && !lost) {
        int pointX = floor((mouseX - leftOffset) / (16 * scaleFactor));
        int pointY = floor((mouseY - topOffset) / (16 * scaleFactor));

        if (gameBoard -> getHidden(pointX, pointY) == 0) {

            gameBoard -> setSprite(pointX, pointY, 34, 49, 16, 16);
            gameBoard -> setHidden(pointX, pointY, 2);
            gameBoard->decrementBombs();
        }

        else if (gameBoard -> getHidden(pointX, pointY) == 2) {
            gameBoard -> setSprite(pointX, pointY, 0, 49, 16, 16);
            gameBoard -> setHidden(pointX, pointY, 0);
            gameBoard->incrementBombs();
        }
        return true;
    }
    if (mouse == sf::Mouse::Left && !lost) {

        if (!running) {
            InitializeBoard(gameBoard, (mouseX - leftOffset) / (16 * scaleFactor), (mouseY - topOffset) / (16 * scaleFactor));
            gameBoard -> setRunning(true);
            gameBoard->resetClock();
        }
        RevealSquare(gameBoard, mouseX, mouseY, false);
        return true;
    }

    return false;
}

bool InsideBoard(int mouseX, int mouseY) {
    if (mouseX < leftOffset || mouseX > leftOffset + (boardWidth * scaleFactor * 16)) {
        return false;
    }

    if (mouseY < topOffset || mouseY > topOffset + (boardHeight * scaleFactor * 16)) {
        return false;
    }

    return true;

}
bool RevealSquare(GameBoard *gameBoard, int mouseX, int mouseY, bool recursion) {

    if (!InsideBoard(mouseX, mouseY)) {
        return false;
    }

    int pointX = floor((mouseX - leftOffset) / (16 * scaleFactor));
    int pointY = floor((mouseY - topOffset) / (16 * scaleFactor));

    int numberInSquare = gameBoard -> getBoard(pointX, pointY);
    int hiddenNumber = gameBoard -> getHidden(pointX, pointY);

    if (hiddenNumber == 1 && !recursion) {
        return false;
    }

    if (numberInSquare == -1) {
        return false;
    }

    // If there is a flag in the square, turn it into a normal block
    if (hiddenNumber == 2) {
        gameBoard -> setSprite(pointX, pointY, 0, 49, 16, 16);
        gameBoard -> setHidden(pointX, pointY, 0);
        gameBoard->incrementBombs();
        return false;
    }

    // If the number is 0 (black square), Flood fill
    if (numberInSquare == 0 && !recursion) {
        gameBoard->addRevealed(FloodFill(gameBoard, pointX, pointY));

        for (int i = 0; i < boardWidth; ++i) {
            for (int j = 0; j < boardHeight; ++j) {
                if (gameBoard -> getHidden(i, j) == 1) {
                    RevealSquare(gameBoard, (i * 16 * scaleFactor) + leftOffset, (j * 16 * scaleFactor) + topOffset, true);
                }
            }
        }

        if ((boardWidth * boardHeight) - gameBoard->getRevealed() == numBombs) {
            gameBoard->setButton(72, 24, 24, 24);
            cout << "win";
            gameBoard->setLost(true);
            return true;
        }
        return false;
    }

    if (!recursion) {
        gameBoard->incrementRevealed();
    }

    // If the number is 0 and flood fill is currently occuring, reveal the square
    if (numberInSquare == 0) {

        gameBoard -> setSprite(pointX, pointY, 17, 49, 16, 16);

        if ((boardWidth * boardHeight) - gameBoard->getRevealed() == numBombs) {
            gameBoard->setButton(72, 24, 24, 24);
            cout << "win";
            gameBoard->setLost(true);
            return true;
        }
        return false;
    }

    if (numberInSquare == 9) {
        gameBoard -> setSprite(pointX, pointY, 102, 49, 16, 16);
        ShowBombs(gameBoard, pointX, pointY);
        cout << "Lost\n";
        gameBoard->setLost(true);
        gameBoard->setButton(100, 24, 24, 24);
        return true;
    }

    gameBoard -> setSprite(pointX, pointY, 17 * (numberInSquare - 1), 66, 16, 16);
    gameBoard -> setHidden(pointX, pointY, 1);

    if ((boardWidth * boardHeight) - gameBoard->getRevealed() == numBombs) {
        gameBoard->setButton(75, 24, 24, 24);
        cout << "win";
        gameBoard->setLost(true);
        return true;
    }
    return false;
}

bool ShowBombs(GameBoard* gameBoard, int pointX, int pointY) {
    for (int i = 0; i < boardWidth; ++i) {
        for (int j = 0; j < boardHeight; ++j) {
            if (i == pointX && j == pointY) {
                continue;
            }
            if (gameBoard -> getBoard(i, j) == 9) {
                if (gameBoard -> getHidden(i, j)) {
                    continue;
                }
                gameBoard -> setSprite(i, j, 85, 49, 16, 16);
                continue;
            }
            if (gameBoard->getHidden(i, j) == 2) {
                gameBoard->setSprite(i, j, 119, 49, 16, 16);
                continue;
            }
        }
    }
    return false;
}

int Modulo(int a, int b) {
    return a - abs(b) * floor(a / abs(b));
}

bool UpdateTimer(GameBoard* gameBoard) {
    if (gameBoard->getLost()) {
        return true;
    }
    if (!gameBoard->getRunning()) {
        gameBoard->setCounter(0, 10);
        gameBoard->setCounter(1, 10);
        gameBoard->setCounter(2, 10);

        gameBoard->setCounter(3, 10);
        gameBoard->setCounter(4, 10);
        gameBoard->setCounter(5, 10);

        return true;
    }
    int time = gameBoard->getTime();

    int hundred;
    int ten;
    int one;

    int numBomb = gameBoard->getBombs();
    if (numBomb > numBombs) {
        numBomb = numBombs;
    }

    if (numBomb < 0) {
        numBomb = 0;
    }

    int bombHundred;
    int bombTen;
    int bombOne;

    if (time < 999) {
        hundred = floor(time / 100);
        ten = Modulo(floor(time / 10), 10);
        one = Modulo(time, 10);
    }
    else {
        hundred = 9;
        ten = 9;
        one = 9;
    }

    gameBoard->setCounter(0, one);
    gameBoard->setCounter(1, ten);
    gameBoard->setCounter(2, hundred);

    if (numBomb < 999) {
        bombHundred = floor(numBomb / 100);
        bombTen = Modulo((floor(numBomb / 10)), 10);
        bombOne = Modulo(numBomb, 10);
    }
    else {
        bombHundred = 9;
        bombTen = 9;
        bombOne = 9;
    }

    gameBoard->setCounter(5, bombOne);
    gameBoard->setCounter(4, bombTen);
    gameBoard->setCounter(3, bombHundred);

    return true;
}