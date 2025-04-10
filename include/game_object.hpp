#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "raylib-cpp.hpp"
#include "transform2d.hpp"

class GameObject 
{
    Transform2D m_transform;
    bool m_isActive;
    
public:
    GameObject() = default;
    GameObject(raylib::Vector2 initialPosition);
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void render() const = 0;

    void setActive(bool active);
    
    Transform2D& getTransform();
    const Transform2D& getTransform() const;
    bool isActive() const;
};
