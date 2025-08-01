#include "player.hpp"
#include "game.hpp"
#include "systems/texture_cacher.hpp"
#include <raylib.h>

void Player::update()
{
	float movement_speed = 500.0f;
	float jump_velocity = 40.0f;
	float gravity = 9.81f * 1;
	if (IsKeyDown(KEY_A)) {
		velocity.x = -movement_speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_D)) {
		velocity.x = movement_speed * GetFrameTime();
	}
	if (IsKeyPressed(KEY_W)) {
		velocity.y -= jump_velocity;
	}

	if (!onGround) {
		velocity.y += gravity * GetFrameTime();
	}

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

	position.x += velocity.x;
	position.y += velocity.y;
	velocity.x *= 0.9f;
	velocity.y *= 0.2f;
}

void Player::draw() const { DrawTextureV(TextureCache::load("./imgs/block.png"), position, BLUE); }
