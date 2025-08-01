#include "level.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"

constexpr struct {
	int x, y;
} TileSize = {32, 32};

#include <stdexcept>
#include <string>

ILevel::ILevel() {}

void ILevel::draw() const
{
	int tile_x = 0, tile_y = 0;
	for (char ch : get_level_data()) {
		int draw_x = tile_x * TileSize.x;
		int draw_y = tile_y * TileSize.y;

		switch (ch) {
			case '.': {
				break;
			}
			case '#': {
				DrawTexture(TextureCache::load("./imgs/block.png"), draw_x, draw_y, WHITE);
				break;
			}
			// We know that new line as the separator for lines is slow,
			// than using a fix-sized array, but this is easier to prototype with :^)
			case '\n': {
				tile_x = 0;
				tile_y++;
				continue;
			}

			default:
				throw std::runtime_error(std::string("invalid character! '") + ch + "'!");
		}

		tile_x++;
	}
}
