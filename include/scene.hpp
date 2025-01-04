#pragma once

class SceneManager;

class Scene 
{
    bool m_isActive;

public:
    Scene(bool active = true);
    ~Scene() = default;
    
    virtual void update(SceneManager& sceneManager) = 0;
    virtual void render() = 0;
    virtual void renderUI() = 0;

    const bool isActive() const;
    void setActive(bool active = true);
};
