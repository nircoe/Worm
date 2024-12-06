#pragma once

#include <vector>
#include "game_object.hpp"
#include "player.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"

class Scene 
{
public:
    Scene();

    ~Scene() = default;
    
    void update();
    void render();

private:
    Player m_player;
    Food m_food;
};
