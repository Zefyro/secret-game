#pragma once
#include <raylib.h>

struct Player {
	Vector2 position{500, 300};
	Vector2 size{30, 30};
	bool onGround{true};
	void update();
};
