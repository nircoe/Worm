#pragma once

#include "raylib-cpp.hpp"

class Moveable
{
protected:

    float m_speed;
    raylib::Vector2 m_velocity;

public:

    Moveable();

    Moveable(float speed);

    ~Moveable() = default;

    float getSpeed();

    void setVelocity(raylib::Vector2 vel);

    const raylib::Vector2& getVelocity() const;
};