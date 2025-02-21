#include "game_object.hpp"

GameObject::GameObject(raylib::Vector2 initialPosition) : m_transform(initialPosition), m_isActive(true) { }

void GameObject::setActive(bool active) { m_isActive = active; }

Transform2D& GameObject::getTransform() { return m_transform; }

const Transform2D& GameObject::getTransform() const { return m_transform; }

const bool GameObject::isActive() const { return m_isActive; }
