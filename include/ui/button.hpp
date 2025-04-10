#pragma once

#include "raylib-cpp.hpp"
#include <string>
#include "ui/text.hpp"

namespace UI 
{

    class Button
    {
        raylib::Color m_color;
        raylib::Rectangle m_rect;
        UI::Text m_text;

    public:

        Button() = default;

        Button(const raylib::Color &color, const raylib::Rectangle &rect, const raylib::Color &textColor, const std::string &text, 
            const float fontSize, const raylib::Font *font = nullptr);

        ~Button() = default;

        void init(const raylib::Color &color, const raylib::Rectangle &rect, const raylib::Color &textColor, const std::string &text,
                  const float fontSize, const raylib::Font *font = nullptr);

        void render() const;
        void render(const raylib::Camera2D& camera) const;

        void setColor(const raylib::Color &newColor);
        void setText(const std::string &text);
        void setTextPosition(const raylib::Vector2& pos);
        void setFontSize(const float fontSize);
        void setFont(const raylib::Font *font = nullptr);

        const raylib::Color &getColor() const;
        const std::string& getText() const;
        const raylib::Vector2& getTextPosition() const;
        float getFontSize() const;
        const raylib::Font *getFont() const;

        bool isHovered(const raylib::Vector2& mousePosition) const;
    };

}