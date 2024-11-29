#include "scene.hpp"

Scene::Scene() 
{
    m_player = Player(raylib::Vector2(), 50.0f);
    m_foods = std::vector<Food>();
}

void Scene::Update() 
{
    // check collision between the worm and the foods
    // check collision between the head of the worm and the rest of the body
}

void Scene::Render() 
{
    m_player.Render();

    for(auto& food : m_foods)
    {
        food.Render();
    }
}
