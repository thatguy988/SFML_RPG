#ifndef PLATFORMINGSTATE_HPP
#define PLATFORMINGSTATE_HPP

#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class PlatformingState : public GameState
{
private:
    sf::RectangleShape player;
    float playerSpeed;
    float jumpSpeed;
    bool isJumping;
    bool spaceKeyPressed;
    sf::RectangleShape ground;

    GameState*& currentState;
    GameState*& pState;
    GameState*& cState;

public:
    PlatformingState(GameState*& currentState, GameState*& pState, GameState*& cState);
    void setSpaceKeyPressed(bool value);
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

#endif // PLATFORMINGSTATE_HPP
