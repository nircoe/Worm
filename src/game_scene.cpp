#include "game_scene.hpp"
#include <datacoe/game_data.hpp>

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
        resetScoreText(gameManager);
        this->m_food.setActive(false);
        saveGame(gameManager);
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
                                                static_cast<std::size_t>(Consts::GAME_OVER_BUTTONS_ID[i])));
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

void GameScene::renderUI(const raylib::Camera2D& /*camera*/)
{
    if(m_isBeginning)
        m_startText.render();
    if(!m_gameOver)
        return;

    m_gameoverText.render();
    m_scoreText.render();
    m_highscoreText.render();

    for (auto &button : m_buttons)
        button.render();
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
    m_player.changeDifficulty(newDifficulty);
}

Enums::Difficulty GameScene::getDifficulty() const
{
    return m_difficulty;
}

void GameScene::initUI(const GameManager &gameManager)
{
    auto& font = gameManager.getFont();
    m_startText.init("Start Moving With The Arrow Buttons!", Colors::TEXT_COLOR, Consts::START_GAME_FONT_SIZE, 
        {0.0f, 0.0f, Consts::SCREEN_WIDTH, Consts::HALF_SCREEN.y}, &font);

    m_gameoverText.init("Game Over!", Colors::TEXT_COLOR, 50.0f, 
        {0.0f, 0.0f, Consts::SCREEN_WIDTH, 1.5f * Consts::HALF_SCREEN.y}, &font);


    for(std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        auto& rect = Consts::GAME_OVER_RECTS[i];
        m_buttons[i].init(Colors::BUTTON_BASE_COLOR, rect, WHITE, Consts::GAME_OVER_BUTTONS_TEXT[i], Consts::BUTTONS_FONT_SIZE, &font);
    }
}

raylib::Color GameScene::checkButton(GameManager &gameManager, const raylib::Color &hoverColor, const raylib::Color &clickedColor, std::size_t buttonId)
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
    for(auto& button : m_buttons)
    {
        button.setColor(Colors::BUTTON_BASE_COLOR);
    }
}

void GameScene::resetScoreText(GameManager &gameManager)
{
    m_score = m_player.getScore();
    std::string scoreText = "Your Score: " + std::to_string(m_score);
    m_scoreText.init(scoreText, Colors::TEXT_COLOR, 30.0f, 
        {0.0f, 90.0f, Consts::SCREEN_WIDTH, 1.5f * Consts::HALF_SCREEN.y}, &gameManager.getFont());    
}

void GameScene::saveGame(GameManager &gameManager)
{
    datacoe::GameData data = gameManager.getGamedata();
    auto highscores = data.getHighscores();
    int index;
    if (m_difficulty == Enums::Difficulty::Easy)
        index = 0;
    else if (m_difficulty == Enums::Difficulty::Medium)
        index = 1;
    else if (m_difficulty == Enums::Difficulty::Hard)
        index = 2;
    else
        index = 3;

    auto score = m_player.getScore();
    if (highscores[index] < score)
        highscores[index] = score;

    std::string highscoreText = "Your Highscore: " + std::to_string(highscores[index]);
    m_highscoreText.init(highscoreText, Colors::TEXT_COLOR, 30.0f, 
        {0.0f, 120.0f, Consts::SCREEN_WIDTH, 1.5f * Consts::HALF_SCREEN.y}, &gameManager.getFont());

    data.setHighscores(highscores);
    gameManager.saveGame(data);
}
