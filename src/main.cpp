#include "raylib-cpp.hpp"
#include "auxiliary/colors.hpp"
#include "auxiliary/consts.hpp"
#include "game_manager.hpp"
#include "new_game_scene.hpp"
#include "home_scene.hpp"
#include "game_scene.hpp"
#include "player.hpp"
#include "food.hpp"

int main() 
{
    SetTraceLogLevel(LOG_ALL);       // Show all logs, TODO: delete when finish the project!

    NewGameScene newGameScene;
    HomeScene homeScene;
    GameScene gameScene(Consts::STARTING_DIFFICULTY);

    GameManager gameManager({ &newGameScene, &homeScene, &gameScene });

    return gameManager.gameLoop();
}