#include "scene.hpp"

Scene::Scene() : m_player(raylib::Vector2(), Consts::PLAYER_SPEED), 
                    m_food(Utils::getFoodSpawnPoint(Consts::INITIAL_PLAYER_BODY)),
                    m_gameOver(false) { }

void Scene::update() 
{
    if(!this->m_gameOver)
    {
        //m_player.checkFoodCollision(m_food);
        
        m_player.update();
        m_food.update();
    }

    if(!m_player.isActive())
    {
        this->m_gameOver = true;
    }
    // check collision between the worm and the foods
    // check collision between the head of the worm and the rest of the body
}

void Scene::render() 
{
    m_player.render();
    m_food.render();
}

void Scene::gameOver() const
{
    // Draw text "GAME OVER!"
    // Draw text "You've Got ___ Points!"
}
