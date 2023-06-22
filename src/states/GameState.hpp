#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual int getState() const = 0; // Add this function to retrieve the current state

    virtual ~GameState() {}
};

#endif // GAMESTATE_HPP
