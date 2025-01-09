#pragma once

#include "raylib-cpp.hpp"
#include <vector>

namespace Colors
{
    // Home Scene
    
    // Easy Button (Green - Calm, approachable)
    const raylib::Color EASY_BASE_COLOR(100, 180, 100);     // Slightly desaturated, friendly green
    const raylib::Color EASY_HOVER_COLOR(130, 210, 130);    // Lighter, more vibrant green
    const raylib::Color EASY_CLICKED_COLOR(70, 150, 70);     // Darker, slightly desaturated green

    // Medium Button (Yellow/Orange - Balanced, moderate challenge)
    const raylib::Color MEDIUM_BASE_COLOR(230, 180, 50);    // Warm, slightly golden yellow/orange
    const raylib::Color MEDIUM_HOVER_COLOR(255, 200, 70);   // Brighter, more saturated yellow/orange
    const raylib::Color MEDIUM_CLICKED_COLOR(200, 150, 30);    // Darker, slightly reddish orange

    // Hard Button (Red/Dark Orange - Challenging, intense)
    const raylib::Color HARD_BASE_COLOR(200, 80, 50);     // Slightly desaturated, deep reddish-orange
    const raylib::Color HARD_HOVER_COLOR(230, 100, 70);    // Brighter, more saturated red-orange
    const raylib::Color HARD_CLICKED_COLOR(150, 50, 30);     // Darker, more maroonish red

    // Impossible Button (Black/Dark Purple - Extremely difficult)
    const raylib::Color IMPOSSIBLE_BASE_COLOR(30, 20, 40);    // Very dark purple, almost black
    const raylib::Color IMPOSSIBLE_HOVER_COLOR(50, 40, 60);   // Slightly lighter, more visible dark purple
    const raylib::Color IMPOSSIBLE_CLICKED_COLOR(10, 0, 20);    // Even darker, almost imperceptible shift towards black

    // Play/Exit Buttons (Orange/Brown - Warm/Friendly)
    const raylib::Color BUTTON_BASE_COLOR(210, 180, 140); // Light Brownish Orange
    const raylib::Color BUTTON_HOVER_COLOR(255, 204, 102); // Light Orange
    const raylib::Color BUTTON_CLICKED_COLOR(160, 82, 45);  // Sienna

    // Game Scene
    const raylib::Color WORM_HEAD_COLOR(97, 62, 33);
    const raylib::Color WORM_BODY_COLOR(145, 94, 49);
    const raylib::Color FOOD_COLOR(33, 97, 34);
    const raylib::Color BORDER_COLOR(46, 33, 97);
    
}