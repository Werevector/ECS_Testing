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
		CONTROLLER_MOUSE = 1 << 8
	};
}