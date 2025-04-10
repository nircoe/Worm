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
  const std::string &text = m_textBox.getText();
  if (button == Enums::NewGameButton::Continue && text.empty())
    return LIGHTGRAY;

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
  {
    gameManager.changeDifficulty(Enums::Difficulty::Easy);
    if (button == Enums::NewGameButton::Continue) // init datamanager with nickname
      gameManager.newGame(text);
    else if (button == Enums::NewGameButton::Guest) // init datamanager with guest mode
      gameManager.newGame();

    gameManager.activateScene(Enums::SceneName::Home_Scene);
    gameManager.deactivateScene(Enums::SceneName::New_Game_Scene);

    m_currentClickedButton = Enums::NewGameButton::None;
    return clickedColor;
  }

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && m_currentClickedButton == button)
    return clickedColor;

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    m_currentClickedButton = button;

  return hoverColor;
}

bool NewGameScene::checkEnterKey(GameManager &gameManager)
{
  auto text = m_textBox.getText();
  if (!IsKeyPressed(KEY_ENTER) || text.empty())
    return false;

  gameManager.changeDifficulty(Enums::Difficulty::Easy);
  gameManager.newGame(text);
  gameManager.activateScene(Enums::SceneName::Home_Scene);
  gameManager.deactivateScene(Enums::SceneName::New_Game_Scene);
  m_buttons[static_cast<int>(Enums::NewGameButton::Continue)].setColor(Colors::BUTTON_CLICKED_COLOR);

  return true;
}

void NewGameScene::update(GameManager &gameManager)
{
  resetButtonsColor();
  raylib::Vector2 mousePosition = GetMousePosition();

  if(checkEnterKey(gameManager))
    return;

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

void NewGameScene::renderUI(const raylib::Camera2D &camera)
{
  m_title.render(camera);
  m_subtitle.render(camera);

  for (auto &button : m_buttons)
    button.render(camera);

  m_textBox.render(camera, 1.0f, 8);
}

void NewGameScene::initUI(const GameManager &gameManager)
{
  auto &font = gameManager.getFont();
  m_title.init("Welcome!", Colors::TEXT_COLOR, 70.0f, 
    {0.0f, 0.0f, Consts::SCREEN_WIDTH, 350.0f}, &font);

  m_subtitle.init("Please choose a nickname or continue as guest", Colors::TEXT_COLOR, 20.0f, 
    {0.0f, 80.0f, Consts::SCREEN_HEIGHT, 350.0f}, &font);

  for (std::size_t i = 0; i < m_buttons.size(); ++i)
  {
    auto &rect = Consts::NEW_GAME_RECTS[i];
    m_buttons[i].init(Colors::BUTTON_BASE_COLOR, rect, WHITE, Consts::NEW_GAME_BUTTONS_TEXT[i], Consts::BUTTONS_FONT_SIZE, &font);
  }

  auto textBoxPosition = Consts::NEW_GAME_TEXT_BOX_RECT.GetPosition();
  auto textBoxSize = Consts::NEW_GAME_TEXT_BOX_RECT.GetSize();
  raylib::Vector2 textBoxTextPosition = Utils::centralizeTextEx(font, "TEXTBOX", 20, textBoxPosition, textBoxSize);
  textBoxTextPosition.x = textBoxPosition.x + (textBoxTextPosition.y - textBoxPosition.y);
  m_textBox.init(Colors::TEXT_BOX_COLOR, Consts::NEW_GAME_TEXT_BOX_RECT, textBoxTextPosition, Colors::TEXT_COLOR, 20, &font);
}
