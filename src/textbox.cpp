#include "ui/textbox.hpp"
#include "auxiliary/colors.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"

UI::TextBox::TextBox(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition, 
    raylib::Color textColor, float fontSize, std::string text) : 
    m_color(color),
    m_rect(rect),
    m_textPosition(textPosition),
    m_textColor(textColor),
    m_fontSize(fontSize),
    m_text(text) { }

void UI::TextBox::init(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition, 
    raylib::Color textColor, float fontSize, std::string text)
{
    m_color = color;
    m_rect = rect;
    m_textPosition = textPosition;
    m_textColor = textColor;
    m_fontSize = fontSize;
    m_text = text;
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
            m_text = m_text.substr(0, len - 1);
            m_lastFrameDelete = m_framesCounter;
        }
    }

    m_framesCounter++;
}

void UI::TextBox::render(const raylib::Font &font, bool round, float spacing) const
{
    if(round)
        DrawRectangleRounded(m_rect, 1.0f, 8, m_color);
    else
        DrawRectangleRec(m_rect, m_color);
    std::string text = m_text;
    if (text.length() < Consts::MAX_INPUT_CHARS && (m_framesCounter / 20) % 2 == 0)
        text += "_";
    raylib::DrawTextEx(font, text, m_textPosition, m_fontSize, spacing, m_textColor);
}

void UI::TextBox::render(const raylib::Font &font, const raylib::Camera2D &camera, bool round, float spacing) const
{
    raylib::Rectangle rect = raylib::Rectangle(camera.GetWorldToScreen(m_rect.GetPosition()), {m_rect.width, m_rect.height});
    if (round)
        DrawRectangleRounded(rect, 1.0f, 8, m_color);
    else
        DrawRectangleRec(rect, m_color);
    std::string text = m_text;
    if (text.length() < Consts::MAX_INPUT_CHARS && (m_framesCounter / 20) % 2 == 0)
        text += "_";
    raylib::DrawTextEx(font, text, camera.GetWorldToScreen(m_textPosition), m_fontSize, spacing, m_textColor);
}

void UI::TextBox::setColor(const raylib::Color &newColor)
{
    m_color = newColor;
}

std::string UI::TextBox::getText() const
{
    return m_text;
}

bool UI::TextBox::isHovered(const raylib::Vector2 &mousePosition) const
{
    return CheckCollisionPointRec(mousePosition, m_rect);
}
