#pragma once

#include <array>
#include <bitset>
#include <initializer_list>
#include <filesystem>
#include <datacoe/data_manager.hpp>
#include "auxiliary/enums.hpp"
#include "auxiliary/consts.hpp"
#include <soundcoe.hpp>

class Scene;

namespace raylib
{
    class Window;
    class Camera2D;
}

class GameManager
{
    datacoe::DataManager m_dataManager;
    raylib::Window m_window;
    int m_targetFPS;
    raylib::Camera2D m_camera;
    std::array<Scene *, Consts::NUM_OF_SCENES> m_scenes;
    std::bitset<Consts::NUM_OF_SCENES> m_activeScenes;
    raylib::Font m_font;
    const raylib::Image m_iconImage;
    bool m_shouldClose = false;
    soundcoe::MusicHandle m_music = soundcoe::INVALID_MUSIC_HANDLE;

    void setSceneActive(Enums::SceneName sceneName, bool active = true);
    bool loadSceneAudio(Enums::SceneName sceneName);
    bool unloadSceneAudio(Enums::SceneName sceneName);

    static std::filesystem::path getGameDataPath();

public:
    GameManager(std::initializer_list<Scene *> scenes);
    ~GameManager();

    void activateScene(Enums::SceneName sceneName);
    void deactivateScene(Enums::SceneName sceneName);
    void closeGame();
    void changeDifficulty(Enums::Difficulty newDifficulty);

    void update();
    void render();
    void renderUI();

    const raylib::Font &getFont() const;

    void moveCamera(raylib::Vector2 velocity);

    const raylib::Vector2 getCameraTarget() const;

    void resetCamera();

    void newGame(const std::string &nickname = "");

    const datacoe::GameData getGamedata() const;
    bool saveGame(const datacoe::GameData &data);

    void setMusicHandle(soundcoe::MusicHandle handle);
    soundcoe::MusicHandle getMusicHandle() const;

    int gameLoop();
};