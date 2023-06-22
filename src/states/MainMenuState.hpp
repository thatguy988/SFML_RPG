#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "PlatformingState.hpp"

class MainMenuState : public GameState
{
private:
    sf::Text titleText;
    sf::Text startText;
    sf::Text loadText;
    sf::Text quitText;
    sf::Text cursorText;  
    sf::Event event;

    GameState*& currentState;  
    PlatformingState* platformingState;

    bool wKeyPressed;
    bool sKeyPressed;
    bool spaceKeyPressed;

    sf::Font font;
    int selectedOption;

public:
    MainMenuState(GameState*& currentState, PlatformingState* platformingState);

    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    int getState() const override;

};

#endif // MAINMENUSTATE_HPP
