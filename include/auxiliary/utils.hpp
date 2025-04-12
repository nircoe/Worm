#pragma once

#include "raylib-cpp.hpp"
#include "consts.hpp"
#include "enums.hpp"
#include <vector>
#include <random>

namespace Utils
{
    inline const raylib::Vector2 getFoodSpawnPoint(const std::deque<raylib::Vector2>& playerBody)
    {
        const float margin = Consts::FOOD_SPAWN_MARGIN;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(margin, Consts::SCREEN_WIDTH - margin);
        std::uniform_real_distribution<float> distY(margin, Consts::SCREEN_HEIGHT - margin);
        raylib::Vector2 spawnPoint = raylib::Vector2();
        bool valid = false;
        
        while(!valid)
        {
            spawnPoint.x = distX(gen);
            spawnPoint.y = distY(gen);
            Rectangle rec = { spawnPoint.x, spawnPoint.y, 5.0f, 5.0f};
            bool collision = false;
            for (auto it = playerBody.begin(); it != playerBody.end(); ++it)
            {
                float radius = (playerBody.front().Equals(*it)) ? 
                                Consts::PLAYER_HEAD_RADIUS : 
                                Consts::PLAYER_BODY_RADIUS;
                if(CheckCollisionCircleRec(*it, radius, rec))
                {
                    collision = true;
                    break;
                }
            }

            valid = !collision;
        }

        return spawnPoint;
    }

    inline int centerlizeTextX(const char* text, const int fontSize) 
    {
        return (Consts::SCREEN_WIDTH - MeasureText(text, fontSize)) / 2;
    }

    inline void drawTestingText(raylib::Window& window, 
                                const int TargetFPS, const raylib::Vector2 playerPos)
    {
        const char* targetFPSStr = TargetFPS > 0 ? TextFormat("Target FPS: %i", TargetFPS) : "Target FPS: MAX";
        std::pair<int, int> fpsPos = std::pair<int, int>(50, 50);
        DrawText(targetFPSStr, fpsPos.first, fpsPos.second, 20, BLACK);
        DrawText(TextFormat("Current FPS: %i", window.GetFPS()), fpsPos.first, fpsPos.second + 50, 20, BLACK);
        DrawText(TextFormat("X: %f", playerPos.x), fpsPos.first, fpsPos.second + 100, 20, BLACK);
        DrawText(TextFormat("Y: %f", playerPos.y), fpsPos.first, fpsPos.second + 130, 20, BLACK);
    }

    // Gives you the position (Vector2) for your text so it will be Centered in specific area for Font
    inline raylib::Vector2 centralizeTextEx(Font font, const char *text, float fontSize, 
                                            const raylib::Vector2& anchorPosition, const raylib::Vector2& areaSize, float spacing = 1)
    {
        raylib::Vector2 textPosition = { 0 };
        raylib::Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);

        textPosition = anchorPosition + ((areaSize - textSize) / 2.0f);

        return textPosition;
    }

    // Gives you the position (Vector2) for your text so it will be Centered in specific area for default font
    inline raylib::Vector2 centralizeText(const char *text, int fontSize, 
                                            const raylib::Vector2& anchorPosition, const raylib::Vector2& areaSize)
    {
        raylib::Vector2 textPosition = { 0.0f, 0.0f };

        // Check if default font has been loaded
        if (GetFontDefault().texture.id != 0)
        {
            int defaultFontSize = 10;   // Default Font chars height in pixel
            if (fontSize < defaultFontSize) fontSize = defaultFontSize;
            int spacing = fontSize/defaultFontSize;

            textPosition = centralizeTextEx(GetFontDefault(), text, (float)fontSize, anchorPosition, areaSize, (float)spacing);
        }

        return textPosition;
    }

    inline void drawButton(const raylib::Font& font, const raylib::Rectangle& rect, 
                            const std::string& text, const raylib::Vector2& textPosition, 
                            const raylib::Color& buttonColor, float fontSize, 
                            const raylib::Color& textColor, float spacing = 1) 
    {
        DrawRectangleRec(rect, buttonColor);
        raylib::DrawTextEx(font, text.c_str(), textPosition, fontSize, spacing, textColor);
    }
} // namespace Utils
