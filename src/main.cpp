#include "game.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"

#include <raylib.h>

int main()
{
	InitWindow(BaseResolution.x, BaseResolution.y, "GMTK-2025");
	SetTargetFPS(60);

	Game game;

	while (!WindowShouldClose()) {
		game.update();
		BeginDrawing();
		game.draw();
		EndDrawing();
	}

	TextureCache::unload_all();

	CloseWindow();

	return 0;
}
