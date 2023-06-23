#include "Character.hpp"

Character::Character(const std::string& name, int health, const std::vector<std::string>& weaknesses,
                     const std::vector<std::string>& strengths, const sf::Vector2f& size, const sf::Color& color,
                     const sf::Vector2f& position)
    : name(name), health(health), weaknesses(weaknesses), strengths(strengths),
      size(size), color(color), position(position), shape(size)
{
    shape.setFillColor(color);
    shape.setPosition(position);
}

std::string Character::getName() const
{
    return name;
}

int Character::getHealth() const
{
    return health;
}

const std::vector<std::string>& Character::getWeaknesses() const
{
    return weaknesses;
}

const std::vector<std::string>& Character::getStrengths() const
{
    return strengths;
}

sf::Vector2f Character::getSize() const
{
    return size;
}

sf::Color Character::getColor() const
{
    return color;
}

sf::Vector2f Character::getPosition() const
{
    return position;
}

sf::FloatRect Character::getBounds() const
{
    return shape.getGlobalBounds();
}

void Character::move(const sf::Vector2f& offset)
{
    position += offset;
    shape.setPosition(position);
}

void Character::setPosition(const sf::Vector2f& position)
{
        
    this->position = position;
    shape.setPosition(position);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}