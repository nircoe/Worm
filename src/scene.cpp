#include "scene.hpp"

Scene::Scene(bool active) : m_isActive(active) { }

void Scene::initUI(const raylib::Font & /*font*/) { }

bool Scene::isActive() const { return this->m_isActive; }

void Scene::setActive(bool active) { this->m_isActive = active; }
