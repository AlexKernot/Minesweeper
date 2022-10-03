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

int main()
{
    int mouseX = 0;
    int mouseY = 0;
    int numberInSquare = 0;

    sf::RenderWindow window(sf::VideoMode(17*boardHeight*scaleFactor + leftOffset + rightOffset, 17*boardWidth*scaleFactor + topOffset + bottomOffset), "Minesweeper", sf::Style::Close);

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
        for (int i = 0; i < boardHeight; ++i) {
            for (int j = 0; j < boardWidth; ++j) {
                sf::Sprite sprite = gameBoard.getSprite(i, j);
                window.draw(sprite);
            }
        }

        window.display();
    }

    return 0;
}

bool MouseClick(sf::Event *event, GameBoard *gameBoard) {

    sf::Mouse::Button mouse = event -> mouseButton.button;
    int mouseX = event -> mouseButton.x;
    int mouseY = event -> mouseButton.y;

    bool running = gameBoard -> getRunning();
    bool lost = gameBoard -> getLost();

    if (!InsideBoard(mouseX, mouseY)) {
        return false;
    }

    if (mouse == sf::Mouse::Right && running && !lost) {
        int pointX = floor((mouseX - leftOffset) / (17 * scaleFactor));
        int pointY = floor((mouseY - topOffset) / (17 * scaleFactor));

        if (gameBoard -> getHidden(pointX, pointY) == 0) {

            gameBoard -> setSprite(pointX, pointY, 34, 49, 17, 17);
            gameBoard -> setHidden(pointX, pointY, 2);
        }

        else if (gameBoard -> getHidden(pointX, pointY) == 2) {
            gameBoard -> setSprite(pointX, pointY, 0, 49, 17, 17);
            gameBoard -> setHidden(pointX, pointY, 0);
        }
    }
    if (mouse == sf::Mouse::Left && !lost) {

        if (!running) {
            InitializeBoard(gameBoard, (mouseX - leftOffset) / (17 * scaleFactor), (mouseY - topOffset) / (17 * scaleFactor));
            gameBoard -> setRunning(true);
        }
        lost = RevealSquare(gameBoard, mouseX, mouseY, false);
    }
}

bool InsideBoard(int mouseX, int mouseY) {
    if (mouseX < leftOffset || mouseX > leftOffset + (boardWidth * scaleFactor * 17)) {
        return false;
    }

    if (mouseY < topOffset || mouseY > topOffset + (boardHeight * scaleFactor * 17)) {
        return false;
    }

    return true;

}
bool RevealSquare(GameBoard *gameBoard, int mouseX, int mouseY, bool recursion) {

    if (!InsideBoard(mouseX, mouseY)) {
        return false;
    }

    int pointX = floor((mouseX - leftOffset) / (17 * scaleFactor));
    int pointY = floor((mouseY - topOffset) / (17 * scaleFactor));

    int numberInSquare = gameBoard -> getBoard(pointX, pointY);
    int hiddenNumber = gameBoard -> getHidden(pointX, pointY);

    if (numberInSquare == -1) {
        return false;
    }

    // If there is a flag in the square, turn it into a normal block
    if (hiddenNumber == 2) {
        gameBoard -> setSprite(pointX, pointY, 0, 49, 17, 17);
        gameBoard -> setHidden(pointX, pointY, 0);
        return false;
    }

    // If the number is 0 (black square), Flood fill
    if (numberInSquare == 0 && !recursion) {
        FloodFill(gameBoard, pointX, pointY);

        for (int i = 0; i < boardHeight; ++i) {
            for (int j = 0; j < boardWidth; ++j) {
                if (gameBoard -> getHidden(i, j) == 1) {
                    RevealSquare(gameBoard, (i * 17 * scaleFactor) + leftOffset, (j * 17 * scaleFactor) + topOffset, true);
                }
            }
        }
    }

    // If the number is 0 and flood fill is currently occuring, reveal the square
    if (numberInSquare == 0) {
        gameBoard -> setSprite(pointX, pointY, 17, 49, 17, 17);
        return false;
    }

    if (numberInSquare == 9) {
        gameBoard -> setSprite(pointX, pointY, 102, 49, 17, 17);
        ShowBombs(gameBoard, pointX, pointY);
        cout << "Lost\n";
        gameBoard->setLost(true);
        return true;
    }

    gameBoard -> setSprite(pointX, pointY, 17 * (numberInSquare - 1), 66, 17, 17);
    gameBoard -> setHidden(pointX, pointY, 1);
    return false;

}

bool ShowBombs(GameBoard* gameBoard, int pointX, int pointY) {
    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            if (i == pointX && j == pointY) {
                continue;
            }
            if (gameBoard -> getBoard(i, j) == 9) {
                if (gameBoard -> getHidden(i, j)) {
                    continue;
                }
                gameBoard -> setSprite(i, j, 85, 49, 17, 17);
                continue;
            }
            if (gameBoard->getHidden(i, j) == 2) {
                gameBoard->setSprite(i, j, 119, 49, 17, 17);
                continue;
            }
        }
    }
    return false;
}