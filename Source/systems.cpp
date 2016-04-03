#include "systems.h"

bool MovementSystem::update(std::vector<Entity*> entities, float delta) {
	bool success = true;

	bool hasPos;
	bool hasVel;
	bool hasAcc;
	bool hasGrav;


	for (Entity* entity : entities) {
		hasPos = entity->HasComponent(ComponentMask::POSITION);
		hasVel = entity->HasComponent(ComponentMask::VELOCITY);
		hasAcc = entity->HasComponent(ComponentMask::ACCELERATION);
		hasGrav = entity->HasComponent(ComponentMask::GRAVITY);

		if (hasPos) {
			if (hasAcc) {

				if (hasGrav) {
					if (entity->grounded)
						entity->velocity.y += 60;
					else
						entity->velocity.y += 30;
				}

				entity->velocity.x += entity->acceleration.x;
				entity->velocity.y += entity->acceleration.y;
			}
			if (hasVel) {
				entity->position.x += entity->velocity.x * delta;
				entity->position.y += entity->velocity.y * delta;
			}
		}
		else
			success = false;

		
		entity->boundingBox.x = entity->position.x;
		entity->boundingBox.y = entity->position.y;

		entity->renderTarget.x = entity->position.x;
		entity->renderTarget.y = entity->position.y;

	}

	return success;
}

bool RenderSystem::update(SDL_Renderer* renderer, std::vector<Entity*> entities) {
	bool success = true;

	std::vector<Entity*>::iterator entity;
	for (Entity* entity : entities) {
		
		//Store Component Checks
		bool renderPrim = entity->HasComponent(ComponentMask::RENDERER_PRIMITIVE);
		bool renderTex = entity->HasComponent(ComponentMask::RENDERER_TEXTURE);
		bool animated = entity->HasComponent(ComponentMask::ANIMATION);
		bool hasPos = entity->HasComponent(ComponentMask::POSITION);

		if (renderTex) {
			renderTexture(entity, renderer);
		}
		else if (renderPrim) {

			if (hasPos) {
				entity->primitive.x = entity->position.x;
				entity->primitive.y = entity->position.y;
			}
			renderPrimitive(entity, renderer);
		
		}
		else if(animated) {
			renderAnimated(entity, renderer);
		}
		else {
			success = false;
		}

	}
	return success;
}

void RenderSystem::renderPrimitive(Entity * entity, SDL_Renderer* renderer)
{
	rgba color = entity->primitiveColor;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &(entity->primitive));
}

void RenderSystem::renderTexture(Entity * entity, SDL_Renderer* renderer)
{
	entity->texture.renderALTER(
		renderer,
		entity->position.x,
		entity->position.y,
		NULL,
		&entity->renderTarget,
		entity->angle
		);
}

void RenderSystem::renderAnimated(Entity * entity, SDL_Renderer* renderer)
{

	stateCheck(entity);

	int x = entity->position.x;
	int y = entity->position.y;
	int key = entity->animation.GetAnimationKey();
	SDL_Rect target = entity->renderTarget;
	double angle = entity->angle;
	SDL_RendererFlip flip = entity->animation.flip;

	entity->spritesheet.renderSpriteAtKey(renderer, x, y ,key, &target, angle, flip);
}

void RenderSystem::stateCheck(Entity * entity)
{
	if (entity->movementState != EntityState::JUMP) {
		if (entity->stateChanged) {
			switch (entity->movementState) {
			case EntityState::IDLE:
				entity->animation.changeSequence("Idle");
				entity->animation.setTickPerUpdate(5);
				break;
			case EntityState::RUNNING:
				entity->animation.changeSequence("Running");
				entity->animation.setTickPerUpdate(10);
				break;
			case EntityState::WALKING:
				entity->animation.changeSequence("Walking");
				entity->animation.setTickPerUpdate(5);
				break;
			default:
				entity->animation.changeSequence("Idle");
				entity->animation.setTickPerUpdate(8);
				break;
			}
		}
	}
	else {
		if (entity->stateChanged) {
			entity->animation.changeSequence("Jump");
			entity->animation.setTickPerUpdate(1);
		}
	}
}

