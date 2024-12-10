#pragma once

#include <string>

namespace Consts
{
    const std::string TRANSFORM = "Transform";
    const std::string MOVEABLE = "Moveable";
    const std::string COLLIDER = "Collider";
    const std::string CIRCLE_COLLIDER = "Circle_Collider";
    const std::string RECT_COLLIDER = "Rect_Collider";

    const int FPS_TARGET = 10;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;

    const float ZERO_F = 0.0f;
    const float ONE_F = 1.0f;
    const float PLAYER_SPEED = 20.0f;
    const float FOOD_SIZE = 8.0f;
    const float PLAYER_HEAD_RADIUS = 12.0f;
    const float PLAYER_BODY_RADIUS = 10.0f;
    const float FOOD_SPAWN_MARGIN = 50.0f;

    const raylib::Vector2 ZERO_2D = { 0.0f, 0.0f };
    const std::vector<raylib::Vector2> INITIAL_PLAYER_BODY = { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 
                                                                {(SCREEN_WIDTH / 2) - 20.0f, SCREEN_HEIGHT / 2}, 
                                                                {(SCREEN_WIDTH / 2) - (2 * 19.0f), SCREEN_HEIGHT / 2} };
} // namespace Consts
