#pragma once
#include "level.hpp"
#include "player.hpp"

#include <memory>

struct Game {
public:
	Game();

	Player player;
	std::unique_ptr<ILevel> current_level;

public:
	void update();
	void draw();
};
