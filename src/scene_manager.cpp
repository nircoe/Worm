#include "scene_manager.hpp"
#include "scene.hpp"
#include "raylib-cpp.hpp"
#include <string>
#include "auxiliary/enums.hpp"
#include <algorithm>
#include <iostream>
#include <exception>

SceneManager::SceneManager(std::initializer_list<Scene*> scenes) : 
    m_window(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT, Consts::GAME_NAME),
    m_camera(raylib::Vector2::Zero(), raylib::Vector2::Zero())
{
    m_window.SetTargetFPS(static_cast<int>(Enums::Difficulty::Medium));
    m_window.SetIcon(Consts::ICON_IMAGE);

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
}

SceneManager::~SceneManager() { }

void SceneManager::setSceneActive(Enums::SceneName sceneName, bool active)
{
    int scene = static_cast<int>(sceneName);
    if(scene < 0 || m_scenes.size() <= scene) 
        throw std::exception("ERROR: Trying to reach invalid Scene!");
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
            m_scenes[i]->renderUI();
        }
    }
}

int SceneManager::gameLoop()
{
    try
    {
        while(!m_window.ShouldClose())
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
