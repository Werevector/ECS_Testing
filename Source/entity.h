#pragma once
#include "sdl.h"
#include "components.h"
#include "structures.h"
#include "Texture.h"
#include "SpriteSheet.h"

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
	SpriteSheet spritesheet;
	float angle = 0.5;
	int health = 0;

	SDL_Rect boundingBox;

	Animation animation;

	EntityState::Movement movementState = EntityState::IDLE;
	bool stateChanged = false;
	bool grounded = false;
	bool collidedGround = false;

private:

	int mask;

};