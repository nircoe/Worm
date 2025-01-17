#include "home_scene.hpp"
#include "scene_manager.hpp"

HomeScene::HomeScene() : 
    m_player(raylib::Vector2::Zero(), 
    Consts::PLAYER_SPEED, 
    m_difficulty) 
{ 
    //  0  ,  1  ,  2  ,    3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible

    resetButtonsColor();
}

void HomeScene::update(SceneManager& sceneManager)
{
    m_player.update();

    resetButtonsColor();
    raylib::Vector2 mousePosition = GetMousePosition();
    checkButtons(sceneManager, mousePosition);
}

void HomeScene::render()
{
    m_player.render();
}

void HomeScene::renderUI(const raylib::Font& font)
{
    DrawTextEx(font, m_titleText, m_titlePosition, Consts::TITLE_FONT_SIZE, 1, BLACK);
    for(std::size_t i = 0; i < m_arraysSize; ++i)
    {
        Utils::drawButton(font, Consts::HOME_BUTTONS_RECTS[i], Consts::HOME_BUTTONS_TEXTS[i], 
            m_buttonsTextPosition[i], m_buttonsColors[i], Consts::BUTTONS_FONT_SIZE, WHITE);
    }
}

Enums::Difficulty HomeScene::getDifficulty() const
{
    return m_difficulty;
}

void HomeScene::calculateTextsPositions(const raylib::Font &font)
{
    m_titlePosition = Utils::centralizeTextEx(font, m_titleText.c_str(), 
                                            Consts::TITLE_FONT_SIZE, raylib::Vector2::Zero(), 
                                            { Consts::SCREEN_WIDTH, 200.0f});

    for(std::size_t i = 0; i < 6; ++i)
    {
        auto& rect = Consts::HOME_BUTTONS_RECTS[i];
        m_buttonsTextPosition[i] = Utils::centralizeTextEx(font, Consts::HOME_BUTTONS_TEXTS[i].c_str(), Consts::BUTTONS_FONT_SIZE, 
                                        { rect.x, rect.y }, { rect.width, rect.height });
    }
}

void HomeScene::resetButtonsColor()
{
    m_buttonsColors = Consts::HOME_BUTTONS_BASE_COLORS;
    resetDifficultyButtonsColor();
    
}

void HomeScene::resetDifficultyButtonsColor()
{
    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    for(std::size_t i = 2; i < m_arraysSize; ++i)
    {
        if(m_difficulty == Consts::DIFFICULTIES_ARRAY[i - 2])
        {
            m_buttonsColors[i] = Consts::HOME_BUTTONS_CLICKED_COLORS[i];
            return;
        }
    }
}

void HomeScene::checkDifficultyButton()
{
    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    for(std::size_t i = 2; i < m_arraysSize; ++i)
    {
        if(m_currentClickedButton == Consts::HOME_BUTTONS_IDS[i])
        {
            m_difficulty = Consts::DIFFICULTIES_ARRAY[i - 2];
            return;
        }
    }
}

raylib::Color HomeScene::checkButton(SceneManager& sceneManager, const raylib::Color &hoverColor, 
    const raylib::Color& clickedColor, Enums::HomeButton button)
{
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
    {
        if(button == Enums::HomeButton::Play)
        {
            sceneManager.activateScene(Enums::SceneName::Game_Scene);
            sceneManager.deactivateScene(Enums::SceneName::Home_Scene);
        }
        else if(button == Enums::HomeButton::Exit)
            sceneManager.closeGame();
        else if(button != Enums::HomeButton::Play && button != Enums::HomeButton::Exit) 
        {
            checkDifficultyButton();
            sceneManager.changeDifficulty(m_difficulty);
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

void HomeScene::checkButtons(SceneManager& sceneManager, const raylib::Vector2& mousePosition)
{
    for(std::size_t i = 0; i < m_arraysSize; ++i)
    {
        if(checkButtonHover(mousePosition, Consts::HOME_BUTTONS_RECTS[i]))
        {
            m_buttonsColors[i] = checkButton(sceneManager, Consts::HOME_BUTTONS_HOVER_COLORS[i], 
                                                Consts::HOME_BUTTONS_CLICKED_COLORS[i], 
                                                Consts::HOME_BUTTONS_IDS[i]);
            return;
        }
    }
}

const bool HomeScene::checkButtonHover(const raylib::Vector2 &mousePosition, const raylib::Rectangle &rect)
{
    return CheckCollisionPointRec(mousePosition, rect);
}
