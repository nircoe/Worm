#include "ui/button.hpp"
#include "auxiliary/utils.hpp"
#include "button.hpp"

UI::Button::Button(raylib::Color color, raylib::Rectangle rect, raylib::Color textColor, std::string text, 
    float fontSize, const raylib::Font *font = nullptr) : 
    m_color(color),
    m_rect(rect),
    m_text(text, textColor, fontSize, rect, font)
    // m_textColor(textColor),
    // m_text(text),
    // m_fontSize(fontSize),
    // m_font(font) 
{
    // m_textPosition = m_font ? 
    //     Utils::centralizeTextEx(*font, m_text.c_str(), m_fontSize, m_rect.GetPosition(), m_rect.GetSize()) :
    //     Utils::centralizeText(m_text.c_str(), (int)m_fontSize, m_rect.GetPosition(), m_rect.GetSize());
}

void UI::Button::init(raylib::Color color, raylib::Rectangle rect, raylib::Color textColor, std::string text, 
    float fontSize, const raylib::Font *font = nullptr)
{
    m_color = color;
    m_rect = rect;
    m_text.init(text, textColor, fontSize, m_rect, font);

    // m_textColor = textColor;
    // m_text = text;
    // m_fontSize = fontSize;
    // m_font = font;

    // m_textPosition = m_font ? 
    //     Utils::centralizeTextEx(*font, m_text.c_str(), m_fontSize, m_rect.GetPosition(), m_rect.GetSize()) :
    //     Utils::centralizeText(m_text.c_str(), (int)m_fontSize, m_rect.GetPosition(), m_rect.GetSize());
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
