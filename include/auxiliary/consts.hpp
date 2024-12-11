#pragma once

#include "raylib-cpp.hpp"
#include <string>

namespace Consts
{

    const std::string GAME_OVER_TEXT = "GAME OVER!";
    const std::string TRANSFORM = "Transform";
    const std::string MOVEABLE = "Moveable";
    const std::string COLLIDER = "Collider";
    const std::string CIRCLE_COLLIDER = "Circle_Collider";
    const std::string RECT_COLLIDER = "Rect_Collider";

    const int TWO = 2;
    const int FPS_TARGET = 10;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    const int GAME_OVER_FONT_SIZE = 50;

    const float HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2.0f;
    const float HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2.0f;
    const float PLAYER_SPEED = 23.0f;
    const float FOOD_SIZE = 8.0f;
    const float PLAYER_HEAD_RADIUS = 12.0f;
    const float PLAYER_BODY_RADIUS = 10.0f;
    const float FOOD_SPAWN_MARGIN = 50.0f;

    const raylib::Vector2 ZERO_2D = { 0.0f, 0.0f };
    const raylib::Vector2 HALF_SCREEN = { HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT };
    const std::vector<raylib::Vector2> INITIAL_PLAYER_BODY = { HALF_SCREEN, 
                                                                { HALF_SCREEN_WIDTH - PLAYER_SPEED, HALF_SCREEN_HEIGHT }, 
                                                                { HALF_SCREEN_WIDTH - (2.0f * (PLAYER_SPEED - 1.0f)), HALF_SCREEN_HEIGHT } };
} // namespace Consts
