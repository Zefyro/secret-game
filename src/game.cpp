#include "game.hpp"
#include "player.hpp"
#include <raylib.h>

void Game::update() { player.update(); }
void Game::draw()
{
	ClearBackground(RAYWHITE);
	DrawFPS(80, 80);

	DrawRectangleV(player.position, player.size, DARKGRAY);
}