#include "ui/text.hpp"
#include "auxiliary/utils.hpp"

void UI::Text::calculateRect()
{
    raylib::Vector2 textSize = m_font ? 
        MeasureTextEx(*m_font, m_text.c_str(), m_fontSize, m_spacing) : 
        raylib::Vector2((float)MeasureText(m_text.c_str(), (int)m_fontSize), m_fontSize);
    m_rect = raylib::Rectangle(m_textPosition, textSize);
}

UI::Text::Text(const std::string &text, const raylib::Vector2 &textPosition, const raylib::Color &color,
    const float fontSize, const raylib::Font *font, const float spacing) : 
    m_text(text),
    m_textPosition(textPosition),
    m_color(color),
    m_fontSize(fontSize),
    m_font(font),
    m_spacing(spacing)
{
    calculateRect();
}

UI::Text::Text(const std::string &text, const raylib::Color &color, const float fontSize, 
    const raylib::Rectangle &area, const raylib::Font *font, const float spacing) :
    m_text(text),
    m_color(color),
    m_fontSize(fontSize),
    m_font(font),
    m_spacing(spacing)
{
    centralizeText(area); // it will call calculateRect()
}

void UI::Text::init(const std::string &text, const raylib::Vector2 &textPosition, const raylib::Color &color,
                    const float fontSize, const raylib::Font *font, const float spacing)
{
    m_text = text;
    m_textPosition = textPosition;
    m_color = color;
    m_fontSize = fontSize;
    m_font = font ? font : m_font;
    m_spacing = spacing;
    calculateRect();
}

void UI::Text::init(const std::string &text, const raylib::Color &color, const float fontSize,
                    const raylib::Rectangle &area, const raylib::Font *font, const float spacing)
{
    m_text = text;
    m_color = color;
    m_fontSize = fontSize;
    m_font = font;
    m_spacing = spacing;
    centralizeText(area); // it will call calculateRect()
}
void UI::Text::render() const
{
    if (m_font)
        raylib::DrawTextEx(*m_font, m_text, m_textPosition, m_fontSize, m_spacing, m_color);
    else // default font
        raylib::DrawText(m_text, (int)m_textPosition.x, (int)m_textPosition.y, (int)m_fontSize, m_color);
}

void UI::Text::render(const raylib::Camera2D &camera) const
{
    if (m_font)
        raylib::DrawTextEx(*m_font, m_text, camera.GetWorldToScreen(m_textPosition), m_fontSize, m_spacing, m_color);
    else // default font
        raylib::DrawText(m_text, (int)m_textPosition.x, (int)m_textPosition.y, (int)m_fontSize, m_color);
}

void UI::Text::setText(const std::string &text)
{
    m_text = text;
    calculateRect();
}

void UI::Text::setText(const std::string &text, const raylib::Rectangle &area)
{
    m_text = text;
    centralizeText(area);
}

void UI::Text::setTextPosition(const raylib::Vector2 &pos)
{
    m_textPosition = pos;
    calculateRect();
}

void UI::Text::centralizeText(const raylib::Rectangle &area)
{
    if (m_font)
        m_textPosition = Utils::centralizeTextEx(*m_font, m_text.c_str(), m_fontSize, area.GetPosition(), area.GetSize());
    else
        m_textPosition = Utils::centralizeText(m_text.c_str(), (int)m_fontSize, area.GetPosition(), area.GetSize());
    calculateRect();
}

void UI::Text::setColor(const raylib::Color &newColor) { m_color = newColor; }

void UI::Text::setFontSize(const float fontSize)
{
    m_fontSize = fontSize;
    calculateRect();
}

void UI::Text::setFont(const raylib::Font *font)
{
    m_font = font;
    calculateRect();
}

const std::string &UI::Text::getText() const { return m_text; }

const raylib::Vector2 &UI::Text::getTextPosition() const { return m_textPosition; }

const raylib::Color &UI::Text::getColor() const { return m_color; }

float UI::Text::getFontSize() const { return m_fontSize; }

const raylib::Font *UI::Text::getFont() const { return m_font; }

std::size_t UI::Text::length() const
{
    return m_text.length();
}

bool UI::Text::isHovered(const raylib::Vector2 &mousePosition) const { return CheckCollisionPointRec(mousePosition, m_rect); }

UI::Text &UI::Text::operator+=(const std::string &addition)
{
    m_text += addition;
    return *this;
}

UI::Text &UI::Text::operator+=(const char addition)
{
    m_text += addition;
    return *this;
}

UI::Text &UI::Text::operator+=(const char *addition)
{
    m_text += addition;
    return *this;
}

UI::Text &UI::Text::operator--()
{
    m_text = m_text.substr(0, length() - 1);
    return *this;
}

const UI::Text UI::Text::operator--(int)
{
    const UI::Text text(*this);
    --(*this);
    return text;
}
