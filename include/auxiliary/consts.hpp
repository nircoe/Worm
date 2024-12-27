#pragma once

#include "raylib-cpp.hpp"
#include <string>
#include <list>

namespace Consts
{
    const std::string GAME_OVER_TEXT = "GAME OVER!";
    const std::string TRANSFORM = "Transform";
    const std::string MOVEABLE = "Moveable";
    const std::string COLLIDER = "Collider";
    const std::string CIRCLE_COLLIDER = "Circle_Collider";
    const std::string RECT_COLLIDER = "Rect_Collider";

    const int EASY_FPS_TARGET = 10;
    const int MEDIUM_FPS_TARGET = 20;
    const int HARD_FPS_TARGET = 30;
    const int IMPOSSIBLE_FPS_TARGET = 60;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    const int GAME_OVER_FONT_SIZE = 50;
    const int NAME_OF_SCENES = 2;

    const float PLAYER_SPEED = 23.0f;
    const float DIAGONAL_MULTIPLY = 1.352f;
    const float FOOD_SIZE = 15.0f;
    const float PLAYER_HEAD_RADIUS = 12.0f;
    const float PLAYER_BODY_RADIUS = 10.0f;
    const float FOOD_SPAWN_MARGIN = 50.0f;

    const raylib::Vector2 ZERO_2D = { 0.0f, 0.0f };
    const raylib::Vector2 HALF_SCREEN = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    const std::list<raylib::Vector2> INITIAL_PLAYER_BODY = { HALF_SCREEN, HALF_SCREEN, HALF_SCREEN };
    const std::vector<raylib::Rectangle> BORDERS = {
        { -1.0f, -1.0f, 10.0f, SCREEN_HEIGHT + 1.0f },
        { -1.0f, -1.0f, SCREEN_WIDTH + 1.0f, 10.0f },
        { -1.0f, SCREEN_HEIGHT - 10.0f, SCREEN_WIDTH + 1.0f, 10.0f },
        { SCREEN_WIDTH - 10.0f, -1.0f, 10.0f, SCREEN_HEIGHT + 1.0f }
    };

    const raylib::Font FONT("../../assets/fonts/joystix_monospace.otf");
} // namespace Consts
