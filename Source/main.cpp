#pragma once
#include "sdl.h"
#include "components.h"
#include "entity.h"
#include "systems.h"

int main(int argc, char* argv[]) {
	
	using namespace ComponentMask;

	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Entity Components", 100,100 ,400,400, SDL_WINDOW_SHOWN );
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	std::vector<Entity*> entityArray;

	RenderSystem rendering;
	MovementSystem movement;
	ControllSystem control;
	CollisionSystem collision;
	
	SDL_Rect rect; rect.w = 70; rect.h = 70;
	SDL_Color color = {255,255,255};
	
	Entity box;
	box.AddComponent(POSITION | RENDERER_PRIMITIVE);
	box.SetPrimitive(rect);
	box.renderTarget = rect;
	box.controllSpeed = 0.5f;
	//box.texture.loadFromRenderedText(renderer, TTF_OpenFont("aller.ttf", 30), "", color);
	box.position = vec2(100, 100);
	box.primitiveColor = rgba(255, 255, 255, 1);
	box.boundingBox = rect;
	box.acceleration.x = 0;
	entityArray.push_back(&box);

	rect.w = 100; rect.h = 100;
	Entity box2;
	box2.AddComponent(POSITION | VELOCITY | ACCELERATION | RENDERER_PRIMITIVE);
	box2.SetPrimitive(rect);
	box2.texture.loadFromFile(renderer, "mfw.PNG");
	box2.renderTarget = rect;
	box2.boundingBox = rect;
	box2.position = vec2(300, 140);
	box2.controllSpeed = 0.1f;
	box2.primitiveColor = rgba(0, 255, 0, 1);
	box2.acceleration.x = -0.0;
	box2.velocity.y = 0.0;
	box2.velocity.x = -0.3;
	box2.angle = 30;
	entityArray.push_back(&box2);

	rect.w = 30;
	rect.h = 30;

	Entity player;
	player.AddComponent(POSITION | VELOCITY | CONTROLLER_KEYBOARD | RENDERER_PRIMITIVE | COLLISION_DETECTOR_AXALIGN | COLLISON_RESOLVER);
	player.SetPrimitive(rect);
	player.texture.loadFromFile(renderer, "devil.png");
	/*rect.w = player.texture.getWidth();
	rect.h = player.texture.getHeight();*/
	player.renderTarget = rect;
	player.boundingBox = rect;
	player.position = vec2(100, 200);
	player.primitiveColor = rgba(255, 0, 0, 1);
	player.controllSpeed = 0.5f;
	entityArray.push_back(&player);

	SDL_Event* event = new SDL_Event();

	const Uint8* keyboard;

	
	while (!quit) {
		
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
				else if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					quit = true;
				}
			}

			
		}

		player.angle += 10;

		//CONTROLLTEST
		control.update(event, entityArray);

		//box.texture.loadFromRenderedText(renderer, TTF_OpenFont("aller.ttf", 15), std::to_string((int)box2.velocity.x), color);

		//UPDATETEST
		movement.update(entityArray, 1.f);

		//COLLISIONTEST
		collision.update(entityArray);

		//RENDERTEST
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);

		rendering.update(renderer, entityArray);

		SDL_RenderPresent(renderer);

	}
	return 0;

}