#pragma once

class Scene 
{
    bool m_isActive;

public:
    Scene(bool active = true);
    ~Scene() = default;
    
    virtual void update() = 0;
    virtual void render() = 0;

    const bool isActive() const;
    void setActive(bool active = true);
};
