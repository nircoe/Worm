#include "ui/button.hpp"
#include "auxiliary/utils.hpp"

UI::Button::Button(const raylib::Color &color, const raylib::Rectangle &rect, const raylib::Color &textColor, const std::string &text,
    const float fontSize, const raylib::Font *font) : 
    m_color(color),
    m_rect(rect),
    m_text(text, textColor, fontSize, rect, font) { }

void UI::Button::init(const raylib::Color &color, const raylib::Rectangle &rect, const raylib::Color &textColor, const std::string &text,
    const float fontSize, const raylib::Font *font)
{
    m_color = color;
    m_rect = rect;
    m_text.init(text, textColor, fontSize, m_rect, font);
}

void UI::Button::render() const
{
    DrawRectangleRounded(m_rect, 0.2f, 16, m_color);
    m_text.render();
}

void UI::Button::render(const raylib::Camera2D& camera) const
{
    raylib::Rectangle rect = raylib::Rectangle(camera.GetWorldToScreen(m_rect.GetPosition()), { m_rect.width, m_rect.height });
    DrawRectangleRounded(rect, 0.2f, 16, m_color);
    m_text.render(camera);
}

void UI::Button::setColor(const raylib::Color &newColor)
{
    m_color = newColor;
}

void UI::Button::setText(const std::string &text)
{
    m_text.setText(text);
}

void UI::Button::setTextPosition(const raylib::Vector2& pos)
{
    m_text.setTextPosition(pos);
}

void UI::Button::setFontSize(const float fontSize)
{
    m_text.setFontSize(fontSize);
}

void UI::Button::setFont(const raylib::Font *font)
{
    m_text.setFont(font);
}

float UI::Button::getFontSize() const
{
    return m_text.getFontSize();
}

const raylib::Font *UI::Button::getFont() const
{
    return m_text.getFont();
}

bool UI::Button::isHovered(const raylib::Vector2 &mousePosition) const
{
    return CheckCollisionPointRec(mousePosition, m_rect);
}
