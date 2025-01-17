#include "scene.hpp"

Scene::Scene(bool active) : m_isActive(active) { }

void Scene::calculateTextsPositions(const raylib::Font &font) { }

const bool Scene::isActive() const { return this->m_isActive; }

void Scene::setActive(bool active) { this->m_isActive = active; }
