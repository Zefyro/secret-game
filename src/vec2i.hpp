#pragma once

struct Vec2i {
public:
	int x = 0, y = 0;
};

inline Vec2i operator+(Vec2i lh, Vec2i rh)
{
	return Vec2i{lh.x + rh.x, lh.y + rh.y};
}