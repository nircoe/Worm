#include "ui/button.hpp"

UI::Button::Button(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition, 
    raylib::Color textColor, std::string text, float fontSize) :
    m_color(color), 
    m_rect(rect),
    m_textPosition(textPosition), 
    m_textColor(textColor), 
    m_text(text), 
    m_fontSize(fontSize) { }

void UI::Button::init(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition, 
    raylib::Color textColor, std::string text, float fontSize)
{
    m_color = color;
    m_rect = rect;
    m_textPosition = textPosition;
    m_textColor = textColor;
    m_text = text;
    m_fontSize = fontSize;
}

void UI::Button::render(const raylib::Font &font, float spacing) const
{
    DrawRectangleRec(m_rect, m_color);
    raylib::DrawTextEx(font, m_text.c_str(), m_textPosition, m_fontSize, spacing, m_textColor);
}

void UI::Button::setTextPosition(const raylib::Vector2& pos)
{
    m_textPosition = pos;
}

void UI::Button::setColor(const raylib::Color& newColor)
{
    m_color = newColor;
}

const bool UI::Button::isHovered(const raylib::Vector2 &mousePosition)
{
    return CheckCollisionPointRec(mousePosition, m_rect);
}
