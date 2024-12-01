#pragma once

#include <unordered_map>
#include <memory>
#include "game_object.hpp"
#include "player.hpp"
#include "food.hpp"

class Scene 
{
public:
    Scene();

    ~Scene() = default;
    
    void Update();
    void Render();

private:
    // std::unordered_map<unsigned int, std::shared_ptr<GameObject>> m_gameObjects;
    Player m_player;
    std::vector<Food> m_foods;
};
