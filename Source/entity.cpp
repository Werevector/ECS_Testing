#include "entity.h"

void Entity::AddComponent(int mask) {
	this->mask |= mask;
}

void Entity::RemoveComponent(int mask) {
	this->mask &= ~mask;
}

void Entity::ToggleComponent(int mask) {
	this->mask ^= mask;
}

bool Entity::HasComponent(int component) {
	return (mask & component) == component;
}

void Entity::SetPrimitive(SDL_Rect rect) {
	primitive = rect;
}