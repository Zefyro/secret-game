#pragma once
#include "player.hpp"

struct Game {
	Player player;

public:
	void update();
	void draw();
};
