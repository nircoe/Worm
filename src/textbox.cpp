#include "ui/textbox.hpp"
#include "auxiliary/colors.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"

UI::TextBox::TextBox(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition,
    raylib::Color textColor, float fontSize, const raylib::Font *font, std::string text) : 
    m_color(color),
    m_rect(rect),
    m_text(text, textPosition, textColor, fontSize, font) {}

void UI::TextBox::init(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition,
    raylib::Color textColor, float fontSize, const raylib::Font *font, std::string text)
{
    m_color = color;
    m_rect = rect;
    m_text.init(text, textPosition, textColor, fontSize, font);
}

void UI::TextBox::update()
{
    int key = GetCharPressed();
    while (key > 0)
    {
        if ((32 <= key) && (key <= 125) && (m_text.length() < Consts::MAX_INPUT_CHARS))
        {
            m_text += (char)key;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyDown(KEY_BACKSPACE))
    {
        auto len = m_text.length();
        if (len > 0 && m_framesCounter - m_lastFrameDelete >= 5)
        {
            --m_text;
            m_lastFrameDelete = m_framesCounter;
        }
    }

    m_framesCounter++;
}

void UI::TextBox::render()
{
    DrawRectangleRec(m_rect, m_color);
    renderText();
}

void UI::TextBox::render(float roundness, int segments)
{
    DrawRectangleRounded(m_rect, roundness, segments, m_color);
    renderText();
}

void UI::TextBox::render(const raylib::Camera2D &camera)
{
    raylib::Rectangle rect = getRectWorldToScreen(camera);
    DrawRectangleRec(rect, m_color);
    renderText(&camera);
}

void UI::TextBox::render(const raylib::Camera2D &camera, float roundness, int segments)
{
    raylib::Rectangle rect = getRectWorldToScreen(camera);
    DrawRectangleRounded(rect, roundness, segments, m_color);
    renderText(&camera);
}

const raylib::Rectangle UI::TextBox::getRectWorldToScreen(const raylib::Camera2D &camera)
{
    return raylib::Rectangle(camera.GetWorldToScreen(m_rect.GetPosition()), {m_rect.width, m_rect.height});
}

void UI::TextBox::renderText(const raylib::Camera2D *camera)
{
    bool addition = false;
    if (m_text.length() < Consts::MAX_INPUT_CHARS && (m_framesCounter / 20) % 2 == 0)
    {
        m_text += "_";
        addition = true;
    }

    if(camera)
        m_text.render(*camera);
    else
        m_text.render();

    if (addition)
        --m_text;
}

void UI::TextBox::setColor(const raylib::Color &newColor)
{
    m_color = newColor;
}

std::string UI::TextBox::getText() const
{
    return m_text.getText();
}

bool UI::TextBox::isHovered(const raylib::Vector2 &mousePosition) const
{
    return CheckCollisionPointRec(mousePosition, m_rect);
}
