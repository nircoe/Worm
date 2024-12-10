#pragma once

#include "game_object.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include <vector>

class Food : public GameObject {
public:
    Food(raylib::Vector2 position);
    
    virtual ~Food() override = default;

    virtual void update() override;

    virtual void render() const override;

    void changePosition(const raylib::Vector2 newPosition);

private:
};
