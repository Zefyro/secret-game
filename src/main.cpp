#include "game.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"

#include <raylib.h>

int main()
{
	InitWindow(1280, 720, "GMTK-2025");
	SetTargetFPS(0);

	Game game;

	while (!WindowShouldClose()) {
		game.update();
		BeginDrawing();
		game.draw();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
