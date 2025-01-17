#include "raylib-cpp.hpp"
#include "auxiliary/colors.hpp"
#include "auxiliary/consts.hpp"
#include "scene_manager.hpp"
#include "home_scene.hpp"
#include "game_scene.hpp"
#include "player.hpp"
#include "food.hpp"

int main() 
{
    SetTraceLogLevel(LOG_ALL);       // Show all logs

    HomeScene homeScene;
    GameScene gameScene(Consts::STARTING_DIFFICULTY);

    SceneManager sceneManager({ &homeScene, &gameScene });
    //SceneManager sceneManager({ &homeScene });
    // SceneManager sceneManager({ &gameScene });

    return sceneManager.gameLoop();
}