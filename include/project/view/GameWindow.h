#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SFML/Graphics.hpp>

class GameWindow {
public:
    GameWindow();

    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text startText;
    sf::Text titleText;
    sf::Text quitText;
};

#endif // GAME_WINDOW_H
