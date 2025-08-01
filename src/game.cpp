#include "game.hpp"
#include "player.hpp"
#include <raylib.h>

Game::Game() { current_level = std::make_unique<Level1>(); }

void Game::update()
{
	current_level->update(player);
	player.update();
}

void Game::draw()
{
	ClearBackground(RAYWHITE);

	current_level->draw();
	player.draw();

	DrawFPS(80, 80);
}
