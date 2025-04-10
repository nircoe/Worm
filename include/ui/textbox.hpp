#pragma once

#include "raylib-cpp.hpp"
#include <string>
#include "ui/text.hpp"

namespace UI
{
    class TextBox
    {
        raylib::Color m_color;
        raylib::Rectangle m_rect;
        UI::Text m_text;

        std::size_t m_framesCounter = 0;
        std::size_t m_lastFrameDelete = 0;

        const raylib::Rectangle getRectWorldToScreen(const raylib::Camera2D &camera);
        void renderText(const raylib::Camera2D *camera = nullptr);

    public:
        TextBox() = default;

        TextBox(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition,
                raylib::Color textColor, float fontSize, const raylib::Font *font = nullptr, std::string text = "");

        ~TextBox() = default;

        void init(raylib::Color color, raylib::Rectangle rect, raylib::Vector2 textPosition,
                  raylib::Color textColor, float fontSize, const raylib::Font *font = nullptr, std::string text = "");

        void update();

        void render();
        void render(float roundness, int segments);
        void render(const raylib::Camera2D &camera);
        void render(const raylib::Camera2D &camera, float roundness, int segments);

        void setColor(const raylib::Color &newColor);

        std::string getText() const;

        bool isHovered(const raylib::Vector2 &mousePosition) const;
    };

}