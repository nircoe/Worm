#include "game_scene.hpp"

GameScene::GameScene(Enums::Difficulty difficulty) : m_player(raylib::Vector2(), Consts::PLAYER_SPEED, difficulty),
      m_food(Utils::getFoodSpawnPoint(Consts::INITIAL_PLAYER_BODY)),
      m_difficulty(difficulty),
      m_borders(Consts::BORDERS),
      m_gameOver(false) { }

void GameScene::update(SceneManager& sceneManager) 
{
    if(!this->m_gameOver)
    {
        if(m_player.checkFoodCollision(m_food))
        {
            m_player.handleFoodCollision();
            m_food.changePosition(Utils::getFoodSpawnPoint(m_player.getPlayerBody()));
        }

        m_player.update();
        m_food.update();
    }

    if(!this->m_gameOver && !m_player.isActive())
    {
        this->m_gameOver = true;
        this->m_food.setActive(false);
    }

    if(this->m_gameOver)
    {
        // logic for buttons
    }
}

void GameScene::render() 
{
    m_player.render();
    m_food.render();
    if(m_difficulty == Enums::Difficulty::Hard || m_difficulty == Enums::Difficulty::Impossible)
    {
        for (auto &&rec : m_borders)
        {
            DrawRectangleRec(rec, Colors::BORDER_COLOR);
        }
    }
}

void GameScene::renderUI(const raylib::Font& font)
{
    if(m_gameOver) 
        gameOver(font);
}

const raylib::Vector2 GameScene::getPlayerHeadPosition() const
{
    return this->m_player.getHeadPosition();
}

void GameScene::changeDifficulty(Enums::Difficulty newDifficulty)
{
    m_difficulty = newDifficulty;
    m_player.changeDifficulty(newDifficulty);
}

const Enums::Difficulty GameScene::getDifficulty() const
{
    return m_difficulty;
}

void GameScene::gameOver(const raylib::Font& font) const
{
    // Draw text "GAME OVER!"
    float textHeight = Consts::SCREEN_HEIGHT;
    textHeight *= (m_player.getHeadPosition().y > Consts::HALF_SCREEN.y) ? 0.25f : 0.75f;
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

    // TODO: add buttons
}
