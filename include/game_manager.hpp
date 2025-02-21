#pragma once

#include <array>
#include <bitset>
#include <initializer_list>
#include "auxiliary/enums.hpp"
#include "auxiliary/consts.hpp"

class Scene;

namespace raylib { class Window; class Camera2D; }

class GameManager 
{
    raylib::Window m_window;
    int m_targetFPS;
    raylib::Camera2D m_camera;
    std::array<Scene*, Consts::NUM_OF_SCENES> m_scenes;
    std::bitset<Consts::NUM_OF_SCENES> m_activeScenes;
    raylib::Font m_font;
    const raylib::Image m_iconImage;
    bool m_shouldClose = false;

    void setSceneActive(Enums::SceneName sceneName, bool active = true);

public:
    GameManager(std::initializer_list<Scene*> scenes);
    ~GameManager() = default;
    
    void activateScene(Enums::SceneName sceneName);
    void deactivateScene(Enums::SceneName sceneName);
    void closeGame();
    void changeDifficulty(Enums::Difficulty newDifficulty);

    void update();
    void render();
    void renderUI();

    const raylib::Font& getFont();

    void moveCamera(raylib::Vector2 velocity);

    const raylib::Vector2 getCameraTarget() const;

    void resetCamera();

    int gameLoop();
};