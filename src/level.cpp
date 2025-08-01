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
	const std::string_view level_data = get_level_data();
	for (int i = 0; i < (TileDimensions.x * TileDimensions.y); i++) {
		char ch = level_data[i];
		int draw_x = (i % TileDimensions.x) * TileSize.x;
		int draw_y = (i / TileDimensions.x) * TileSize.y;

		switch (ch) {
			case '.': {
				break;
			}
			case '#': {
				DrawTexture(
					TextureCache::load("./imgs/block.png"),
					draw_x,
					draw_y,
					WHITE
				);
				break;
			}

			default:
				throw std::runtime_error(
					std::string("invalid character! '") + ch + "'!"
				);
		}
	}
}
