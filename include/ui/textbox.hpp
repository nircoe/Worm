#pragma once

#include "raylib-cpp.hpp"
#include <string>

namespace UI
{
    class TextBox
    {
        raylib::Color m_color;
        raylib::Rectangle m_rect;
        raylib::Vector2 m_textPosition;
        raylib::Color m_textColor;
        float m_fontSize;
        std::string m_text;

        std::size_t m_framesCounter = 0;
        std::size_t m_lastFrameDelete = 0;

    public:
        TextBox() = default;

        TextBox(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition,
                raylib::Color textColor, float fontSize, std::string text = "");

        ~TextBox() = default;

        void init(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition,
                  raylib::Color textColor, float fontSize, std::string text = "");

        void update();

        void render(const raylib::Font &font, bool round = true, float spacing = 1) const;
        void render(const raylib::Font &font, const raylib::Camera2D &camera, bool round = true, float spacing = 1) const;

        void setColor(const raylib::Color &newColor);

        std::string getText() const;

        bool isHovered(const raylib::Vector2 &mousePosition) const;
    };

}