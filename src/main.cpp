#include "game.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"

#include <raylib.h>

constexpr struct {
	int x, y;
} BaseResolution{640, 360};

int main()
{
	InitWindow(BaseResolution.x, BaseResolution.y, "GMTK-2025");
	SetTargetFPS(0);

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
