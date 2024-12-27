#pragma once
#include <array>
#include "scene.hpp"
#include "auxiliary/consts.hpp"

class SceneManager 
{
    std::array<Scene&, Consts::NAME_OF_SCENES> scenes;

public:
    SceneManager();
    ~SceneManager();
    
    void update();
    void render();
};