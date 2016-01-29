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
		CONTROLLER_INPUT = 1 << 4,
		RENDERER_PRIMITIVE = 1 << 5,
		RENDERER_TEXTURE = 1 << 6
	};
}

