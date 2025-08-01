#include "level.hpp"
#include "player.hpp"
#include "systems/texture_cacher.hpp"
#include "vec2i.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

constexpr Vec2i TileSize = {32, 32};
constexpr Vec2i TileDimensions = {20, 10};

Vec2i Vec2i::world_pos_from_loc(size_t index)
{
	const int tiled_x = static_cast<int>(index % TileSize.x);
	const int tiled_y = static_cast<int>(index / TileSize.y);
	return Vec2i{tiled_x, tiled_y} * TileSize;
}

static std::optional<Texture2D> get_texture_for_tile(Tile tile)
{
	switch (tile) {
		case Tile::BLOCK: {
			return TextureCache::load("./imgs/block.png");
		}
		case Tile::SPIKE: {
			return TextureCache::load("./imgs/spike.png");
		}
		case Tile::GOAL: {
			return TextureCache::load("./imgs/goal.png");
		}
		case Tile::SPAWN:
		case Tile::AIR: {
			return std::optional<Texture2D>{};
		}
	}

	throw std::runtime_error("invalid character!");
}

static bool is_tile_solid(Tile tile)
{
	switch (tile) {
		case Tile::BLOCK:
		case Tile::SPIKE:
			return true;
		case Tile::GOAL:
		case Tile::SPAWN:
		case Tile::AIR:
			return false;
	}

	throw std::runtime_error("invalid character!");
}

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
			// @TODO: screen wrapping
			int level_index = tile_index + offx + (offy * TileDimensions.x);
			if (level_index >= (TileDimensions.x * TileDimensions.y)) {
				continue;
			}
			if (level_index < 0) {
				continue;
			}

			const Tile current_tile =
				static_cast<Tile>(level_data[level_index]);
			if (!is_tile_solid(current_tile)) {
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

Vec2i LevelBase::get_player_spawn_tile() const
{
	const std::string_view level_data = get_level_data();
	auto spawn_location = std::find_if(
		std::begin(level_data), std::end(level_data), [&level_data](char ch) {
			return ch == static_cast<char>(Tile::SPAWN);
		}
	);

	if (spawn_location == std::end(level_data)) {
		throw std::runtime_error("no spawn location defined!");
	}

	const size_t index = std::distance(std::begin(level_data), spawn_location);
	return Vec2i::world_pos_from_loc(index);
}

void LevelBase::draw() const { draw_level(); }

void LevelBase::draw_level() const
{
	const std::string_view level_data = get_level_data();
	for (int i = 0; i < (TileDimensions.x * TileDimensions.y); i++) {
		char ch = level_data[i];

		int draw_x = (i % TileDimensions.x) * TileSize.x;
		int draw_y = (i / TileDimensions.x) * TileSize.y;

		if (auto texture = get_texture_for_tile(static_cast<Tile>(ch))) {
			DrawTexture(texture.value(), draw_x, draw_y, WHITE);
		}
	}
}
