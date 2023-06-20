#include "CombatState.hpp"

CombatState::CombatState(GameState*& currentState, PlatformingState* platformingState)
{
    // Initialize member variables and setup your combat state
}

CombatState::~CombatState()
{
    // Clean up any dynamically allocated resources
}

void CombatState::handleInput(sf::RenderWindow& window)
{
    // Handle input for your combat state
}

void CombatState::update(float deltaTime)
{
    // Update your combat state logic
}

void CombatState::render(sf::RenderWindow& window)
{
    // Render your combat state
}

void transitionToPlatformingState(GameState*& currentState, GameState* platformingState)
{
    // Clean up the combat state
    delete currentState;

    // Set the game state to the platforming state
    currentState = platformingState;
}
