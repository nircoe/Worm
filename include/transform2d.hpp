#pragma once

#include "raylib-cpp.hpp"

class Transform2D
{
protected:

    float m_posX;
    float m_posY;

public:

    Transform2D();

    Transform2D(float posX, float posY);

    Transform2D(raylib::Vector2 pos);

    ~Transform2D() = default;

    void setPosition(const raylib::Vector2 newPosition);

    raylib::Vector2 getPosition();

    const raylib::Vector2 getPosition() const;
};