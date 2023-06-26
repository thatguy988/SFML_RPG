#include "PlatformingState.hpp"
#include "PauseMenuState.hpp"


#include <algorithm>
#include <SFML/Graphics/View.hpp>



PlatformingState::PlatformingState(GameState*& currentState, GameState*& pState, GameState*& cState, const std::vector<std::vector<int>>& levelData)
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

    view.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));

}

void PlatformingState::setLevelData(const std::vector<std::vector<int>>& data)
{
    levelData.clear();  // Clear the existing levelData vector

    // Copy each row of the 2D vector to levelData
    for (const auto& row : data)
    {
        levelData.push_back(row);
    }
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
    
    player.move(movement);
    // Update the view's center position based on the player's position
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float minX = viewSize.x / 2.0f;
    float maxX = levelData[0].size() * tileSize - viewSize.x / 2.0f;
    float minY = viewSize.y / 2.0f;
    float maxY = levelData.size() * tileSize - viewSize.y / 2.0f;

    if (playerPosition.x < minX)
    {
        playerPosition.x = minX;
    }
    else if (playerPosition.x > maxX)
    {
        playerPosition.x = maxX;
    }

    if (playerPosition.y < minY)
    {
        playerPosition.y = minY;
    }
    else if (playerPosition.y > maxY)
    {
        playerPosition.y = maxY;
    }




    view.setCenter(playerPosition);

    // Apply the view to the render window
    window.setView(view);
}



// std::string PlatformingState::getPlayerExitDirection(const sf::RenderWindow& window) const //for window
// {
//     sf::Vector2f playerPosition = player.getPosition();
//     sf::Vector2u windowSize = window.getSize();

//     std::string exitDirection;

//     if (playerPosition.x < 0) {
//         // Player exited on the left side of the window
//         exitDirection = "left";
//     } else if (playerPosition.x > windowSize.x) {
//         // Player exited on the right side of the window
//         exitDirection = "right";
//     } else if (playerPosition.y < 0) {
//         // Player exited on the top side of the window
//         exitDirection = "up";
//     } else if (playerPosition.y > windowSize.y) {
//         // Player exited on the bottom side of the window
//         exitDirection = "down";
//     }

//     return exitDirection;
// }

std::string PlatformingState::getPlayerExitDirection(const sf::RenderWindow& window) const //for view
{
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    std::string exitDirection;

    if (playerPosition.x < viewCenter.x - viewSize.x / 2) {
        // Player exited on the left side of the view
        exitDirection = "left";
    } else if (playerPosition.x > viewCenter.x + viewSize.x / 2) {
        // Player exited on the right side of the view
        exitDirection = "right";
    } else if (playerPosition.y < viewCenter.y - viewSize.y / 2) {
        // Player exited on the top side of the view
        exitDirection = "up";
    } else if (playerPosition.y > viewCenter.y + viewSize.y / 2) {
        // Player exited on the bottom side of the view
        exitDirection = "down";
    }

    return exitDirection;
}


void PlatformingState::updatePlayerPosition(const std::string& exitDirection)
{
    int spawnMarker = 0;

    // Determine the spawn marker value based on the exit direction
    if (exitDirection == "up")
    {
        spawnMarker = 2;
    }
    else if (exitDirection == "down")
    {
        spawnMarker = 3;
    }
    else if (exitDirection == "right")
    {
        spawnMarker = 4;
    }
    else if (exitDirection == "left")
    {
        spawnMarker = 5;
    }
    sf::Vector2f spawnPosition;


    // Find the spawn marker in the level data
    for (size_t i = 0; i < levelData.size(); ++i)
    {
        const std::vector<int>& row = levelData[i];
        for (size_t j = 0; j < row.size(); ++j)
        {
            if (row[j] == spawnMarker) 
            {
                // Set the player's spawn position
                spawnPosition.x = static_cast<float>(j) * tileSize;
                spawnPosition.y = static_cast<float>(i) * tileSize;
                player.setPosition(spawnPosition);


                return; 
            }
        }
    }
    
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

    for (size_t i = 0; i < levelData.size(); ++i)
    {
        for (size_t j = 0; j < levelData[i].size(); ++j)
        {
            if (levelData[i][j] == 1) // Tile present
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
                            rightside = true;
                        }
                        else
                        {
                            player.move(sf::Vector2f(dx, gravity * deltaTime));
                            leftside = true;
                        }
                    }
                    else
                    {
                        // Adjust vertical position
                        if (dy == std::abs(tileBounds.top - playerBottom))
                        {
                            sf::Vector2f movement(0.0f, -dy);
                            player.move(movement);
                            isJumping = false; // Reset jumping flag if player lands on a tile
                        }
                        else
                        {
                            sf::Vector2f movement(0.0f, dy);
                            player.move(movement);
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
    window.setView(view);
    window.draw(player);

    for (size_t i = 0; i < levelData.size(); ++i)
    {
        const std::vector<int>& row = levelData[i];
        for (size_t j = 0; j < row.size(); ++j)
        {
            if (row[j] == 1) // Tile present
            {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setFillColor(sf::Color::Blue);
                tile.setPosition(static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize);
                window.draw(tile);
            }
        }
    }
}









