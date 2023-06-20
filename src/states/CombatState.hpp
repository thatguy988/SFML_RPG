#ifndef COMBATSTATE_HPP
#define COMBATSTATE_HPP

#include "GameState.hpp" // Assuming GameState.hpp is included
#include <SFML/Graphics.hpp>
#include "PlatformingState.hpp"



class CombatState : public GameState
{
private:
    // Add necessary member variables for your combat state

public:
    CombatState(GameState*& currentState, PlatformingState* platformingState);
    virtual ~CombatState();

    virtual void handleInput(sf::RenderWindow& window) override;
    virtual void update(float deltaTime) override;
    virtual void render(sf::RenderWindow& window) override;
    static void transitionToPlatformingState(GameState*& currentState, GameState* platformingState);

};


#endif // COMBATSTATE_HPP
