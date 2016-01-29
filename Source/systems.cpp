#include "systems.h"

bool MovementSystem::update(std::vector<Entity*> entities, float delta) {
	bool success = true;

	std::vector<Entity*>::iterator entity;
	for (entity = entities.begin(); entity != entities.end(); entity++) {
		bool hasPos = (*entity)->HasComponent(ComponentMask::POSITION);
		bool hasVel = (*entity)->HasComponent(ComponentMask::VELOCITY);
		bool hasAcc = (*entity)->HasComponent(ComponentMask::ACCELERATION);

		if (hasPos) {
			if (hasAcc) {
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
		bool renderPrim = (*entity)->HasComponent(ComponentMask::RENDERER_PRIMITIVE);
		bool renderTex = (*entity)->HasComponent(ComponentMask::RENDERER_TEXTURE);
		bool hasPos = (*entity)->HasComponent(ComponentMask::POSITION);

		if (renderTex) {
			//NO TEXTURE SUPPORT
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