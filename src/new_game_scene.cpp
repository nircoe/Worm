#include "new_game_scene.hpp"
#include "game_manager.hpp"

void NewGameScene::resetButtonsColor()
{
  if (m_textBox.getText().length() == 0)
    m_buttons[0].setColor(LIGHTGRAY);
  else
    m_buttons[0].setColor(Colors::BUTTON_BASE_COLOR);
  m_buttons[1].setColor(Colors::BUTTON_BASE_COLOR);
}

raylib::Color NewGameScene::checkButton(GameManager &gameManager, const raylib::Color &hoverColor, const raylib::Color &clickedColor, int buttonId)
{
  auto button = static_cast<Enums::NewGameButton>(buttonId);
  if (button == Enums::NewGameButton::Continue && m_textBox.getText().length() == 0)
    return LIGHTGRAY;

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
  {
    gameManager.changeDifficulty(Enums::Difficulty::Easy);
    if (button == Enums::NewGameButton::Continue)
    {
      // init datamanager with nickname
      gameManager.newGame(m_textBox.getText());
    }
    else if (button == Enums::NewGameButton::Guest)
    {
      // init datamanager with guest mode
      gameManager.newGame();
    }
    gameManager.activateScene(Enums::SceneName::Home_Scene);
    gameManager.deactivateScene(Enums::SceneName::New_Game_Scene);

    m_currentClickedButton = Enums::NewGameButton::None;
    return clickedColor;
  }

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
  {
    return clickedColor;
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    m_currentClickedButton = button;
  }

  return hoverColor;
}

NewGameScene::NewGameScene() { }

void NewGameScene::update(GameManager &gameManager)
{
  resetButtonsColor();
  raylib::Vector2 mousePosition = GetMousePosition();

  for (std::size_t i = 0; i < m_buttons.size(); ++i)
  {
    if (m_buttons[i].isHovered(mousePosition))
    {
      m_buttons[i].setColor(checkButton(gameManager, Colors::BUTTON_HOVER_COLOR,
                                        Colors::BUTTON_CLICKED_COLOR,
                                        static_cast<int>(Consts::NEW_GAME_BUTTONS_ID[i])));
      break;
    }
  }

  m_textBox.update();
}

void NewGameScene::render() {}

void NewGameScene::renderUI(const raylib::Font &font, const raylib::Camera2D &camera)
{
  raylib::DrawTextEx(font, m_titleText, camera.GetWorldToScreen(m_titlePosition), 70, 1, Colors::TEXT_COLOR);
  raylib::DrawTextEx(font, m_subtitleText, camera.GetWorldToScreen(m_subtitlePosition), 20, 1, Colors::TEXT_COLOR);

  for (auto &button : m_buttons)
  {
    button.render(font, camera);
  }

  m_textBox.render(font, camera);
}

void NewGameScene::initUI(const GameManager &gameManager)
{
  auto &font = gameManager.getFont();
  m_title.init("Welcome!", Colors::TEXT_COLOR, 70.0f, 
    {0.0f, 0.0f, Consts::SCREEN_WIDTH, 350.0f}, &font);
  m_titlePosition = Utils::centralizeTextEx(font, m_titleText.c_str(),
                                            70, raylib::Vector2::Zero(),
                                            {Consts::SCREEN_WIDTH, 350.0f});

  m_subtitle.init("Please choose a nickname or continue as guest", Colors::TEXT_COLOR, 20.0f, 
    {0.0f, 80.0f, Consts::SCREEN_HEIGHT, 350.0f}, &font);
  m_subtitlePosition = Utils::centralizeTextEx(font, m_subtitleText.c_str(),
                                               20, raylib::Vector2::Zero(),
                                               {Consts::SCREEN_WIDTH, 350.0f});
  m_subtitlePosition.y = m_titlePosition.y + 80.0f;

  for (std::size_t i = 0; i < m_buttons.size(); ++i)
  {
    auto &rect = Consts::NEW_GAME_RECTS[i];
    m_buttons[i].init(
        Colors::BUTTON_BASE_COLOR, rect,
        Utils::centralizeTextEx(font, Consts::NEW_GAME_BUTTONS_TEXT[i].c_str(),
                                Consts::BUTTONS_FONT_SIZE, {rect.x, rect.y},
                                {rect.width, rect.height}),
        WHITE, Consts::NEW_GAME_BUTTONS_TEXT[i], Consts::BUTTONS_FONT_SIZE);
  }

  auto textBoxPosition = Consts::NEW_GAME_TEXT_BOX_RECT.GetPosition();
  auto textBoxSize = Consts::NEW_GAME_TEXT_BOX_RECT.GetSize();
  raylib::Vector2 textBoxTextPosition = Utils::centralizeTextEx(font, "TEXTBOX", 20, textBoxPosition, textBoxSize);
  textBoxTextPosition.x = textBoxPosition.x + (textBoxTextPosition.y - textBoxPosition.y);
  m_textBox.init(Colors::TEXT_BOX_COLOR, Consts::NEW_GAME_TEXT_BOX_RECT, textBoxTextPosition, Colors::TEXT_COLOR, 20);
}
