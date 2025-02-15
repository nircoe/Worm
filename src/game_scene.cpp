#include "game_scene.hpp"

GameScene::GameScene(Enums::Difficulty difficulty) : m_player(raylib::Vector2(), Consts::PLAYER_SPEED, difficulty),
      m_food(Utils::getFoodSpawnPoint(Consts::INITIAL_PLAYER_BODY)),
      m_difficulty(difficulty),
      m_isBeginning(true),
      m_gameOver(false) { }

void GameScene::update(GameManager& gameManager) 
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
        resetScoreText(gameManager.getFont());
        this->m_food.setActive(false);
    }

    if(this->m_gameOver)
    {
        resetButtonsColor();

        raylib::Vector2 mousePosition = GetMousePosition();

        for(std::size_t i = 0; i < m_buttons.size(); ++i)
        {
            if(m_buttons[i].isHovered(mousePosition))
            {
                m_buttons[i].setColor(checkButton(gameManager, Colors::BUTTON_HOVER_COLOR, 
                Colors::BUTTON_CLICKED_COLOR, 
                static_cast<int>(Consts::GAME_OVER_BUTTONS_ID[i])));
                break;
            }
        }
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
        DrawTextEx(font, m_startText, m_startTextPosition, Consts::START_GAME_FONT_SIZE, 1, Colors::TEXT_COLOR);
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
    m_borderColor = Colors::BORDER_COLOR;
    //m_borderColor = (m_difficulty == Enums::Difficulty::Impossible) ? Colors::IMPOSSIBLE_HOVER_COLOR : Colors::HARD_HOVER_COLOR;
    m_player.changeDifficulty(newDifficulty);
}

const Enums::Difficulty GameScene::getDifficulty() const
{
    return m_difficulty;
}

void GameScene::initUI(const raylib::Font &font)
{
    m_startTextPosition = Utils::centralizeTextEx(font, m_startText.c_str(), Consts::START_GAME_FONT_SIZE, raylib::Vector2::Zero(), 
        { Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT / 2});

    m_gameOverTextPosition = Utils::centralizeTextEx(font, Consts::GAME_OVER_TEXT.c_str(), 
        Consts::GAME_OVER_FONT_SIZE, raylib::Vector2::Zero(), { Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT * (2.0f / 3.0f) });
    m_gameOverTextPosition.y -= Consts::GAME_OVER_TO_SCORE_GAP;


    for(std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        auto& rect = Consts::GAME_OVER_RECTS[i];
        m_buttons[i].init(Colors::BUTTON_BASE_COLOR, 
        rect, 
        Utils::centralizeTextEx(font, Consts::GAME_OVER_BUTTONS_TEXT[i].c_str(), Consts::BUTTONS_FONT_SIZE, 
                                {rect.x, rect.y}, {rect.width, rect.height}),
        WHITE,
        Consts::GAME_OVER_BUTTONS_TEXT[i], 
        Consts::BUTTONS_FONT_SIZE);
    }
}

raylib::Color GameScene::checkButton(GameManager &gameManager, const raylib::Color &hoverColor, const raylib::Color &clickedColor, int buttonId)
{
    auto button = static_cast<Enums::GameButton>(buttonId);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
    {
        if(button == Enums::GameButton::Home_Screen)
        {
            gameManager.activateScene(Enums::SceneName::Home_Scene);
            restart(); // reset for next play
            gameManager.deactivateScene(Enums::SceneName::Game_Scene);
        }
        else if(button == Enums::GameButton::Play_Again) 
        {
            restart();
        }
        else if(button == Enums::GameButton::Exit)
            gameManager.closeGame();
        
        m_currentClickedButton = Enums::GameButton::None;
        return clickedColor;
    } 
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
    {
        return clickedColor;
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        m_currentClickedButton = button;
    }
        
    return hoverColor;
}

void GameScene::gameOver(const raylib::Font &font) const
{
    // Draw text "GAME OVER!"
    float textHeight = Consts::SCREEN_HEIGHT;
    textHeight *= (m_player.getHeadPosition().y > Consts::HALF_SCREEN.y) ? 0.25f : 0.75f;
    raylib::DrawTextEx(font, Consts::GAME_OVER_TEXT.c_str(), m_gameOverTextPosition, 
        Consts::GAME_OVER_FONT_SIZE, 1, Colors::TEXT_COLOR);

    raylib::DrawTextEx(font, m_scoreText.c_str(), m_scoreTextPosition, 
        Consts::GAME_OVER_FONT_SIZE, 1, Colors::TEXT_COLOR);

    for(std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].render(font);
    }
}

void GameScene::restart()
{
    m_player = Player(raylib::Vector2::Zero(), Consts::PLAYER_SPEED, m_difficulty);
    m_food = Food(Utils::getFoodSpawnPoint(Consts::INITIAL_PLAYER_BODY));
    m_isBeginning = true;
    m_gameOver = false;

    resetButtonsColor();
}

void GameScene::resetButtonsColor()
{
    for(std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].setColor(Colors::BUTTON_BASE_COLOR);
    }
}

void GameScene::resetScoreText(const raylib::Font& font)
{
    m_score = m_player.getScore();
    m_scoreText = "Your Score: " + std::to_string(m_score);
    m_scoreTextPosition = Utils::centralizeTextEx(font, m_scoreText.c_str(), Consts::GAME_OVER_FONT_SIZE, 
        raylib::Vector2::Zero(), Consts::SCREEN_SIZE);
    m_scoreTextPosition.y = m_gameOverTextPosition.y + (Consts::GAME_OVER_TO_SCORE_GAP * 2);
}
