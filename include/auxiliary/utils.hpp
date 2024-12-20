#pragma once

#include "raylib-cpp.hpp"
#include "consts.hpp"
#include <vector>
#include <random>

namespace Utils
{
    inline const raylib::Vector2 getFoodSpawnPoint(const std::list<raylib::Vector2>& playerBody)
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

    inline const raylib::Vector2 getFoodSize()
    {
        return raylib::Vector2(Consts::FOOD_SIZE, Consts::FOOD_SIZE);
    }

    inline const int centerlizeTextX(const char* text, const int fontSize) 
    {
        return (Consts::SCREEN_WIDTH - MeasureText(text, fontSize)) / 2;
    }

} // namespace Utils
