#include "home_scene.hpp"
#include "game_manager.hpp"

HomeScene::HomeScene() : 
    m_player(raylib::Vector2::Zero(), 
    Consts::PLAYER_SPEED, 
    m_difficulty) { }

void HomeScene::update(GameManager& gameManager)
{
    if(m_isLoading)
    {
        m_player.loading(gameManager);
        if(m_player.isFinishLoading())
        {
            m_isLoading = false;
            m_player.resetBody();
            gameManager.changeDifficulty(m_difficulty);
            gameManager.resetCamera();
            gameManager.activateScene(Enums::SceneName::Game_Scene);
            gameManager.deactivateScene(Enums::SceneName::Home_Scene);
        }
        return;
    }

    m_player.update();
    resetButtonsColor();
    raylib::Vector2 mousePosition = GetMousePosition();

    for(std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        if(m_buttons[i].isHovered(mousePosition))
        {
            m_buttons[i].setColor(checkButton(gameManager, Consts::HOME_BUTTONS_HOVER_COLORS[i], 
            Consts::HOME_BUTTONS_CLICKED_COLORS[i], 
            static_cast<int>(Consts::HOME_BUTTONS_IDS[i])));
            break;
        }
    }
}

void HomeScene::render()
{
    m_player.render();
}

void HomeScene::renderUI(const raylib::Font& font, const raylib::Camera2D& camera)
{
    raylib::DrawTextEx(font, m_titleText, camera.GetWorldToScreen(m_titlePosition), Consts::TITLE_FONT_SIZE, 1, Colors::TEXT_COLOR);
    for(auto& button : m_buttons)
    {
        button.render(font, camera);
    }
}

Enums::Difficulty HomeScene::getDifficulty() const
{
    return m_difficulty;
}

void HomeScene::initUI(const raylib::Font &font)
{
    m_titlePosition = Utils::centralizeTextEx(font, m_titleText.c_str(), 
                                            Consts::TITLE_FONT_SIZE, raylib::Vector2::Zero(), 
                                            { Consts::SCREEN_WIDTH, 300.0f});

    for(std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        auto& rect = Consts::HOME_BUTTONS_RECTS[i];
        m_buttons[i].init(Colors::BUTTON_BASE_COLOR, 
            rect,
            Utils::centralizeTextEx(font, Consts::HOME_BUTTONS_TEXTS[i].c_str(), Consts::BUTTONS_FONT_SIZE, 
                                        { rect.x, rect.y }, { rect.width, rect.height }),
            WHITE,
            Consts::HOME_BUTTONS_TEXTS[i],
            Consts::BUTTONS_FONT_SIZE);
    }

    resetDifficultyButtonsColor();
}

void HomeScene::resetButtonsColor()
{
    for(auto& button : m_buttons)
    {
        button.setColor(Colors::BUTTON_BASE_COLOR);
    }
    resetDifficultyButtonsColor();
}

void HomeScene::resetDifficultyButtonsColor()
{
    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    for(std::size_t i = 2; i < m_buttons.size(); ++i)
    {
        if(m_difficulty == Consts::DIFFICULTIES_ARRAY[i - 2])
        {
            m_buttons[i].setColor(Consts::HOME_BUTTONS_CLICKED_COLORS[i]);
            return;
        }
    }
}

void HomeScene::checkDifficultyButton()
{
    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    for(std::size_t i = 2; i < m_buttons.size(); ++i)
    {
        if(m_currentClickedButton == Consts::HOME_BUTTONS_IDS[i])
        {
            m_difficulty = Consts::DIFFICULTIES_ARRAY[i - 2];
            return;
        }
    }
}

raylib::Color HomeScene::checkButton(GameManager& gameManager, const raylib::Color &hoverColor, 
    const raylib::Color& clickedColor, int buttonId)
{
    auto button = static_cast<Enums::HomeButton>(buttonId);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
    {
        if(button == Enums::HomeButton::Play)
        {
            gameManager.changeDifficulty(Enums::Difficulty::Hard);
            m_isLoading = true;
        }
        else if(button == Enums::HomeButton::Exit)
            gameManager.closeGame();
        else if(button != Enums::HomeButton::Play && button != Enums::HomeButton::Exit) 
        {
            checkDifficultyButton();
            gameManager.changeDifficulty(m_difficulty);
        }
        
        m_currentClickedButton = Enums::HomeButton::None;
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
