#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "states/MainMenuState.hpp"
#include "states/PlatformingState.hpp"
#include "states/PauseMenuState.hpp"
#include "states/GameState.hpp"
#include "states/CombatState.hpp"
#include "leveldata.hpp" 


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    GameState* currentState = nullptr;
    GameState* pState = nullptr;
    GameState* cState = nullptr;



    std::vector<std::string> levelData = getLevelData(); // Retrieve level data

    PlatformingState platformingState(currentState, pState, cState, levelData);
    CombatState combatState(currentState, &platformingState);
    MainMenuState mainMenuState(currentState, &platformingState);
    PauseMenuState pauseMenuState(currentState, &platformingState, &mainMenuState);

    pState = &pauseMenuState;
    cState = &combatState;
    currentState = &mainMenuState;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear(sf::Color::Black);

        switch (currentState->getState())
        {
            case 0://main menu
                currentState->handleInput(window);
                currentState->update(deltaTime);
                currentState->render(window);
                break;

            case 1://platforming state
                currentState->handleInput(window);
                currentState->update(deltaTime);
                currentState->render(window);
                
                break;

            case 2://combat
                currentState->handleInput(window);
                currentState->update(deltaTime);
                currentState->render(window);
                break;

            case 3://pause menu
                currentState->handleInput(window);
                currentState->update(deltaTime);
                currentState->render(window);
                break;


            default:
                break;
        }

        window.display();
    }

    return 0;
}

