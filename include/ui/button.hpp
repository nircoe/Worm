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
        // raylib::Vector2 m_textPosition;
        // raylib::Color m_textColor;
        // std::string m_text;
        // float m_fontSize;
        // const raylib::Font *m_font;

    public:

        Button() = default;

        Button(raylib::Color color, raylib::Rectangle rect, raylib::Color textColor, std::string text, 
            float fontSize, const raylib::Font *font = nullptr);

        ~Button() = default;

        void init(raylib::Color color, raylib::Rectangle rect, raylib::Color textColor, std::string text, 
            float fontSize, const raylib::Font *font = nullptr);

        void render(const raylib::Font& font, float spacing = 1) const;
        void render(const raylib::Font& font, const raylib::Camera2D& camera, float spacing = 1) const;

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