#pragma once
#include <raylib.h>

class Player {
public:
	void update();
	void draw() const;

public:
	Vector2 position{500, 300};
	Vector2 size{30, 30};
	bool onGround{true};
};
