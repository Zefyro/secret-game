#pragma once
#include <string_view>

class Player;

enum class Tiles : char { AIR = '.', BLOCK = '#' };

class ILevel {
public:
	void draw() const;

	virtual ~ILevel() {};
	virtual void update(const Player& player) = 0;

protected:
	virtual std::string_view get_level_data() const = 0;

	ILevel();
};
