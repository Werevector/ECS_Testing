#pragma once
#include "sdl.h"
#include "components.h"
#include "entity.h"
#include "systems.h"
#include "metafilereader.h"
#include <vector>
#include "GameTimer.h"

int main(int argc, char* argv[]) {
	
	using namespace ComponentMask;

	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Entity Components", 400,400 ,1000,800, SDL_WINDOW_SHOWN );
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	std::vector<Entity*> entityArray;
	GameTimer timer;


	RenderSystem rendering;
	MovementSystem movement;
	ControllSystem control;
	CollisionSystem collision;
	AnimationSystem animation;
	
	SDL_Rect rect; rect.w = 300; rect.h = 300;
	SDL_Color color = {255,255,255};
	
	Entity box;
	box.AddComponent(
		POSITION |
		VELOCITY |
		ACCELERATION |
		RENDERER_PRIMITIVE |
		SOLID_FORM);

	box.SetPrimitive(rect);
	box.renderTarget = rect;
	box.controllSpeed = 0.5f;
	//box.texture.loadFromRenderedText(renderer, TTF_OpenFont("aller.ttf", 30), "", color);
	//box.texture.loadFromFile(renderer, "../resources/cirno.jpg");
	box.position = vec2(80, 300);
	box.primitiveColor = rgba(255, 255, 255, 1);
	box.boundingBox = rect;
	box.acceleration.x = 0;
	

	rect.w = 70; rect.h = 70;
	Entity box2;
	box2.AddComponent(
		POSITION			| 
		VELOCITY			| 
		ACCELERATION		| 
		RENDERER_TEXTURE	| 
		SOLID_FORM			|
		GRAVITY |
		COLLISION_DETECTOR_AXALIGN |
		COLLISON_RESOLVER
		);

	box2.SetPrimitive(rect);
	box2.texture.loadFromFile(renderer, "../resources/crate1.PNG");
	box2.renderTarget = rect;
	box2.boundingBox = rect;
	box2.position = vec2(290, 200);
	box2.controllSpeed = 10.f;
	box2.primitiveColor = rgba(0, 255, 0, 1);
	box2.acceleration.x = 0.0;
	box2.velocity.y = 0.0;
	box2.velocity.x = 0;
	box2.angle = 0;
	

	rect.w = 50;
	rect.h = 90;

	Entity player;
	player.AddComponent(
		POSITION					| 
		VELOCITY					| 
		ACCELERATION				|
		CONTROLLER_KEYBOARD			| 
		RENDERER_SHEET				|
		COLLISION_DETECTOR_AXALIGN	| 
		COLLISON_RESOLVER			| 
		SOLID_FORM					|
		ANIMATION					|
		GRAVITY
		);

	player.SetPrimitive(rect);
	player.spritesheet.loadSpriteSheet("../resources/character_sprite.png", "../resources/character_sprite.meta", renderer);
	player.animation.createTestAnimation();
	player.renderTarget = rect;
	rect.w = 40;
	player.boundingBox = rect;
	player.position = vec2(70, 200);
	player.primitiveColor = rgba(255, 0, 0, 1);
	player.controllSpeed = 100.f;

	entityArray.push_back(&box2);

	entityArray.push_back(&box);
	entityArray.push_back(&player);
	

	SDL_Event* event = new SDL_Event();

	const Uint8* keyboard;


	while (!quit) {
		
		timer.Tick();

		float delta = timer.DeltaTime();

		if (delta > 1) { delta = 0.f; }

		if (SDL_PollEvent(event)) {
			
			if (event->type == SDL_QUIT) { quit = true; }
			if (event->type == SDL_KEYUP) {
				if (event->key.keysym.scancode == SDL_SCANCODE_R) {
					box.ToggleComponent(RENDERER_PRIMITIVE);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_E) {
					box.ToggleComponent(ACCELERATION);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_C) {
					player.ToggleComponent(CONTROLLER_KEYBOARD);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_B) {
					player.animation.changeSequence("Running");
					player.animation.setTickPerUpdate(1);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_N) {
					player.animation.changeSequence("Jump");
					player.animation.setTickPerUpdate(4);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_M) {
					player.animation.changeSequence("Walking");
					player.animation.setTickPerUpdate(0);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_H) {
					player.animation.changeSequence("Dying");
					player.animation.setTickPerUpdate(0);
				}
				else if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					quit = true;
				}
			}

			
		}

		//player.angle += 10;

		//CONTROLLTEST
		control.update(event, entityArray);

		//box.texture.loadFromRenderedText(renderer, TTF_OpenFont("aller.ttf", 15), std::to_string((int)box2.velocity.x), color);

		//UPDATETEST
		movement.update(entityArray, delta);

		//COLLISIONTEST
		collision.update(entityArray);

		//ANIMATIONTEST
		animation.update(entityArray);

		std::cout << player.velocity.y <<"   " << delta << endl;

		//RENDERTEST
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);

		rendering.update(renderer, entityArray);

		SDL_RenderPresent(renderer);

	}
	return 0;

}