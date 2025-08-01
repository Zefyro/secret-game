#include "player.hpp"
#include <raylib.h>

void Player::update()
{
	float movement_speed = 500.0f;
	float jump_velocity = 50.0f;
	float gravity = 9.81f * 20;
	if (IsKeyDown(KEY_A)) {
		position.x -= movement_speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_D)) {
		position.x += movement_speed * GetFrameTime();
	}
	if (IsKeyPressed(KEY_W)) {
		position.y -= jump_velocity;
	}
	position.y += gravity * GetFrameTime();
}
