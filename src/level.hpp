#pragma once

class Player;

class ILevel {
public:
	virtual ~ILevel() {};
	virtual void draw() = 0;
	virtual void update(const Player& player) = 0;

protected:
	ILevel();
};

class Level1 final : public ILevel {
public:
	Level1() = default;
	~Level1() override {};

	void draw() override;

	void update(const Player& player) override;
};
