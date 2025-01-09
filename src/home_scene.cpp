#include "home_scene.hpp"
#include "scene_manager.hpp"

HomeScene::HomeScene() : m_player(raylib::Vector2::Zero(), Consts::PLAYER_SPEED, m_difficulty) 
{ 
    //  0  ,  1  ,  2  ,    3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    resetButtonsColor();
}

void HomeScene::update(SceneManager& sceneManager)
{
    m_player.updateForHomeScene();

    resetButtonsColor();
    raylib::Vector2 mousePosition = GetMousePosition();
    checkButtons(sceneManager, mousePosition);
}

void HomeScene::render()
{
    m_player.render();
}

void HomeScene::renderUI()
{
    DrawTextEx(Consts::FONT, m_titleText, m_titlePosition, Consts::TITLE_FONT_SIZE, 0, BLACK);
    for(std::size_t i = 0; i < m_arraysSize; ++i)
    {
        Utils::drawButton(Consts::FONT, Consts::HOME_BUTTONS_RECTS[i], Consts::HOME_BUTTONS_TEXTS[i], m_buttonsColors[i], Consts::BUTTONS_FONT_SIZE, WHITE);
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
            sceneManager.setSceneActive(Enums::SceneName::Game_Scene);

        }
        if(button != Enums::HomeButton::Play && button != Enums::HomeButton::Exit) 
            checkDifficultyButton();
        
        m_currentClickedButton = Enums::HomeButton::None;
        return clickedColor;
    } 

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        m_currentClickedButton = button;

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
