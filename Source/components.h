#pragma once
#include <bitset>
#include <string>
#include <iostream>

namespace ComponentMask {
	enum {
		NONE = 0,
		POSITION = 1,
		VELOCITY = 1 << 2,
		ACCELERATION = 1 << 3,
		GRAVITY = 1 << 4,
		RENDERER_PRIMITIVE = 1 << 5,
		RENDERER_TEXTURE = 1 << 6,
		CONTROLLER_KEYBOARD = 1 << 7,
		CONTROLLER_MOUSE = 1 << 8,
		HEALTH = 1 << 9,
		HEALTHBAR = 1 << 10,
		MOVEMENT_LEVEL_RESTRICTION = 1 << 11,
		OUTSIDE_BOUNDS_DESPAWN = 1 << 12,
		COLLISION_DETECTOR_AXALIGN = 1 << 13,
		COLLISON_RESOLVER = 1 << 14,
		SOLID_FORM = 1 << 15,
		PASS_THROUGH_FORM = 1 << 16,
		ANIMATION = 1 << 17,
		RENDERER_SHEET = 1 << 18,
		CONTROLLER_PLATFORMER = 1 << 19

	};
}