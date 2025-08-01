#pragma once
#include "level.hpp"

class Level1 final : public LevelBase {
public:
	Level1() = default;
	~Level1() override {};

	void update(const Player& player) override;

protected:
	std::string_view get_level_data() const override;
};
