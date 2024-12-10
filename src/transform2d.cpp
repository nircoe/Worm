#include "transform2d.hpp"

Transform2D::Transform2D() : m_posX(0), m_posY(0) {}

Transform2D::Transform2D(float posX, float posY) : m_posX(posX), m_posY(posY) {}

Transform2D::Transform2D(raylib::Vector2 pos) : m_posX(pos.x), m_posY(pos.y) {}

void Transform2D::setPosition(const raylib::Vector2 newPosition) { m_posX = newPosition.x; m_posY = newPosition.y; }

raylib::Vector2 Transform2D::getPosition() { return raylib::Vector2(this->m_posX, this->m_posY); }

const raylib::Vector2 Transform2D::getPosition() const { return raylib::Vector2(this->m_posX, this->m_posY); }
