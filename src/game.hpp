#pragma once
#include "player.hpp"
#include "vec2i.hpp"

#include <memory>

class LevelBase;

constexpr Vec2i BaseResolution{640, 360};

struct Game {
public:
	Game();
	~Game();

	Player player;
	std::unique_ptr<LevelBase> current_level;

public:
	void update();
	void draw();
};