bool ControllSystem::update(SDL_Event* sdl_Event, std::vector<Entity*> entities){
	bool success = true;

	for (Entity* entity : entities) {
		entity->stateChanged = false;

		bool hasKeyBoardControll = entity->HasComponent(ComponentMask::CONTROLLER_KEYBOARD);
		bool hasPlatformerControlls = entity->HasComponent(ComponentMask::CONTROLLER_PLATFORMER);

		bool noInput = true;

		const Uint8* keyboard;

		if (hasKeyBoardControll) {
			keyboard = SDL_GetKeyboardState(NULL);

			if (keyboard[SDL_SCANCODE_X]) {
				if (entity->grounded) {
					
					if (entity->movementState != EntityState::JUMP) {
						entity->movementState = EntityState::JUMP;
						entity->stateChanged = true;
					}

					entity->velocity.y -= 700;
					entity->grounded = false;
				}

				noInput = false;
			}

			float maxvel = 100;

			if (keyboard[SDL_SCANCODE_A]) {
				
				entity->velocity.x -= entity->controllSpeed;
				if (entity->velocity.x <= -maxvel) entity->velocity.x = -maxvel;
				
				if (entity->movementState != EntityState::WALKING && entity->grounded) {
					entity->movementState = EntityState::WALKING;
					entity->stateChanged = true;
					
				}
				entity->animation.flip = SDL_FLIP_HORIZONTAL;
				noInput = false;
			}

			if (keyboard[SDL_SCANCODE_D]) {
				entity->velocity.x += entity->controllSpeed;
				if (entity->velocity.x >= maxvel) entity->velocity.x = maxvel;
				
				if (entity->movementState != EntityState::WALKING && entity->grounded) {
					entity->movementState = EntityState::WALKING;
					entity->stateChanged = true;
					
				}
				entity->animation.flip = SDL_FLIP_NONE;
				
				noInput = false;
			}

			if (noInput) {
				
				if (entity->movementState != EntityState::IDLE && entity->movementState != EntityState::JUMP) {
					entity->stateChanged = true;
					entity->movementState = EntityState::IDLE;
				}

				float deaxell = 0;
				if (entity->grounded)
					deaxell = 0.0;
				else
					deaxell = 0.0;

				if (entity->velocity.x > 0) {
					entity->velocity.x -= deaxell;
				}
				if (entity->velocity.x < 0) {
					entity->velocity.x += deaxell;
				}


				if ((entity->velocity.x < 0.01 || entity->velocity.x > -0.01) ) {
					if(entity->grounded) entity->velocity.x = 0;
				}
			}

		}

	}
	return success;
}

bool CollisionSystem::update(std::vector<Entity*> entities) {
	for (int i = 0; i < entities.size(); i++) {
		
		Entity* entity = entities[i];
		/*bool hasRequired = entity->HasComponent(
			ComponentMask::VELOCITY&&
			ComponentMask::ACCELERATION&&
			ComponentMask::POSITION
			);*/


		bool hasDetect = entity->HasComponent(ComponentMask::COLLISION_DETECTOR_AXALIGN);
		bool hasResolver = entity->HasComponent(ComponentMask::COLLISON_RESOLVER);
		bool isSolid = entity->HasComponent(ComponentMask::SOLID_FORM);
		bool opponentIsSolid = true;
		

		if (hasDetect) {

			entity->collidedGround = false;

			for (int i2 = 0; i2 < entities.size(); i2++ ) {
				SDL_Rect result;

				if (entities[i2]->HasComponent(ComponentMask::SOLID_FORM)) {

					if (!SDL_RectEquals(
						&(entity->boundingBox),
						&(entities[i2]->boundingBox))) {


						if (SDL_IntersectRect(&(entity->boundingBox),
							&(entities[i2]->boundingBox),
							&result) == SDL_TRUE)
						{
							if (hasResolver && isSolid)
								CollisionResolver::resolveRectCollide(
									entity,
									entities[i2],
									&result);
						}
					}
				}
			}
			if (!entity->collidedGround && entity->grounded) {
				entity->grounded = false;
				//cout << "no collision with ground";
			}
		}
	}
	return true;
}

void CollisionResolver::resolveRectCollide(Entity* entA, Entity* entB, SDL_Rect* intersection)
{
	Direction collDir = CollisionResolver::findDirectionFromIntersect(entA, intersection);
	switch(collDir) {
	
	case UP:
		entA->position.y += intersection->h;
		entA->velocity.y = 0;
		break;
		
	case DOWN:
		
		if ( ! entA->grounded) {
			entA->movementState = EntityState::IDLE;
			entA->stateChanged = true;
			entA->grounded = true;
		}

		entA->collidedGround = true;
		entA->position.y -= intersection->h;
		entA->velocity.y = 0;
		
		break;

	case LEFT:
		entA->position.x += intersection->w;
		entA->velocity.x = 0;
		break;

	case RIGHT:
		entA->position.x -= intersection->w;
		entA->velocity.x = 0;
		break;
	}

}

Direction CollisionResolver::findDirectionFromIntersect(Entity* ent, SDL_Rect* intersection)
{
	Direction collDir = Direction::UP;

	//Figure out the collision direction from intersection rectangle
	if (intersection->w < intersection->h)
		if (intersection->x > ent->boundingBox.x)
			collDir = Direction::RIGHT;
		else
			collDir = Direction::LEFT;
	else
		if (intersection->y > ent->boundingBox.y)
			collDir = Direction::DOWN;
		else
			collDir = Direction::UP;

	return collDir;
}

void AnimationSystem::update(std::vector<Entity*> entities)
{

	for (Entity* entity : entities) {
		
		bool hasPosition = entity->HasComponent(ComponentMask::POSITION);
		bool hasSheet = entity->HasComponent(ComponentMask::RENDERER_SHEET);
		bool hasAnimation = entity->HasComponent(ComponentMask::ANIMATION);
		bool hasRequired = hasPosition && hasSheet && hasAnimation;

		/*bool hasRequired = entity->HasComponent(
			ComponentMask::POSITION &&
			ComponentMask::RENDERER_SHEET &&
			ComponentMask::ANIMATION
			);*/

		if (hasRequired) {
			entity->animation.Tick();
		}
	}

}

void StateSystem::update(std::vector<Entity*> entities)
{

}

void StateSystem::checkMoveStates(std::vector<Entity*> entities)
{
	/*for(Entity* entity : entities)
	{
		switch (entity->movementState) {
		case EntityState::IDLE:
			s

		}
	}*/
}
