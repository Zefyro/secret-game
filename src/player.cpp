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
	constexpr float ground_accelration = 74.0f;
	constexpr float ground_deacceleration = 0.18f;
	constexpr float ground_max_speed = 7.2f;

	constexpr float jump_initial_force = 5.25f;
	constexpr float jump_hold_force = 8.45f;
	constexpr float gravity = 19.4f;

	static_assert(gravity > jump_hold_force, "infinite jumping");

	const float delta = GetFrameTime();
	velocity.y += gravity * delta;

	update_grounded(level);
	update_timers();

	if (IsKeyDown(KEY_A)) {
		velocity.x -= ground_accelration * delta;
	}
	if (IsKeyDown(KEY_D)) {
		velocity.x += ground_accelration * delta;
	}
	if (m_JumpBufferTimer > 0.0f && m_CayoteTimer > 0.0f) {
		velocity.y = -jump_initial_force;
		m_CayoteTimer = 0.0f;
		m_JumpBufferTimer = 0.0f;
	}
	if (IsKeyDown(KEY_W) && velocity.y < 0.0f) {
		velocity.y -= jump_hold_force * delta;
	}

	// Cap speed
	if (std::abs(velocity.x) >= ground_max_speed) {
		const float sign = velocity.x / std::abs(velocity.x);
		velocity.x = ground_max_speed * sign;
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

void Player::update_grounded(const LevelBase& level)
{
	// Positioned 1 pixel under feet.
	const Rectangle grounded_hitbox = {
		position.x, position.y + size.y, size.x, 1
	};
	on_ground = level.get_overlapping_tile(grounded_hitbox).first != Tile::AIR;
}

void Player::update_timers()
{
	const float delta = GetFrameTime();

	m_CayoteTimer -= delta;
	m_JumpBufferTimer -= delta;

	if (on_ground) {
		constexpr float CayoteTime = 0.10f;
		m_CayoteTimer = CayoteTime;
	}
	if (IsKeyPressed(KEY_W)) {
		constexpr float JumpTime = 0.10f;
		m_JumpBufferTimer = JumpTime;
	}
}

void Player::draw() const
{
	DrawTextureV(TextureCache::load("./imgs/block.png"), position, BLUE);
}
