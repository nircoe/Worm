#include "scene_manager.hpp"
#include "scene.hpp"
#include "home_scene.hpp"
#include "game_scene.hpp"
#include "raylib-cpp.hpp"
#include <string>
#include "auxiliary/enums.hpp"
#include <algorithm>
#include <iostream>
#include <exception>

SceneManager::SceneManager(std::initializer_list<Scene*> scenes) : 
    m_window(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT, Consts::GAME_NAME),
    m_camera(raylib::Vector2::Zero(), raylib::Vector2::Zero()),
    m_font(Consts::FONT_PATH, 80),
    m_iconImage(Consts::ICON_IMAGE_PATH)
{
    m_window.SetTargetFPS(static_cast<int>(Enums::Difficulty::Medium));
    m_window.SetIcon(m_iconImage);

    size_t i = 0;
    for(Scene* scene: scenes)
    {
        if(i >= Consts::NUM_OF_SCENES)
        {
            TraceLog(LOG_WARNING, "Too many scenes provided, will take only " + Consts::NUM_OF_SCENES);
            break;
        }
        m_scenes[i] = scene;
        ++i;
    }
    m_activeScenes.set(0);
    static_cast<HomeScene*>(m_scenes[0])->calculateTitlePosition(m_font);
}

void SceneManager::activateScene(Enums::SceneName sceneName)
{
    setSceneActive(sceneName, true);
    if(sceneName == Enums::SceneName::Game_Scene)
    {
        HomeScene* homeScene = static_cast<HomeScene*>(m_scenes[static_cast<int>(Enums::SceneName::Home_Scene)]);
        Enums::Difficulty difficulty = homeScene->getDifficulty();
        GameScene* gameScene = static_cast<GameScene*>(m_scenes[static_cast<int>(sceneName)]);
        gameScene->changeDifficulty(difficulty);
    }
}

void SceneManager::deactivateScene(Enums::SceneName sceneName)
{
    setSceneActive(sceneName, false);
}

// close the game at the end of the frame
void SceneManager::closeGame()
{
    m_shouldClose = true;
}

void SceneManager::changeDifficulty(Enums::Difficulty newDifficulty)
{
    m_targetFPS = static_cast<int>(newDifficulty);
    m_window.SetTargetFPS(m_targetFPS);
}

void SceneManager::setSceneActive(Enums::SceneName sceneName, bool active)
{
    int scene = static_cast<int>(sceneName);
    if(scene < 0 || m_scenes.size() <= scene) 
        closeGame();
    m_activeScenes.set(scene, active);
}

void SceneManager::update()
{
    for(std::size_t i = 0; i < Consts::NUM_OF_SCENES; ++i)
    {
        if(m_activeScenes.test(i))
        {
            m_scenes[i]->update(*this);
        }
    }
}

void SceneManager::render()
{
    for(std::size_t i = 0; i < Consts::NUM_OF_SCENES; ++i)
    {
        if(m_activeScenes.test(i))
        {
            m_scenes[i]->render();
        }
    }
}

void SceneManager::renderUI()
{
    for(std::size_t i = 0; i < Consts::NUM_OF_SCENES; ++i)
    {
        if(m_activeScenes.test(i))
        {
            m_scenes[i]->renderUI(m_font);
        }
    }
}

int SceneManager::gameLoop()
{
    try
    {
        while(!m_shouldClose && !m_window.ShouldClose())
        {
            this->update();

            m_window.BeginDrawing();
            {
                m_window.ClearBackground(WHITE);
                m_camera.BeginMode();
                {
                    this->render();
                }
                m_camera.EndMode();

                this->renderUI();
            }   
            m_window.EndDrawing();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0; // Success
}
