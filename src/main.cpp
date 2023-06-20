#include <iostream>
#include <SFML/Graphics.hpp>
#include "states/MainMenuState.hpp"
#include "states/PlatformingState.hpp"
#include "states/PauseMenuState.hpp"
#include "states/GameState.hpp"
#include "states/CombatState.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    GameState* currentState = nullptr;
    GameState* pState = nullptr;

    GameState* cState = nullptr;


    PlatformingState platformingState(currentState, pState, cState);

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

        currentState->handleInput(window);
        currentState->update(deltaTime);

        window.clear(sf::Color::Black);

        currentState->render(window);

        window.display();
    }

    return 0;
}



