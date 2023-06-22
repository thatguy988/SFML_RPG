#include "PauseMenuState.hpp"
#include <iostream>

PauseMenuState::PauseMenuState(GameState*& currentState, PlatformingState* platformingState, MainMenuState* mainMenuState) 
    : currentState(currentState), platformingState(platformingState), mainMenuState(mainMenuState)
{
    if (!font.loadFromFile("C:\\Users\\jakob\\Desktop\\SFML_RPG\\fonts\\Daydream.ttf"))
    {
        std::cout << "Error: Failed to load font file 'Daydream.ttf'." << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("Pause Menu");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(100, 100);


    resumeText.setFont(font);
    resumeText.setString("Resume Game");
    resumeText.setCharacterSize(20);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(100, 200);

    saveText.setFont(font);
    saveText.setString("Save Game");
    saveText.setCharacterSize(20);
    saveText.setFillColor(sf::Color::White);
    saveText.setPosition(100, 250);

    quitText.setFont(font);
    quitText.setString("Quit Game");
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

int PauseMenuState::getState() const
{
    return 3; // Return the state value for the main menu state
}

void PauseMenuState::handleInput(sf::RenderWindow& window)
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
                selectedOption=0;
                currentState = platformingState;
            }
            else if (selectedOption == 1)
            {
                // Save option selected, save game state
            }
            else if (selectedOption == 2)
            {
                selectedOption=0;
                currentState = mainMenuState;
            }

            spaceKeyPressed = true;
        }
    }
    else
    {
        spaceKeyPressed = false;
    }
}

void PauseMenuState::update(float deltaTime)
{
    cursorText.setPosition(80, 200 + selectedOption * 50);
}

void PauseMenuState::render(sf::RenderWindow& window)
{
    window.draw(titleText);
    window.draw(resumeText);
    window.draw(saveText);
    window.draw(quitText);
    window.draw(cursorText);  
}
