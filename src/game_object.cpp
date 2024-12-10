#include "game_object.hpp"

unsigned int GameObject::s_idCounter = 0; // Initialize the static ID counter

GameObject::GameObject(raylib::Vector2 initialPosition) : m_id(++s_idCounter), m_transform(initialPosition), m_isActive(true) { }

void GameObject::setActive(bool active) { m_isActive = active; }

unsigned int GameObject::getId() const { return m_id; }

Transform2D& GameObject::getTransform() { return m_transform; }

const Transform2D& GameObject::getTransform() const { return m_transform; }

const bool GameObject::isActive() const { return m_isActive; }
