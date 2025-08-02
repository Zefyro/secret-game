#pragma once
#include <raylib.h>

class LevelBase;

class Player {
public:
	void update(const LevelBase& level);
	void draw() const;

	Rectangle get_as_rectangle() const;

public:
	Vector2 position{500, 300};
	Vector2 velocity{0.0f, 0.0f};
	Vector2 size{30, 30};
	bool onGround{true};

private:
	void move_and_slide(const LevelBase& level);
};
