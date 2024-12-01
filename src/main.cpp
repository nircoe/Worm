#include "raylib-cpp.hpp"
#include "colors.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "food.hpp"

using std::string;


void HandleCamera(raylib::Camera2D& camera, const raylib::Vector2 CharacterPos)
{
    const float smoothFactor = 0.02f;
    camera.target = Vector2Lerp(camera.target, CharacterPos, smoothFactor);
}

void WindowSettings(raylib::Window& window, const int TargetFPS, const raylib::Image& IconImage)
{
    window.SetTargetFPS(TargetFPS);
    window.SetIcon(IconImage);
}

void HandleText(raylib::Window& window, raylib::Camera2D& camera, const int TargetFPS)
{
    const char* targetFPSStr = TargetFPS > 0 ? TextFormat("Target FPS: %i", TargetFPS) : "Target FPS: MAX";
    std::pair<int, int> fpsPos = std::pair<int, int>(50, 50);
    DrawText(targetFPSStr, fpsPos.first, fpsPos.second, 20, BLACK);
    DrawText(TextFormat("Current FPS: %i", window.GetFPS()), fpsPos.first, fpsPos.second + 50, 20, BLACK);
    DrawText(TextFormat("X: %f", camera.target.x), fpsPos.first, fpsPos.second + 100, 20, BLACK);
    DrawText(TextFormat("Y: %f", camera.target.y), fpsPos.first, fpsPos.second + 130, 20, BLACK);
}

int main() 
{
    // Awake
    const std::pair<int, int> ScreenSize = std::pair<int, int>(800, 800);
    const raylib::Vector2 fScreenSize = raylib::Vector2((float)ScreenSize.first, (float)ScreenSize.second);
    const int TargetFPS = 60;
    const raylib::Image IconImage = raylib::Image("C:/Projects/Worm/assets/worm.png");  
    
    raylib::Vector2 characterPos = raylib::Vector2();
    raylib::Camera2D camera = raylib::Camera2D({fScreenSize.x / 2, fScreenSize.y / 2}, {0.0f, 0.0f});
    raylib::Window window(ScreenSize.first, ScreenSize.second, "Worm");

    Scene scene = Scene();

    // Start
    WindowSettings(window, TargetFPS, IconImage);
    
    // Update
    while(!window.ShouldClose())
    {
        scene.Update();

        // Drawing
        window.BeginDrawing();
        {
            window.ClearBackground(WHITE);
            camera.BeginMode();
            {
                // HandleCamera / UpdateCamera
                HandleCamera(camera, player->GetPosition());
                scene.Render();
            }
            camera.EndMode();

            // HandleText / HandleUI
            HandleText(window, camera, TargetFPS);
        }   
        window.EndDrawing();
    }

    return 0;
}