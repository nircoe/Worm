#pragma once

#include <array>
#include <bitset>
#include <initializer_list>
#include "auxiliary/enums.hpp"
#include "auxiliary/consts.hpp"

class Scene;

namespace raylib { class Window; class Camera2D; }

class SceneManager 
{
    raylib::Window m_window;
    int m_targetFPS;
    raylib::Camera2D m_camera;
    std::array<Scene*, Consts::NUM_OF_SCENES> m_scenes;
    std::bitset<Consts::NUM_OF_SCENES> m_activeScenes;

public:
    SceneManager(std::initializer_list<Scene*> scenes);
    ~SceneManager();
    
    void setSceneActive(Enums::SceneName sceneName, bool active = true);

    void update();
    void render();
    void renderUI();

    int gameLoop();
};