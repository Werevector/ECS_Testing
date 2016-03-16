#pragma once
#include <vector>
#include "entity.h"

namespace SystemMask {
	enum {
		NONE = 0,
		MOVEMENT = 1,
		PLAYABLE = 1 << 2,
		RENDER = 1 << 3
	};
}

class System {
	virtual bool update() { return true; }
};

/**
System for handling movement of objects, should probably be fixed so that
one does not have to add all 3 components (add some common movement module)
**/
class MovementSystem {
public:
	MovementSystem() {};
	bool update(std::vector<Entity*> entities, float delta);
};

class RenderSystem{
public:
	bool update(SDL_Renderer* renderer, std::vector<Entity*> entities);
};

class ControllSystem {
public:
	bool update(SDL_Event* sdl_Event, std::vector<Entity*> entities);
private:
};

class CollisionSystem {
public:
	bool update(std::vector<Entity*> entities);

};

class CollisionResolver {
public:
	static void resolveRectCollide(Entity* entA, Entity* entB, SDL_Rect* intersection);
	static Direction findDirectionFromIntersect(Entity* ent, SDL_Rect* intersection);
};