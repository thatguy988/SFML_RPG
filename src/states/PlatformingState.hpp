#ifndef PLATFORMINGSTATE_HPP
#define PLATFORMINGSTATE_HPP

#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PlatformingState : public GameState
{
private:
    sf::RectangleShape player;
    float playerSpeed;
    float jumpSpeed;
    bool isJumping;
    bool leftside;
    bool rightside;
    bool spaceKeyPressed;
    sf::RectangleShape ground;

    std::vector<std::string> levelData;



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




    
};

#endif // PLATFORMINGSTATE_HPP
