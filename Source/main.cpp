#pragma once
#include "sdl.h"
#include "components.h"
#include "entity.h"
#include "systems.h"

int main(int argc, char* argv[]) {
	
	using namespace ComponentMask;

	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Entity Components", 100,100 ,400,400, SDL_WINDOW_SHOWN );
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	std::vector<Entity*> entityArray;

	RenderSystem rendering;
	MovementSystem movement;

	
	
	
	SDL_Rect rect; rect.w = 20; rect.h = 20;

	Entity box;
	box.AddComponent(POSITION | VELOCITY | ACCELERATION | RENDERER_PRIMITIVE);
	box.SetPrimitive(rect);
	box.position = vec2(50, 50);
	box.primitiveColor = rgba(255, 255, 255, 1);
	box.acceleration.x = 0.01;
	entityArray.push_back(&box);

	Entity box2;
	box2.AddComponent(POSITION | VELOCITY | RENDERER_PRIMITIVE);
	box2.SetPrimitive(rect);
	box2.position = vec2(50, 90);
	box2.primitiveColor = rgba(255, 255, 0, 1);
	box2.acceleration.y = 0.01;
	entityArray.push_back(&box2);

	SDL_Event* event = new SDL_Event();;

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
			}
		}
		
		//UPDATETEST
		movement.update(entityArray, 1.f);

		//RENDERTEST
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);

		rendering.update(renderer, entityArray);

		SDL_RenderPresent(renderer);

	}
	return 0;

}