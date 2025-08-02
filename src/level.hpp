#pragma once
#include <raylib.h>
#include <string_view>
#include <utility>

#include "vec2i.hpp"

class Player;

constexpr Vec2i TileSize = {32, 32};
constexpr Vec2i TileDimensions = {20, 10};

enum class Tile : char {
	AIR = '.',
	BLOCK = '#',
	SPAWN = 'S', // Air, marks the spawnspot for the player.
	SPIKE = 'A',
	GOAL = 'G'
};

class LevelBase {
public:
	virtual ~LevelBase() {};
	virtual void draw() const;
	virtual void update(const Player& player) = 0;

	// Only returns the first tile that is being overlapped with!
	// Returns AIR tile if no other tile is being overlapped!
	// The Vec2i returns the position of the collided block, IN 2D ARRAY SPACE!
	std::pair<Tile, Vec2i> get_overlapping_tile(Rectangle rect) const;
	Vec2i get_player_spawn_tile() const;

protected:
	void draw_level() const;
	virtual std::string_view get_level_data() const = 0;

	LevelBase();
};
