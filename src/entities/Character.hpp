#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Character : public sf::Drawable
{
public:
    Character(const std::string& name, int health, const std::vector<std::string>& weaknesses,
              const std::vector<std::string>& strengths, const sf::Vector2f& size, const sf::Color& color,
              const sf::Vector2f& position);

    // Getters
    std::string getName() const;
    int getHealth() const;
    const std::vector<std::string>& getWeaknesses() const;
    const std::vector<std::string>& getStrengths() const;
    sf::Vector2f getSize() const;
    sf::Color getColor() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void move(const sf::Vector2f& offset);
    

    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::string name;
    int health;
    std::vector<std::string> weaknesses;
    std::vector<std::string> strengths;
    sf::Vector2f size;
    sf::Color color;
    sf::Vector2f position;
    sf::RectangleShape shape;
};

#endif // CHARACTER_HPP
