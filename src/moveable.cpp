#include "moveable.hpp"

Moveable::Moveable() : Moveable(0.0f) {}

Moveable::Moveable(float speed) : m_speed(speed) {}

float Moveable::getSpeed() { return this->m_speed * GetFrameTime(); }

void Moveable::setVelocity(raylib::Vector2 vel) { m_velocity = vel; }

const raylib::Vector2 &Moveable::getVelocity() const { return m_velocity; }
