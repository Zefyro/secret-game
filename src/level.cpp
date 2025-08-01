#include "level.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"
#include "vec2i.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

constexpr Vec2i TileSize = {32, 32};
constexpr Vec2i TileDimensions = {20, 10};

LevelBase::LevelBase() {}

std::pair<Tile, Vec2i> LevelBase::get_overlapping_tile(Rectangle rect) const
{
	const std::string_view level_data = get_level_data();
	const auto [tile_index, rect_grid_position] =
		[&rect]() -> std::pair<int, Vec2i> {
		const int tiled_x = static_cast<int>(rect.x / TileSize.x);
		const int tiled_y = static_cast<int>(rect.y / TileSize.y);
		const int tile_index = tiled_y * TileDimensions.x + tiled_x;
		return std::pair{tile_index, Vec2i{tiled_x, tiled_y}};
	}();

	for (int offx = -1; offx <= 1; offx++) {
		for (int offy = -1; offy <= 1; offy++) {
			// @TODO: wrapping
			int level_index = tile_index + offx + (offy * TileDimensions.x);
			if (level_index >= (TileDimensions.x * TileDimensions.y)) {
				continue;
			}
			if (level_index < 0) {
				continue;
			}

			const Tile current_tile =
				static_cast<Tile>(level_data[level_index]);
			if (current_tile == Tile::AIR) {
				continue;
			}

			Rectangle hitbox = {
				static_cast<float>((rect_grid_position.x + offx) * TileSize.x),
				static_cast<float>((rect_grid_position.y + offy) * TileSize.y),
				static_cast<float>(TileSize.x),
				static_cast<float>(TileSize.y)
			};

			if (CheckCollisionRecs(rect, hitbox)) {
				return std::pair{
					current_tile, Vec2i{offx, offy} + rect_grid_position
				};
			}
		}
	}

	return std::pair{Tile::AIR, Vec2i{}};
}

void LevelBase::draw() const { draw_level(); }

Texture2D get_texture_for_tile(Tile tile)
{
	switch (tile) {
		case Tile::AIR: {
			throw std::runtime_error("No texture for tile 'AIR'");
		}
		case Tile::BLOCK: {
			return TextureCache::load("./imgs/block.png");
		}
		case Tile::SPIKE: {
			return TextureCache::load("./imgs/spike.png");
		}
	}

	throw std::runtime_error("invalid character!");
}

void LevelBase::draw_level() const
{
	const std::string_view level_data = get_level_data();
	for (int i = 0; i < (TileDimensions.x * TileDimensions.y); i++) {
		char ch = level_data[i];

		if (ch == '.') {
			continue;
		}

		int draw_x = (i % TileDimensions.x) * TileSize.x;
		int draw_y = (i / TileDimensions.x) * TileSize.y;

		Texture2D tile_texture = get_texture_for_tile(static_cast<Tile>(ch));
		DrawTexture(tile_texture, draw_x, draw_y, WHITE);
	}
}
