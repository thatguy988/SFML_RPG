#include <iostream>
#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~GameState() {}
};


class PlatformingState : public GameState
{
private:
    sf::RectangleShape player;
    float playerSpeed;
    float jumpSpeed;
    bool isJumping;

    sf::RectangleShape ground;

public:
    PlatformingState()
    {
        // Initialize player and ground
        player.setSize(sf::Vector2f(50.0f, 50.0f));
        player.setFillColor(sf::Color::Red);
        player.setPosition(400.0f, 500.0f);

        playerSpeed = 25.00f;
        jumpSpeed = 50.0f;
        isJumping = false;

        ground.setSize(sf::Vector2f(800.0f, 50.0f));
        ground.setFillColor(sf::Color::Green);
        ground.setPosition(0.0f, 550.0f);
    }

    void handleInput(sf::RenderWindow& window) override
    {

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
            if (!isJumping)
            {
                movement.y -= jumpSpeed;
                isJumping = true;
            }
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

    void update(float deltaTime) override
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

    void render(sf::RenderWindow& window) override
    {
        window.draw(ground);
        window.draw(player);
    }
};


// Pause menu state
class PauseMenuState : public GameState
{
private:
    sf::Text titleText;
    sf::Text resumeText;
    sf::Text saveText;
    sf::Text quitText;
    int selectedOption;

    GameState* platformingState; // Reference to the platforming state



public:
    PauseMenuState(GameState* platformingState)
    {
        // Initialize title and options text
        // ...

        selectedOption = 0; // Start with the first option selected
        this->platformingState = platformingState;
    }

    void handleInput(sf::RenderWindow& window) override
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    selectedOption = (selectedOption - 1 + 3) % 3; // Move selection up
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    selectedOption = (selectedOption + 1) % 3; // Move selection down
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    if (selectedOption == 0)
                    {
                        // Resume Game option selected, transition back to the platforming state
                        // ...
                    }
                    else if (selectedOption == 1)
                    {
                        // Save Game option selected, save the game
                        // ...
                    }
                    else if (selectedOption == 2)
                    {
                        // Quit option selected, transition back to the main menu state
                        // ...
                    }
                }
            }
        }
    }

    void update(float deltaTime) override
    {
        // Update any necessary logic for the pause menu state
        // ...
    }

    void render(sf::RenderWindow& window) override
    {
        // Draw the title and options text
        // ...
    }
};



class MainMenuState : public GameState
{
private:
    sf::Text titleText;
    sf::Text startText;
    sf::Text loadText;
    sf::Text quitText;
    sf::Text cursorText;  
    sf::Event event;

    GameState*& currentState;  
    PlatformingState& platformingState;  // Reference to the PlatformingState

    sf::Font font;
    int selectedOption;

    

public:
    MainMenuState(GameState*& currentStateRef, PlatformingState& platformingStateRef)
        : currentState(currentStateRef), platformingState(platformingStateRef)
    {
        if (!font.loadFromFile("C:\\Users\\jakob\\Desktop\\SFML_RPG\\fonts\\Daydream.ttf"))
        {
            std::cout << "Error: Failed to load font file 'Daydream.ttf'." << std::endl;
        }

        // Initialize text for title start quit cursor
        titleText.setFont(font);
        titleText.setString("Main Menu");
        titleText.setCharacterSize(30);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(100, 100);

        startText.setFont(font);
        startText.setString("Start Game");
        startText.setCharacterSize(20);
        startText.setFillColor(sf::Color::White);
        startText.setPosition(100, 200);

        loadText.setFont(font);
        loadText.setString("Load Game");
        loadText.setCharacterSize(20);
        loadText.setFillColor(sf::Color::White);
        loadText.setPosition(100, 250);

        quitText.setFont(font);
        quitText.setString("Quit");
        quitText.setCharacterSize(20);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(100, 300);

        cursorText.setFont(font);
        cursorText.setString(">");
        cursorText.setCharacterSize(20);
        cursorText.setFillColor(sf::Color::White);

        selectedOption = 0;  // Start with the first option selected
    }

    void handleInput(sf::RenderWindow& window) override
    {
        static bool wKeyPressed = false;
        static bool sKeyPressed = false;
        static bool spaceKeyPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (!wKeyPressed)
            {
                selectedOption = (selectedOption - 1 + 3) % 3;  // Move selection up
                wKeyPressed = true;
            }
        }
        else
        {
            wKeyPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (!sKeyPressed)
            {
                selectedOption = (selectedOption + 1) % 3;  // Move selection down
                sKeyPressed = true;
            }
        }
        else
        {
            sKeyPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (!spaceKeyPressed)
            {
                if (selectedOption == 0)
                {
                    currentState = &platformingState;
                    //delete this;  // Delete the MainMenuState

                }
                else if (selectedOption == 1)
                {
                    // Load option selected, load game state
                }
                else if (selectedOption == 2)
                {
                    // Quit option selected, terminate the game
                    window.close();
                }

                spaceKeyPressed = true;
            }
        }
        else
        {
            spaceKeyPressed = false;
        }
    }

    void update(float deltaTime) override
    {
        cursorText.setPosition(80, 200 + selectedOption * 50);
    }

    void render(sf::RenderWindow& window) override
    {
        window.draw(titleText);
        window.draw(startText);
        window.draw(loadText);
        window.draw(quitText);
        window.draw(cursorText);        
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60); // Limit the frame rate to 60 frames per second
    window.setVerticalSyncEnabled(true); // Enable VSync

    


    // Create the PlatformingState
    PlatformingState platformingState;

    // Declare the currentState variable
    GameState* currentState;

    // Create the MainMenuState and pass the currentState and platformingState as parameters
    MainMenuState mainMenuState(currentState, platformingState);

    // Set the initial state
    currentState = &mainMenuState;
    

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Handle input, update, and render based on the current state
        currentState->handleInput(window);
        currentState->update(deltaTime);

        window.clear(sf::Color::Black);

        

        currentState->render(window);
        window.display();
    }

    return 0;
}


// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");

//     // Create the PlatformingState
//     PlatformingState platformingState;

//     // Set the initial state
//     GameState* currentState = &platformingState;

//     sf::Clock clock;

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         float deltaTime = clock.restart().asSeconds();

//         // Handle input, update, and render based on the current state
//         currentState->handleInput(window);
//         currentState->update(deltaTime);

//         window.clear(sf::Color::Black);
//         currentState->render(window);
//         window.display();
//     }

//     return 0;
// }
