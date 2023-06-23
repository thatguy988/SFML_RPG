#include "PlatformingState.hpp"
#include "PauseMenuState.hpp"


#include <algorithm>


PlatformingState::PlatformingState(GameState*& currentState, GameState*& pState, GameState*& cState, const std::vector<std::string>& levelData)
    : currentState(currentState), pState(pState), cState(cState), levelData(levelData),
    player("Player", 100, {"Water"}, {"Fire"}, sf::Vector2f(50.0f, 50.0f), sf::Color::Red, sf::Vector2f(100.0f, 400.0f))

{

    playerSpeed = 5.0f;
    jumpSpeed = 0.0f;
    isJumping = false;
    spaceKeyPressed = false;
    gravity = 175.0f;
    jumpAcceleration = 50.0f;
    maxJumpVelocity = 200.0f;
    
    leftside = false;
    rightside = false;
    

}

void PlatformingState::setLevelData(const std::vector<std::string>& data)
{
    levelData = data;
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
        rightside = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !rightside)
    {
        movement.x += playerSpeed;
        leftside = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!isJumping && !spaceKeyPressed)
        {
            movement.y -= jumpSpeed;
            isJumping = true;
            spaceKeyPressed = true;
            jumpTimer.restart();

        
        }
    }
    else
    {
        spaceKeyPressed = false;
    }
    //add offset to sides of window to go offscreen

    sf::FloatRect playerBounds = player.getBounds();
    sf::FloatRect windowBounds(-5.0f, -5.0f, window.getSize().x + 65.0f, window.getSize().y + 65.0f);

    if (!windowBounds.contains(playerBounds.left + movement.x, playerBounds.top) ||
        !windowBounds.contains(playerBounds.left + playerBounds.width + movement.x, playerBounds.top) ||
        !windowBounds.contains(playerBounds.left + playerBounds.width + movement.x, playerBounds.top + playerBounds.height) ||
        !windowBounds.contains(playerBounds.left + movement.x, playerBounds.top + playerBounds.height))
    {
        // Adjust movement to prevent moving outside the window
        movement.x = 0.0f;
    }


    player.move(movement);
}

std::string PlatformingState::getPlayerExitDirection(const sf::RenderWindow& window) const
{
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2u windowSize = window.getSize();

    std::string exitDirection;

    if (playerPosition.x < 0) {
        // Player exited on the left side of the window
        exitDirection = "left";
    } else if (playerPosition.x > windowSize.x) {
        // Player exited on the right side of the window
        exitDirection = "right";
    } else if (playerPosition.y < 0) {
        // Player exited on the top side of the window
        exitDirection = "up";
    } else if (playerPosition.y > windowSize.y) {
        // Player exited on the bottom side of the window
        exitDirection = "down";
    }

    return exitDirection;
}

void PlatformingState::updatePlayerPosition(const std::string& exitDirection,const sf::RenderWindow& window)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2f newPosition;

    if (exitDirection == "left") {
        newPosition = sf::Vector2f(windowSize.x, playerPosition.y);
    } else if (exitDirection == "right") {
        newPosition = sf::Vector2f(0, playerPosition.y);
    } else if (exitDirection == "up") {
        newPosition = sf::Vector2f(playerPosition.x, windowSize.y);
    } else if (exitDirection == "down") {
        newPosition = sf::Vector2f(playerPosition.x, 0);
    }

    player.setPosition(newPosition);
}

void PlatformingState::jumping(float deltaTime)
{

    sf::Vector2f movement(0.0f, gravity * deltaTime);
    if(!isJumping && spaceKeyPressed)
    {
    // Apply jump acceleration until reaching maximum jump velocity
        if (jumpTimer.getElapsedTime().asSeconds() < 0.45f) // Adjust the duration as needed
        {
            jumpSpeed += jumpAcceleration * deltaTime;
            jumpSpeed = std::min(jumpSpeed, maxJumpVelocity);

            movement.y -= jumpSpeed;
    }
    else
    {
        isJumping = false;
        jumpSpeed = 0.0f;
    }
    }
    player.move(movement);
}

void PlatformingState::collision(float deltaTime)
{
    // Perform bounds checking to prevent player from falling through the ground
    sf::FloatRect playerBounds = player.getBounds();
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
                            player.move(sf::Vector2f(-dx, gravity * deltaTime));

                            //player.move(-dx, gravity * deltaTime);
                            rightside = true;
                            
                            
                            
                        }
                        else 
                        {
                            player.move(sf::Vector2f(dx, gravity * deltaTime));

                            //player.move(dx, gravity * deltaTime);
                            leftside = true;
                            
                            
                            
                        }
                    }
                    else
                    {   
                        
                        // Adjust vertical position
                        if (dy == std::abs(tileBounds.top - playerBottom))
                        {
                            
                            sf::Vector2f movement(0.0f, -dy);
                            


                            //movement.y = -dy;
                            player.move(movement);
                            //player.move(0.0f, -dy);
                            isJumping = false; // Reset jumping flag if player lands on a tile
                            
                        }
                        else
                        {
                            

                            sf::Vector2f movement(0.0f, dy);

                            //movement.y = dy;
                            player.move(movement);
                            //player.move(0.0f, dy);
                        }
                        
                        
                            
                    }
                    
                    
                }
                else
                {
                    leftside = false;
                    rightside = false;
                }
            }
        }
    }

}


void PlatformingState::update(float deltaTime)
{
    


    jumping(deltaTime); 
    collision(deltaTime);   
    
    
}

void PlatformingState::render(sf::RenderWindow& window)
{
    
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








