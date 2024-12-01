#pragma once

#include "game_object.hpp"

class Food : public GameObject {
public:
    Food(raylib::Vector2 initialPosition);
    
    virtual ~Food() override = default;

    virtual void Update() override;

    virtual void Render() const override;

private:

    int m_width;
    int m_height;
};
