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
    DrawRectangleRounded(m_rect, 0.2f, 16, m_color);
    raylib::DrawTextEx(font, m_text, m_textPosition, m_fontSize, spacing, m_textColor);
}

void UI::Button::render(const raylib::Font &font, const raylib::Camera2D& camera, float spacing) const
{
    raylib::Rectangle rect = raylib::Rectangle(camera.GetWorldToScreen(m_rect.GetPosition()), { m_rect.width, m_rect.height });
    DrawRectangleRounded(rect, 0.2f, 16, m_color);
    raylib::DrawTextEx(font, m_text, camera.GetWorldToScreen(m_textPosition), m_fontSize, spacing, m_textColor);
}

void UI::Button::setTextPosition(const raylib::Vector2& pos)
{
    m_textPosition = pos;
}

void UI::Button::setColor(const raylib::Color& newColor)
{
    m_color = newColor;
}

bool UI::Button::isHovered(const raylib::Vector2 &mousePosition) const
{
    return CheckCollisionPointRec(mousePosition, m_rect);
}
