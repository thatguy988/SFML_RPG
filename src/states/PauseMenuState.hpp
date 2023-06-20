#ifndef PAUSEMENUSTATE_HPP
#define PAUSEMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "PlatformingState.hpp"
#include "MainMenuState.hpp"

class PauseMenuState : public GameState
{
private:
    sf::Text titleText;
    sf::Text resumeText;
    sf::Text saveText;
    sf::Text quitText;
    sf::Text cursorText;
    
    sf::Font font;

    int selectedOption;

    bool wKeyPressed;
    bool sKeyPressed;
    bool spaceKeyPressed;


    GameState*& currentState;
    PlatformingState* platformingState; 
    MainMenuState* mainMenuState;

public:
    PauseMenuState(GameState*& currentState, PlatformingState* platformingState, MainMenuState* mainMenuState);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

#endif // PAUSEMENUSTATE_HPP
