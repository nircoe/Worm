#pragma once

#include "raylib-cpp.hpp"
#include <string>

namespace UI 
{

    class Button
    {
        raylib::Color m_color;
        raylib::Rectangle m_rect;
        raylib::Vector2 m_textPosition;
        raylib::Color m_textColor;
        std::string m_text;
        float m_fontSize;

    public:

        Button() = default;

        Button(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition, 
            raylib::Color textColor, std::string text, float fontSize);

        ~Button() = default;

        void init(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition, 
            raylib::Color textColor, std::string text, float fontSize);

        void render(const raylib::Font& font, float spacing = 1) const;

        void setTextPosition(const raylib::Vector2& pos);

        void setColor(const raylib::Color& newColor);

        const bool isHovered(const raylib::Vector2& mousePosition);
        // more methods
    };

}