#include "player.hpp"
#include "game.hpp"
#include "level.hpp"

#include "systems/texture_cacher.hpp"

#include <raylib.h>

Rectangle Player::get_as_rectangle() const
{
	return Rectangle{position.x, position.y, size.x, size.y};
}

void Player::update(const LevelBase& level)
{
	constexpr float ground_accelration = 204.0f;
	constexpr float ground_deacceleration = 0.18f;
	constexpr float jump_velocity = 4.2f;
	constexpr float gravity = 9.81f;

	const float delta = GetFrameTime();
	velocity.y += gravity * delta;

	if (IsKeyDown(KEY_A)) {
		velocity.x = -ground_accelration * delta;
	}
	if (IsKeyDown(KEY_D)) {
		velocity.x = ground_accelration * delta;
	}
	if (IsKeyPressed(KEY_W)) {
		velocity.y = -jump_velocity;
	}

	// Wrapping
	if (position.y >= BaseResolution.y) {
		position.y = 0;
	}
	if (position.y <= 0) {
		position.y = (float)BaseResolution.y;
	}
	if (position.x > BaseResolution.x) {
		position.x = 0;
	}
	if (position.x < 0) {
		position.x = (float)BaseResolution.x;
	}

	velocity.x = lerp(velocity.x, 0.0f, ground_deacceleration);

	move_and_slide(level);
}

void Player::move_and_slide(const LevelBase& level)
{
	// Move in x-axis first, then resolve a possible collision.
	// Then move in y-axis, resolve the possible collision.
	position.x += velocity.x;
	if (position.x != 0.0f) {
		auto tile_collision = level.get_overlapping_tile(get_as_rectangle());
		if (tile_collision.first != Tile::AIR) {
			float collision_x =
				static_cast<float>(tile_collision.second.x * TileSize.x);
			if (velocity.x > 0.0f) {
				position.x = collision_x - size.x;
			}
			if (velocity.x < 0.0f) {
				position.x = collision_x + TileSize.x;
			}
			velocity.x = 0.0f;
		}
	}

	position.y += velocity.y;
	if (position.y != 0.0f) {
		auto tile_collision = level.get_overlapping_tile(get_as_rectangle());
		if (tile_collision.first != Tile::AIR) {
			float collision_y =
				static_cast<float>(tile_collision.second.y * TileSize.y);
			if (velocity.y > 0.0f) {
				position.y = collision_y - size.y;
			}
			if (velocity.y < 0.0f) {
				position.y = collision_y + TileSize.y;
			}
			velocity.y = 0.0f;
		}
	}
}

void Player::draw() const
{
	DrawTextureV(TextureCache::load("./imgs/block.png"), position, BLUE);
}
