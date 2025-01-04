#pragma once

#include "scene.hpp"

class HomeScene : public Scene
{
public:
    HomeScene();

    ~HomeScene() = default;

    void update(SceneManager& sceneManager) override;
    void render() override;
    void renderUI() override;
};