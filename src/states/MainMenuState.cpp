#include "MainMenuState.hpp"
#include <iostream>

MainMenuState::MainMenuState(GameState*& currentState, PlatformingState* platformingState) 
    : currentState(currentState), platformingState(platformingState)
{
    if (!font.loadFromFile("C:\\Users\\jakob\\Desktop\\SFML_RPG\\fonts\\Daydream.ttf"))
    {
        std::cout << "Error: Failed to load font file 'Daydream.ttf'." << std::endl;
    }

    // Initialize text for title start quit cursor
    titleText.setFont(font);
    titleText.setString("Main Menu");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(100, 100);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(20);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(100, 200);

    loadText.setFont(font);
    loadText.setString("Load Game");
    loadText.setCharacterSize(20);
    loadText.setFillColor(sf::Color::White);
    loadText.setPosition(100, 250);

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(20);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(100, 300);

    cursorText.setFont(font);
    cursorText.setString(">");
    cursorText.setCharacterSize(20);
    cursorText.setFillColor(sf::Color::White);

    wKeyPressed = false;
    sKeyPressed = false;
    spaceKeyPressed = false;

    selectedOption = 0;
}

void MainMenuState::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (!wKeyPressed)
        {
            selectedOption = (selectedOption - 1 + 3) % 3;  // Move selection up
            wKeyPressed = true;
        }
    }
    else
    {
        wKeyPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (!sKeyPressed)
        {
            selectedOption = (selectedOption + 1) % 3;  // Move selection down
            sKeyPressed = true;
        }
    }
    else
    {
        sKeyPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!spaceKeyPressed)
        {
            if (selectedOption == 0)
            {
                platformingState->setSpaceKeyPressed(true); 
                selectedOption = 0;
                currentState = platformingState;
            }
            else if (selectedOption == 1)
            {
                selectedOption = 0;
                // Load option selected, load game state
            }
            else if (selectedOption == 2)
            {
                // Quit option selected, terminate the game
                window.close();
            }

            spaceKeyPressed = true;
        }
    }
    else
    {
        spaceKeyPressed = false;
    }
}

void MainMenuState::update(float deltaTime)
{
    cursorText.setPosition(80, 200 + selectedOption * 50);
}

void MainMenuState::render(sf::RenderWindow& window)
{
    window.draw(titleText);
    window.draw(startText);
    window.draw(loadText);
    window.draw(quitText);
    window.draw(cursorText);        
}
