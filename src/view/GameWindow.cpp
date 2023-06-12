#include "project/view/GameWindow.h"
#include <iostream>
#include <filesystem>

GameWindow::GameWindow() : window(sf::VideoMode(800, 600), "Game Window") {
    if (!font.loadFromFile("C:\\Users\\jakob\\Desktop\\SFML_RPG\\fonts\\Daydream.ttf")) {
        std::cout << "Failed to load font file" << std::endl;
        // Handle font loading error
    }

    // Configure the text
    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setPosition(100, 100);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Game Title");

    startText.setFont(font);
    startText.setCharacterSize(24);
    startText.setPosition(100, 200);
    startText.setFillColor(sf::Color::White);
    startText.setString("Start");

    quitText.setFont(font);
    quitText.setCharacterSize(24);
    quitText.setPosition(100, 250);
    quitText.setFillColor(sf::Color::White);
    quitText.setString("Quit");
}

void GameWindow::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Update and draw your game logic here
        window.draw(titleText);
        window.draw(startText);
        window.draw(quitText);

        window.display();
    }
}
