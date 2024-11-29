#pragma once

#include "raylib-cpp.hpp"
#include <vector>

namespace Colors
{
/*
    #define VERY_LIGHT_OCEAN    CLITERAL(Color){ 222, 243, 246, 255 }       // Very Light Ocean
    #define LIGHT_OCEAN         CLITERAL(Color){ 135, 206, 250, 255 }       // Light Ocean
    #define OCEAN               CLITERAL(Color){ 102, 204, 255, 255 }       // Ocean
    #define DARK_OCEAN          CLITERAL(Color){ 0, 102, 204, 255 }         // Dark Ocean
    #define VERY_DARK_OCEAN     CLITERAL(Color){ 0, 51, 102, 255 }          // Very Dark Ocean

    const std::vector<Color> OCEAN_PALETTE = { VERY_LIGHT_OCEAN, LIGHT_OCEAN, OCEAN, DARK_OCEAN, VERY_DARK_OCEAN }; // Ocean Color Palette


    Color transitionColorPalette(const std::vector<Color> colorPalette, const float cameraTargetY)
    {
        const float jumps = 300.0f, bottom = -600.0f;
        std::vector<float> depths = { bottom };

        for(int i = 1; i < colorPalette.size(); ++i)
        {
            depths.push_back(depths[i - 1] + jumps);
        }

        for(int i = 0; i < depths.size() - 1; ++i)
        {
            if(cameraTargetY <= depths[i])
            {
                return colorPalette[i];
            }
            if(depths[i] < cameraTargetY && cameraTargetY < depths[i + 1])
            {
                float t = (cameraTargetY - depths[i]) / jumps;
                return {    static_cast<unsigned char>(colorPalette[i].r + t * (colorPalette[i + 1].r - colorPalette[i].r)),
                            static_cast<unsigned char>(colorPalette[i].g + t * (colorPalette[i + 1].g - colorPalette[i].g)),
                            static_cast<unsigned char>(colorPalette[i].b + t * (colorPalette[i + 1].b - colorPalette[i].b)),
                            255 };
            }
        }
        return colorPalette.back();
    }
*/
}