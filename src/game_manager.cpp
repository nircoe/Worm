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
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

GameManager::GameManager(std::initializer_list<Scene *> scenes) : m_window(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT, Consts::GAME_NAME),
                                                                  m_camera(raylib::Vector2::Zero(), raylib::Vector2::Zero()),
                                                                  m_font(Consts::FONT_PATH, 80),
                                                                  m_iconImage(Consts::ICON_IMAGE_PATH)
{
    m_window.SetTargetFPS(static_cast<int>(Enums::Difficulty::Easy));
    m_window.SetIcon(m_iconImage);

    if (!soundcoe::initialize("assets/audio"))
    {
        TraceLog(LOG_ERROR, "soundcoe failed to initialize!");
        fflush(stdout);
        exit(-1);
    }

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

    m_music = soundcoe::fadeInMusic("calm-melody.mp3", 1.0f, 0.45f);
    if (m_dataManager.init(getGameDataPath().string()))
        activateScene(Enums::SceneName::Home_Scene);
    else // failed to load, start new game
    {
        m_window.SetTargetFPS(60);
        activateScene(Enums::SceneName::New_Game_Scene);
    }
    for (auto &scene : m_scenes)
    {
        if (scene->isActive())
            scene->initUI(*this);
    }
}

GameManager::~GameManager()
{
    soundcoe::shutdown();
}

void GameManager::activateScene(Enums::SceneName sceneName)
{
    setSceneActive(sceneName, true);
    if (sceneName == Enums::SceneName::Game_Scene)
    {
        HomeScene *homeScene = static_cast<HomeScene *>(m_scenes[static_cast<std::size_t>(Enums::SceneName::Home_Scene)]);
        Enums::Difficulty difficulty = homeScene->getDifficulty();
        GameScene *gameScene = static_cast<GameScene *>(m_scenes[static_cast<std::size_t>(sceneName)]);
        gameScene->changeDifficulty(difficulty);
    }
    m_scenes[static_cast<std::size_t>(sceneName)]->initUI(*this);
    loadSceneAudio(sceneName);
}

void GameManager::deactivateScene(Enums::SceneName sceneName)
{
    setSceneActive(sceneName, false);
    unloadSceneAudio(sceneName);
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
    std::size_t scene = static_cast<std::size_t>(sceneName);
    if (m_scenes.size() <= scene)
    {
        std::cerr << "Error: Invalid Scene Name" << std::endl;
        closeGame();
        return;
    }
    m_scenes[scene]->setActive(active);
    m_activeScenes.set(scene, active);
}

bool GameManager::loadSceneAudio(Enums::SceneName sceneName)
{
    switch (sceneName)
    {
    case Enums::SceneName::New_Game_Scene:
        return soundcoe::preloadScene("new_game_scene");
    case Enums::SceneName::Home_Scene:
        return soundcoe::preloadScene("home_scene");
    case Enums::SceneName::Game_Scene:
        return soundcoe::preloadScene("game_scene");
    }
    return false;
}

bool GameManager::unloadSceneAudio(Enums::SceneName sceneName)
{
    switch (sceneName)
    {
    case Enums::SceneName::New_Game_Scene:
        return soundcoe::unloadScene("new_game_scene");
    case Enums::SceneName::Home_Scene:
        return soundcoe::unloadScene("home_scene");
    case Enums::SceneName::Game_Scene:
        return soundcoe::unloadScene("game_scene");
    }
    return false;
}

std::filesystem::path GameManager::getGameDataPath()
{
    std::filesystem::path path = std::filesystem::path(GetApplicationDirectory());
    path /= "savedata";

    if (!std::filesystem::exists(path))
        std::filesystem::create_directory(path);

    return path / "gamedata.bin";
}

void GameManager::update()
{
    for (auto scene : m_scenes)
    {
        if (scene->isActive())
            scene->update(*this);
    }

    soundcoe::update();
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
            scene->renderUI(m_camera);
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

void GameManager::newGame(const std::string &nickname)
{
    m_dataManager.newGame(nickname);
    m_dataManager.saveGame();
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

void GameManager::setMusicHandle(soundcoe::MusicHandle handle)
{
    m_music = handle;
}

soundcoe::MusicHandle GameManager::getMusicHandle() const
{
    return m_music;
}

int GameManager::gameLoop()
{
    try
    {
        while (!m_window.ShouldClose())
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

            if (m_shouldClose)
                m_window.Close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    soundcoe::playSound("bye.mp3");
    std::this_thread::sleep_for(1s);

    return 0; // Success
}
