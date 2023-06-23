#ifndef PLATFORMINGSTATE_HPP
#define PLATFORMINGSTATE_HPP

#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../entities/Character.hpp"

class PlatformingState : public GameState
{
private:
    Character player;

    float playerSpeed;
    float jumpSpeed;
    bool isJumping;
    bool leftside;
    bool rightside;
    bool spaceKeyPressed;

    std::vector<std::string> levelData;
    sf::Clock jumpTimer; // Added jumpTimer declaration
    float gravity;
    float jumpAcceleration;
    float maxJumpVelocity;
    sf::Vector2f movement;




    GameState*& currentState;
    GameState*& pState;
    GameState*& cState;

public:
    PlatformingState(GameState*& currentState, GameState*& pState, GameState*& cState, const std::vector<std::string>& levelData);
    void setSpaceKeyPressed(bool value);
    void handleInput(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    int getState() const override;
    void setLevelData(const std::vector<std::string>& data);
    std::string getPlayerExitDirection(const sf::RenderWindow& window) const;
    void updatePlayerPosition(const std::string& exitDirection, const sf::RenderWindow& window);
    void jumping(float deltaTime);
    void collision(float deltaTime);




    
};

#endif // PLATFORMINGSTATE_HPP
