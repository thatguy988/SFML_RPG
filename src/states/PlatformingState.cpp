#include "PlatformingState.hpp"
#include "PauseMenuState.hpp"

PlatformingState::PlatformingState(GameState*& currentState, GameState*& pState, GameState*& cState)
    : currentState(currentState), pState(pState), cState(cState)
{
    // Initialize player and ground
    player.setSize(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Red);
    player.setPosition(400.0f, 500.0f);

    playerSpeed = 25.0f;
    jumpSpeed = 50.0f;
    isJumping = false;
    spaceKeyPressed = true;

    ground.setSize(sf::Vector2f(800.0f, 50.0f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0.0f, 550.0f);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement.x -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
    sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

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

void PlatformingState::update(float deltaTime)
{
    float gravity = 50.0f;
    sf::Vector2f movement(0.0f, gravity * deltaTime);
    player.move(movement);

    // Perform bounds checking to prevent player from falling through the ground
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect groundBounds = ground.getGlobalBounds();

    if (playerBounds.intersects(groundBounds))
    {
        isJumping = false;
        player.setPosition(player.getPosition().x, ground.getPosition().y - player.getSize().y);
    }
}

void PlatformingState::render(sf::RenderWindow& window)
{
    window.draw(ground);
    window.draw(player);
}
