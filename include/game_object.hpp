#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "raylib-cpp.hpp"
#include "transform2d.hpp"

class GameObject 
{
    static unsigned int s_idCounter; // static member for ID generation

    unsigned int m_id;
    Transform2D m_transform;
    bool m_isActive;
    
public:
    GameObject() = default;
    GameObject(raylib::Vector2 initialPosition);
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void render() const = 0;

#pragma region setters
    void setActive(bool active);
#pragma endregion
    
#pragma region getters
    unsigned int getId() const;
    Transform2D& getTransform();
    const Transform2D& getTransform() const;
    const bool isActive() const;
#pragma endregion
};
