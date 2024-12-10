#include "scene.hpp"

Scene::Scene() : m_player(raylib::Vector2(), Consts::PLAYER_SPEED), m_food(Utils::getFoodSpawnPoint(Consts::INITIAL_PLAYER_BODY)) { }

void Scene::update() 
{
    //m_player.checkFoodCollision(m_food);

    m_player.update();
    m_food.update();
    // check collision between the worm and the foods
    // check collision between the head of the worm and the rest of the body
}

void Scene::render() 
{
    m_player.render();
    m_food.render();
}
