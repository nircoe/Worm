#include "game_scene.hpp"

GameScene::GameScene(Enums::Difficulty difficulty) : m_player(raylib::Vector2(), Consts::PLAYER_SPEED, difficulty),
      m_food(Utils::getFoodSpawnPoint(Consts::INITIAL_PLAYER_BODY)),
      m_difficulty(difficulty),
      m_isBeginning(true),
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

        if(m_isBeginning)
            m_isBeginning = m_player.isBeginning();
    }

    if(!this->m_gameOver && !m_player.isActive())
    {
        this->m_gameOver = true;
        this->calculateGameOverTextPositions();
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

    if(m_difficulty == Enums::Difficulty::Hard || m_difficulty == Enums::Difficulty::Impossible)
    {
        for (auto &&rec : m_borders)
        {
            DrawRectangleRec(rec, m_borderColor);
        }
    }

    if(m_isBeginning) return;

    m_food.render();
}

void GameScene::renderUI(const raylib::Font& font)
{
    if(m_isBeginning)
        DrawTextEx(font, m_startText, m_startTextPosition, Consts::START_GAME_FONT_SIZE, 1, BLACK);
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
    m_borders = (m_difficulty == Enums::Difficulty::Impossible) ? Consts::IMPOSSIBLE_BORDERS : Consts::BORDERS;
    m_borderColor = (m_difficulty == Enums::Difficulty::Impossible) ? Colors::IMPOSSIBLE_HOVER_COLOR : Colors::HARD_HOVER_COLOR;
    m_player.changeDifficulty(newDifficulty);
}

const Enums::Difficulty GameScene::getDifficulty() const
{
    return m_difficulty;
}

void GameScene::calculateTextsPositions(const raylib::Font &font)
{
    m_font = &font;

    m_startTextPosition = Utils::centralizeTextEx(font, m_startText.c_str(), Consts::START_GAME_FONT_SIZE, raylib::Vector2::Zero(), 
        { Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT / 2});
}

void GameScene::calculateGameOverTextPositions()
{
    m_gameOverTextPosition = Utils::centralizeTextEx(*m_font, Consts::GAME_OVER_TEXT.c_str(), 
        Consts::GAME_OVER_FONT_SIZE, raylib::Vector2::Zero(), Consts::SCREEN_SIZE);
    m_gameOverTextPosition.y -= Consts::GAME_OVER_TO_SCORE_GAP;

    m_scoreText = "Your Score: " + std::to_string(this->m_player.getScore());
    m_scoreTextPosition = Utils::centralizeTextEx(*m_font, m_scoreText.c_str(), Consts::GAME_OVER_FONT_SIZE, 
        raylib::Vector2::Zero(), Consts::SCREEN_SIZE);
    m_scoreTextPosition.y = m_gameOverTextPosition.y + (Consts::GAME_OVER_TO_SCORE_GAP * 2);
}

void GameScene::gameOver(const raylib::Font &font) const
{
    // Draw text "GAME OVER!"
    float textHeight = Consts::SCREEN_HEIGHT;
    textHeight *= (m_player.getHeadPosition().y > Consts::HALF_SCREEN.y) ? 0.25f : 0.75f;
    raylib::DrawTextEx(font, Consts::GAME_OVER_TEXT.c_str(), const_cast<raylib::Vector2&>(m_gameOverTextPosition), 
        Consts::GAME_OVER_FONT_SIZE, 1, BLACK);

    raylib::DrawTextEx(font, m_scoreText.c_str(), const_cast<raylib::Vector2&>(m_scoreTextPosition), 
        Consts::GAME_OVER_FONT_SIZE, 1, BLACK);

    // TODO: add buttons
}
