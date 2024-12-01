#include "food.hpp"

Food::Food(raylib::Vector2 initialPosition)
    : GameObject(initialPosition) {}

void Food::Update()
{
    //Food Update logic
}

void Food::Render() const
{
    const raylib::Vector2 pos = getTransform().getPosition();
    DrawRectangle(pos.x, pos.y, m_width, m_height, GREEN);
}
