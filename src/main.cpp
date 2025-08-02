#include "game.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"

#include <raylib.h>

void update_zoom(Camera2D& cam)
{
	cam.zoom = GetRenderWidth() / static_cast<float>(BaseResolution.x);
}

int main()
{
	InitWindow(BaseResolution.x * 2, BaseResolution.y * 2, "GMTK-2025");

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	Game game;

	Camera2D camera{
		// Offset
		Vector2{0, 0},
		Vector2{0, 0},
		0.0f,
		1.0f
	};
	update_zoom(camera);

	while (!WindowShouldClose()) {
		if (IsWindowResized()) {
			update_zoom(camera);
		}

		game.update();
		BeginDrawing();
		BeginMode2D(camera);
		game.draw();
		EndMode2D();
		EndDrawing();
	}

	TextureCache::unload_all();

	CloseWindow();

	return 0;
}
