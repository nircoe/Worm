#include "scene.hpp"

Scene::Scene(bool active) : m_isActive(active) { }

const bool Scene::isActive() const
{
    return this->m_isActive;
}

void Scene::setActive(bool active)
{
    this->m_isActive = active;
}
