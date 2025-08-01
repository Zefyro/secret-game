#include "game.hpp"
#include "level.hpp"
#include "levels/level1.hpp"
#include "player.hpp"

#include <raylib.h>

Game::Game()
{
	current_level = std::make_unique<Level1>();
	player.position = current_level->get_player_spawn_tile();
}

Game::~Game() = default;

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
