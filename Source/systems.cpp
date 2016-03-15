#include "systems.h"

bool MovementSystem::update(std::vector<Entity*> entities, float delta) {
	bool success = true;

	bool hasPos;
	bool hasVel;
	bool hasAcc;
	bool hasGrav;

	std::vector<Entity*>::iterator entity;
	for (entity = entities.begin(); entity != entities.end(); entity++) {
		hasPos = (*entity)->HasComponent(ComponentMask::POSITION);
		hasVel = (*entity)->HasComponent(ComponentMask::VELOCITY);
		hasAcc = (*entity)->HasComponent(ComponentMask::ACCELERATION);
		hasGrav = (*entity)->HasComponent(ComponentMask::GRAVITY);

		if (hasPos) {
			if (hasAcc) {

				if (hasGrav) {
					(*entity)->velocity.y += 0.3;
				}

				(*entity)->velocity.x += (*entity)->acceleration.x;
				(*entity)->velocity.y += (*entity)->acceleration.y;
			}
			if (hasVel) {
				(*entity)->position.x += (*entity)->velocity.x * delta;
				(*entity)->position.y += (*entity)->velocity.y * delta;
			}
		}
		else
			success = false;
	}
	return success;
}

bool RenderSystem::update(SDL_Renderer* renderer, std::vector<Entity*> entities) {
	bool success = true;

	std::vector<Entity*>::iterator entity;
	for (entity = entities.begin(); entity != entities.end(); entity++) {
		
		//Store Component Checks
		bool renderPrim = (*entity)->HasComponent(ComponentMask::RENDERER_PRIMITIVE);
		bool renderTex = (*entity)->HasComponent(ComponentMask::RENDERER_TEXTURE);
		bool hasPos = (*entity)->HasComponent(ComponentMask::POSITION);

		if (renderTex) {
			(*entity)->texture.renderALTER(
				renderer,
				(*entity)->position.x,
				(*entity)->position.y,
				NULL,
				&(*entity)->renderTarget,
				(*entity)->angle
				);
		}
		else if (renderPrim) {

			if (hasPos) {
				(*entity)->primitive.x = (*entity)->position.x;
				(*entity)->primitive.y = (*entity)->position.y;
			}

			rgba color = (*entity)->primitiveColor;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(renderer, &((*entity)->primitive));
		}
		else {
			success = false;
		}

	}
	return success;
}

bool ControllSystem::update(SDL_Event* sdl_Event, std::vector<Entity*> entities){
	bool success = true;

	std::vector<Entity*>::iterator entity;
	for (entity = entities.begin(); entity != entities.end(); entity++) {
		bool hasKeyBoardControll = (*entity)->HasComponent(ComponentMask::CONTROLLER_KEYBOARD);

		const Uint8* keyboard;

		if (hasKeyBoardControll) {
			keyboard = SDL_GetKeyboardState(NULL);

			if (keyboard[SDL_SCANCODE_W]) {
				(*entity)->velocity.y -= (*entity)->controllSpeed;
			}
			if (keyboard[SDL_SCANCODE_S]) {
				(*entity)->velocity.y += (*entity)->controllSpeed;
			}
			if (keyboard[SDL_SCANCODE_A]) {
				(*entity)->velocity.x -= (*entity)->controllSpeed;
			}
			if (keyboard[SDL_SCANCODE_D]) {
				(*entity)->velocity.x += (*entity)->controllSpeed;
			}

		}

	}
	return success;
}

bool CollisionSystem::update(std::vector<Entity*> entities) {
	for (int i = 0; i < entities.size()-1; i++) {
		
		Entity* entity = entities[i];
		bool hasDetect = entity->HasComponent(ComponentMask::COLLISION_DETECTOR_AXALIGN);
		bool hasResolver = entity->HasComponent(ComponentMask::COLLISON_RESOLVER);

		if (hasDetect) {
			for (int i2 = i + 1; i2 < entities.size(); i2++ ) {
				SDL_Rect result;
				

				if (SDL_IntersectRect(&(entity->boundingBox),
					&(entities[i2]->boundingBox),
					&result) == SDL_TRUE) 
				{
					
				}
			}
		}
	}
}

bool CollisionResolver::resolveRectCollide(Entity * entA, Entity * entB, SDL_Rect* intersection)
{
	;
}
