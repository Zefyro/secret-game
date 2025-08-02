#pragma once
#include <raylib.h>

struct Vec2i {
public:
	int x = 0, y = 0;

	// Turn a level index into world x,y coordinates.
	static Vec2i world_pos_from_loc(size_t index);

	constexpr operator Vector2() const
	{
		return Vector2{static_cast<float>(x), static_cast<float>(y)};
	}
};

constexpr Vec2i operator+(Vec2i lh, Vec2i rh)
{
	return Vec2i{lh.x + rh.x, lh.y + rh.y};
}

constexpr Vec2i operator-(Vec2i lh, Vec2i rh)
{
	return Vec2i{lh.x - rh.x, lh.y - rh.y};
}

constexpr Vec2i operator*(Vec2i lh, Vec2i rh)
{
	return Vec2i{lh.x * rh.x, lh.y * rh.y};
}

constexpr Vec2i operator*(Vec2i lh, int rh)
{
	return Vec2i{lh.x * rh, lh.y * rh};
}

constexpr Vector2 operator+(Vector2 lh, Vector2 rh)
{
	return Vector2{lh.x + rh.x, lh.y + rh.y};
}

constexpr Vector2 operator-(Vector2 lh, Vector2 rh)
{
	return Vector2{lh.x - rh.x, lh.y - rh.y};
}

constexpr Vector2 operator*(Vector2 lh, Vector2 rh)
{
	return Vector2{lh.x * rh.x, lh.y * rh.y};
}

constexpr Vector2 operator*(Vector2 lh, float rh)
{
	return Vector2{lh.x * rh, lh.y * rh};
}

template <typename T>
constexpr float lerp(const T& initial, const T& target, float time)
{
	return initial + time * (target - initial);
}
