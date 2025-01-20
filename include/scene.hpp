#pragma once

class GameManager;

namespace raylib { class Font; }

class Scene 
{
    bool m_isActive;

public:
    Scene(bool active = true);
    ~Scene() = default;
    
    virtual void update(GameManager& gameManager) = 0;
    virtual void render() = 0;
    virtual void renderUI(const raylib::Font& font) = 0;
    
    virtual void calculateTextsPositions(const raylib::Font& font);

    const bool isActive() const;
    void setActive(bool active = true);
};
