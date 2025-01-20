#include "game_manager.hpp"
#include "scene.hpp"
#include "home_scene.hpp"
#include "game_scene.hpp"
#include "raylib-cpp.hpp"
#include <string>
#include "auxiliary/enums.hpp"
#include "auxiliary/colors.hpp"
#include <algorithm>
#include <iostream>
#include <exception>

GameManager::GameManager(std::initializer_list<Scene*> scenes) : 
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
            fflush(stdout);
            break;
        }
        m_scenes[i] = scene;
        m_scenes[i]->calculateTextsPositions(m_font);
        ++i;
    }
    m_activeScenes.set(0);
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
    if(scene < 0 || m_scenes.size() <= scene) 
        closeGame();
    m_activeScenes.set(scene, active);
}

void GameManager::update()
{
    for(std::size_t i = 0; i < Consts::NUM_OF_SCENES; ++i)
    {
        if(m_activeScenes.test(i))
        {
            m_scenes[i]->update(*this);
        }
    }
}

void GameManager::render()
{
    for(std::size_t i = 0; i < Consts::NUM_OF_SCENES; ++i)
    {
        if(m_activeScenes.test(i))
        {
            m_scenes[i]->render();
        }
    }
}

void GameManager::renderUI()
{
    for(std::size_t i = 0; i < Consts::NUM_OF_SCENES; ++i)
    {
        if(m_activeScenes.test(i))
        {
            m_scenes[i]->renderUI(m_font);
        }
    }
}

int GameManager::gameLoop()
{
    try
    {
        while(!m_shouldClose && !m_window.ShouldClose())
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
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0; // Success
}
