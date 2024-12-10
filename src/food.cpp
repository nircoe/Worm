#include "food.hpp"

Food::Food(raylib::Vector2 position) : GameObject(position) { }

void Food::update() { }

void Food::render() const
{
    if(!this->isActive()) return;

    const raylib::Vector2 pos = getTransform().getPosition();
    const raylib::Vector2 foodSize = Utils::getFoodSize();
    DrawRectangleV(pos, foodSize, GREEN);
}

void Food::changePosition(const raylib::Vector2 newPosition)
{
    this->getTransform().setPosition(newPosition);
}
