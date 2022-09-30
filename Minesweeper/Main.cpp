using namespace std;

#include <iostream>
#include <SFML/Graphics.hpp>
#include "InitializeBoard.h"
#include <cmath>
#include "FloodFill.h"

const int boardHeight = 16;
const int boardWidth = 16;

int main()
{
    bool running = false;
    int mouseX = 0;
    int mouseY = 0;
    int numberInSquare = 0;

    sf::RenderWindow window(sf::VideoMode(17*boardHeight, 17*boardWidth), "Minesweeper");

    vector<vector<int>> board;
    
    vector<vector<int>> hidden;
    hidden.resize(boardHeight);

    for (int i = 0; i < boardHeight; ++i) {
        hidden[i].resize(boardWidth);
    }

    sf::Texture texture;
    if (!texture.loadFromFile("sprites.png")) {
        cout << "The texture could not be loaded";
    }

    sf::Sprite sprite[boardHeight][boardWidth];
    for (int i = 0; i < boardHeight; ++i) 
    {
        for (int j = 0; j < boardWidth; j++) 
        {
            sprite[i][j].setTexture(texture);
            sprite[i][j].setTextureRect(sf::IntRect(0, 49, 17, 17));
            sprite[i][j].setPosition(17.0f * i, 17.0f * j);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && !running) {

                    mouseX = event.mouseButton.x;
                    mouseX = floor(mouseX / 17);

                    mouseY = event.mouseButton.y;
                    mouseY = floor(mouseY / 17);

                    board = InitializeBoard(board, mouseX, mouseY);
                    running = true;
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    numberInSquare = 10;
                    mouseX = event.mouseButton.x;
                    mouseX = floor(mouseX / 17);

                    mouseY = event.mouseButton.y;
                    mouseY = floor(mouseY / 17);

                    if (mouseY < 16 && mouseX < 16 && mouseY > -1 && mouseX > -1) {
                        numberInSquare = board[mouseX][mouseY];
                        hidden[mouseX][mouseY] = 1;
                    }

                    if (numberInSquare == 0) {
                        hidden[mouseX][mouseY] = 0;
                        hidden = FloodFill(board, hidden, mouseX, mouseY);
                        cout << "Flood\n";

                        for (int i = 0; i < boardHeight; ++i) {
                            for (int j = 0; j < boardWidth; ++j) {
                                if (hidden[i][j] == 1) {
                                    numberInSquare = board[i][j];
                                    if (numberInSquare == 0) {
                                        sprite[i][j].setTextureRect(sf::IntRect(17, 49, 17, 17));
                                    }
                                    else if (numberInSquare == 9) {
                                        sprite[i][j].setTextureRect(sf::IntRect(102, 49, 17, 17));
                                    }
                                    else if (numberInSquare < 9) {
                                        sprite[i][j].setTextureRect(sf::IntRect(17 * (numberInSquare - 1), 66, 17, 17));
                                    }
                                }
                            }
                        }

                        for (int i = 0; i < boardHeight; ++i) {
                            for (int j = 0; j < boardWidth; ++j) {
                                cout << hidden[i][j] << " ";
                            }
                            cout << "\n";
                        }
                    }
                    else if (numberInSquare == 9) {
                        sprite[mouseX][mouseY].setTextureRect(sf::IntRect(102, 49, 17, 17));
                    }
                    else if (numberInSquare < 9) {
                        sprite[mouseX][mouseY].setTextureRect(sf::IntRect(17 * (numberInSquare - 1), 66, 17, 17));
                        hidden[mouseX][mouseY] = 1;
                    }
                }
            }
        }

        window.clear();
        for (int i = 0; i < boardHeight; ++i) {
            for (int j = 0; j < boardWidth; ++j) {
                window.draw(sprite[i][j]);
            }
        }

        window.display();
    }

    return 0;
}