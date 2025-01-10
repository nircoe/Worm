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

    // Impossible Button (Deep Purple/Electric Purple - Extremely difficult)
    const raylib::Color IMPOSSIBLE_BASE_COLOR(40, 20, 70);       // Deep purple
    const raylib::Color IMPOSSIBLE_HOVER_COLOR(70, 40, 120);     // Electric purple (more blue and brighter)
    const raylib::Color IMPOSSIBLE_CLICKED_COLOR(20, 10, 35);      // Darker, almost black purple with a red undertone

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