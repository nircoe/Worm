#pragma once

class Scene 
{
public:
    ~Scene() = default;
    
    virtual void update() = 0;
    virtual void render() = 0;
};
