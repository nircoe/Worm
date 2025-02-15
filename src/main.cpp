#include "raylib-cpp.hpp"
#include "auxiliary/colors.hpp"
#include "auxiliary/consts.hpp"
#include "game_manager.hpp"
#include "home_scene.hpp"
#include "game_scene.hpp"
#include "player.hpp"
#include "food.hpp"

int main() 
{
    SetTraceLogLevel(LOG_ALL);       // Show all logs

    HomeScene homeScene;
    GameScene gameScene(Consts::STARTING_DIFFICULTY);

    GameManager gameManager({ &homeScene, &gameScene });
    //GameManager gameManager({ &homeScene });
    // GameManager gameManager({ &gameScene });

    return gameManager.gameLoop();
}