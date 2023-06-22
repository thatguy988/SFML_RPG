#include "PlatformingState.hpp"
#include "PauseMenuState.hpp"
#include <algorithm>


PlatformingState::PlatformingState(GameState*& currentState, GameState*& pState, GameState*& cState, const std::vector<std::string>& levelData)
    : currentState(currentState), pState(pState), cState(cState), levelData(levelData)
{
    // Initialize player and ground
    player.setSize(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Red);
    player.setPosition(100.0f, 150.0f);

    playerSpeed = 5.0f;
    jumpSpeed = 35.0f;
    isJumping = false;
    spaceKeyPressed = true;

    leftside = false;
    rightside = false;

    //ground.setSize(sf::Vector2f(800.0f, 50.0f));
    //ground.setFillColor(sf::Color::Green);
    //ground.setPosition(0.0f, 550.0f);



    
}


int PlatformingState::getState() const
{
    return 1; // Return the state value for the main menu state
}

void PlatformingState::setSpaceKeyPressed(bool value)
{
    spaceKeyPressed = value;
}

void PlatformingState::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        currentState = pState;
    }

    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !leftside)
    {
        movement.x -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !rightside)
    {
        movement.x += playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!isJumping && !spaceKeyPressed)
        {
            movement.y -= jumpSpeed;
            isJumping = true;
            spaceKeyPressed = true;
        
        }
    }
    else
    {
        spaceKeyPressed = false;
    }

    // Perform bounds checking to prevent player from moving outside the window
    sf::FloatRect playerBounds = player.getGlobalBounds();
    // sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

    // if (!windowBounds.contains(playerBounds.left + movement.x, playerBounds.top) ||
    //     !windowBounds.contains(playerBounds.left + playerBounds.width + movement.x, playerBounds.top) ||
    //     !windowBounds.contains(playerBounds.left + playerBounds.width + movement.x, playerBounds.top + playerBounds.height) ||
    //     !windowBounds.contains(playerBounds.left + movement.x, playerBounds.top + playerBounds.height))
    // {
    //     // Adjust movement to prevent moving outside the window
    //     movement.x = 0.0f;
    // }

    player.move(movement);
}



void PlatformingState::update(float deltaTime)
{
    float gravity = 150.0f;
    sf::Vector2f movement(0.0f, gravity * deltaTime);
    player.move(movement);

    // Perform bounds checking to prevent player from falling through the ground
    sf::FloatRect playerBounds = player.getGlobalBounds();
    const float tileSize = 50.0f; // Assuming each tile is a square of size 50x50

    for (size_t i = 0; i < levelData.size(); ++i)
    {
        const std::string& row = levelData[i];
        for (size_t j = 0; j < row.size(); ++j)
        {
            if (row[j] == '1') // Tile present
            {
                sf::FloatRect tileBounds(static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, tileSize, tileSize);

                // Check for collision between player and tile
                if (playerBounds.intersects(tileBounds))
                {
                    // Adjust player position to prevent collision
                    float playerRight = playerBounds.left + playerBounds.width;
                    float playerBottom = playerBounds.top + playerBounds.height;
                    float tileRight = tileBounds.left + tileBounds.width;
                    float tileBottom = tileBounds.top + tileBounds.height;

                    float dx = std::min(std::abs(tileBounds.left - playerRight), std::abs(tileRight - playerBounds.left));
                    float dy = std::min(std::abs(tileBounds.top - playerBottom), std::abs(tileBottom - playerBounds.top));

                    if (dx < dy)
                    {
                        // Adjust horizontal position
                        if (dx == std::abs(tileBounds.left - playerRight))
                        {
                            player.move(-dx, 0.0f);
                            rightside = true;
                            
                            
                            
                        }
                        else 
                        {
                            player.move(dx, 0.0f);
                            leftside = true;
                            
                            
                            
                        }
                    }
                    else
                    {   
                        leftside = false;
                        rightside = false;
                        
                        
                        // Adjust vertical position
                        if (dy == std::abs(tileBounds.top - playerBottom))
                        {
                            player.move(0.0f, -dy);
                            isJumping = false; // Reset jumping flag if player lands on a tile
                            
                        }
                        else
                            player.move(0.0f, dy);
                            
                    }
                    
                    
                }
            }
        }
    }
}

void PlatformingState::render(sf::RenderWindow& window)
{
    //window.draw(ground);
    
    window.draw(player);
    const float tileSize = 50.0f; // Assuming each tile is a square of size 50x50

    for (size_t i = 0; i < levelData.size(); ++i)
    {
        const std::string& row = levelData[i];
        for (size_t j = 0; j < row.size(); ++j)
        {
            if (row[j] == '1') // Tile present
            {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setFillColor(sf::Color::Blue);
                tile.setPosition(static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize);
                window.draw(tile);
            }
        }
    }

    
}

