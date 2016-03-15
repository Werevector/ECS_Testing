#pragma once
#include "sdl.h"
#include "components.h"
#include "structures.h"
#include "Texture.h"

class Entity {
public:

	Entity() : mask(ComponentMask::NONE) {
		primitive.x = 0;
		primitive.y = 0;
		primitive.w = 0;
		primitive.h = 0;
	};

	void AddComponent(int mask);
	void RemoveComponent(int mask);
	void ToggleComponent(int mask);
	bool HasComponent(int mask);
	void SetPrimitive(SDL_Rect rect);

	vec2 position;
	vec2 velocity;
	vec2 acceleration;

	rgba primitiveColor = rgba();

	float controllSpeed = 0;
	
	SDL_Rect primitive;
	SDL_Rect renderTarget;
	Texture texture;
	float angle = 0.5;
	int health = 0;

	SDL_Rect boundingBox;

private:

	int mask;

};