#pragma once

#include "raylib-cpp.hpp"
#include <string>

namespace UI
{

    class Text
    {
        std::string m_text;
        raylib::Vector2 m_textPosition;
        raylib::Color m_color;
        float m_fontSize;
        const raylib::Font *m_font;
        float m_spacing;
        raylib::Rectangle m_rect;

        void calculateRect();

    public:
        Text() = default;

        Text(const std::string &text, const raylib::Vector2 &textPosition, const raylib::Color &color,
             const float fontSize, const raylib::Font *font = nullptr, const float spacing = 1);

        Text(const std::string &text, const raylib::Color &color, const float fontSize,
             const raylib::Rectangle &area, const raylib::Font *font = nullptr, const float spacing = 1);

        ~Text() = default;

        void init(const std::string &text, const raylib::Vector2 &textPosition, const raylib::Color &color,
                  const float fontSize, const raylib::Font *font = nullptr, const float spacing = 1);

        void init(const std::string &text, const raylib::Color &color, const float fontSize,
                  const raylib::Rectangle &area, const raylib::Font *font = nullptr, const float spacing = 1);

        void render() const;
        void render(const raylib::Camera2D &camera) const;

        void setText(const std::string &text);
        void setTextPosition(const raylib::Vector2 &pos);
        void centralizeText(const raylib::Rectangle &area);
        void setColor(const raylib::Color &newColor);
        void setFontSize(const float fontSize);
        void setFont(const raylib::Font *font = nullptr);

        const std::string &getText() const;
        const raylib::Vector2 &getTextPosition() const;
        const raylib::Color &getColor() const;
        float getFontSize() const;
        const raylib::Font *getFont() const;

        bool isHovered(const raylib::Vector2 &mousePosition) const;
    };

} // namespace uicoe