#pragma once
#include <raylib.h>
#include <string_view>

class Player;

enum class Tile : char { AIR = '.', BLOCK = '#' };

class ILevel {
public:
	void draw() const;

	virtual ~ILevel() {};
	virtual void update(const Player& player) = 0;

	// Only returns the first tile that is being overlapped with!
	// Returns AIR tile if no other tile is being overlapped!
	Tile get_overlapping_tile(Rectangle rect) const;

protected:
	virtual std::string_view get_level_data() const = 0;

	ILevel();
};
