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

    if(!this->m_gameOver && !m_player.isActive())
    {
        this->m_gameOver = true;
        this->m_food.setActive(false);
    }

    if(this->m_gameOver)
        this->gameOver();
    // check collision between the worm and the foods
    // check collision between the head of the worm and the rest of the body
}

void Scene::render() 
{
    m_player.render();
    m_food.render();
}

const raylib::Vector2 Scene::getPlayerHeadPosition() const
{
    return this->m_player.getHeadPosition();
}

void Scene::gameOver() const
{
    // Draw text "GAME OVER!"
    float textHeight = Consts::SCREEN_HEIGHT;
    textHeight *= (m_player.getHeadPosition().y > Consts::HALF_SCREEN_HEIGHT) ? 0.25f : 0.75f;
    DrawText(Consts::GAME_OVER_TEXT.c_str(), 
                GAME_OVER_TEXT_WIDTH, 
                (int)textHeight, 
                Consts::GAME_OVER_FONT_SIZE, BLACK);

    // Draw text "YOUR SCORE: ___"
    std::string scoreText = "YOUR SCORE: " + std::to_string(this->m_player.getScore());
    DrawText(scoreText.c_str(), 
                Utils::centerlizeTextX(scoreText.c_str(), 
                Consts::GAME_OVER_FONT_SIZE), 
                (int)textHeight + 100, 
                Consts::GAME_OVER_FONT_SIZE, BLACK);
}
