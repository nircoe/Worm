#pragma once

#include "raylib-cpp.hpp"

class GameManager;

class Scene 
{
    bool m_isActive;

protected:
    virtual raylib::Color checkButton(GameManager& gameManager, const raylib::Color &hoverColor, 
        const raylib::Color& clickedColor, int buttonId) = 0; 

public:
    Scene(bool active = true);
    ~Scene() = default;
    
    virtual void update(GameManager& gameManager) = 0;
    virtual void render() = 0;
    virtual void renderUI(const raylib::Font& font, const raylib::Camera2D& camera) = 0;
    
    virtual void initUI(const raylib::Font& font) = 0;

    const bool isActive() const;
    void setActive(bool active = true);
};
