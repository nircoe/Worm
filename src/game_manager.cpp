#include "game_manager.hpp"
#include "scene.hpp"
#include "home_scene.hpp"
#include "game_scene.hpp"
#include <cstddef>
#include <string>
#include "auxiliary/enums.hpp"
#include "auxiliary/colors.hpp"
#include <iostream>
#include <exception>

GameManager::GameManager(std::initializer_list<Scene*> scenes) : 
    m_window(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT, Consts::GAME_NAME),
    m_camera(raylib::Vector2::Zero(), raylib::Vector2::Zero()),
    m_font(Consts::FONT_PATH, 80),
    m_iconImage(Consts::ICON_IMAGE_PATH)
{
    m_window.SetTargetFPS(static_cast<int>(Enums::Difficulty::Easy));
    m_window.SetIcon(m_iconImage);

    std::size_t i = 0;
    for (Scene *scene : scenes)
    {
        if (i >= Consts::NUM_OF_SCENES)
        {
            std::string message = "Too many scenes provided, will take only " + std::to_string(Consts::NUM_OF_SCENES);
            TraceLog(LOG_WARNING, message.c_str());
            fflush(stdout);
            break;
        }
        m_scenes[i] = scene;
        deactivateScene(static_cast<Enums::SceneName>(i));
        ++i;
    }

    if (m_dataManager.init(getGameDataPath().string()))
        activateScene(Enums::SceneName::Home_Scene);
    else // failed to load, start new game
    {
        m_window.SetTargetFPS(60);
        activateScene(Enums::SceneName::New_Game_Scene);
    }
    for(auto& scene : m_scenes)
    {
        if(scene->isActive())
            scene->initUI(*this);
    }
}

void GameManager::activateScene(Enums::SceneName sceneName)
{
    setSceneActive(sceneName, true);
    if(sceneName == Enums::SceneName::Game_Scene)
    {
        HomeScene* homeScene = static_cast<HomeScene*>(m_scenes[static_cast<int>(Enums::SceneName::Home_Scene)]);
        Enums::Difficulty difficulty = homeScene->getDifficulty();
        GameScene* gameScene = static_cast<GameScene*>(m_scenes[static_cast<int>(sceneName)]);
        gameScene->changeDifficulty(difficulty);
    }
    m_scenes[static_cast<int>(sceneName)]->initUI(*this);
}

void GameManager::deactivateScene(Enums::SceneName sceneName)
{
    setSceneActive(sceneName, false);
}

// close the game at the end of the frame
void GameManager::closeGame()
{
    m_shouldClose = true;
}

void GameManager::changeDifficulty(Enums::Difficulty newDifficulty)
{
    m_targetFPS = static_cast<int>(newDifficulty);
    m_window.SetTargetFPS(m_targetFPS);
}

void GameManager::setSceneActive(Enums::SceneName sceneName, bool active)
{
    int scene = static_cast<int>(sceneName);
    if (scene < 0 || static_cast<int>(m_scenes.size()) <= scene)
    {
        std::cerr << "Error: Invalid Scene Name" << std::endl;
        closeGame();
    }
    m_scenes[scene]->setActive(active);
    m_activeScenes.set(scene, active);
}

std::filesystem::path GameManager::getGameDataPath()
{
    std::filesystem::path path = std::filesystem::path(GetApplicationDirectory());
    path /= "savedata";

    if(!std::filesystem::exists(path))
        std::filesystem::create_directory(path);
    
    return path / "gamedata.bin";
}

void GameManager::update()
{
    for(auto scene : m_scenes)
    {
        if(scene->isActive())
            scene->update(*this);
    }
}

void GameManager::render()
{
    for (auto scene : m_scenes)
    {
        if (scene->isActive())
            scene->render();
    }
}

void GameManager::renderUI()
{
    for (auto scene : m_scenes)
    {
        if (scene->isActive())
            scene->renderUI(m_font, m_camera);
    }
}

const raylib::Font &GameManager::getFont() const
{
    return m_font;
}

void GameManager::moveCamera(raylib::Vector2 velocity)
{
    raylib::Vector2 target = m_camera.target;
    raylib::Vector2 newValue = target + (velocity);
    m_camera.SetTarget(newValue);
}

const raylib::Vector2 GameManager::getCameraTarget() const
{
    return m_camera.GetTarget();
}

void GameManager::resetCamera()
{
    m_camera.SetTarget(raylib::Vector2::Zero());
}

void GameManager::newGame(const std::string& nickname)
{
    m_dataManager.newGame(nickname);
}

const datacoe::GameData GameManager::getGamedata() const
{
    return m_dataManager.getGamedata();
}

bool GameManager::saveGame(const datacoe::GameData &data)
{
    m_dataManager.setGamedata(data);
    return m_dataManager.saveGame();
}

int GameManager::gameLoop()
{
    try
    {
        while(!m_window.ShouldClose())
        {
            this->update();

            m_window.BeginDrawing();
            {
                m_window.ClearBackground(Colors::BACKGROUND_COLOR);
                m_camera.BeginMode();
                {
                    this->render();
                }
                m_camera.EndMode();

                this->renderUI();
            }   
            m_window.EndDrawing();

            if(m_shouldClose) 
                m_window.Close();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    
    return 0; // Success
}
