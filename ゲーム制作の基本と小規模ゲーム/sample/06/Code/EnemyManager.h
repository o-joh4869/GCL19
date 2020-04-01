#pragma once
#include"Enemy.h"
#include<memory>
#include<vector>
#include"Player.h"

class EnemyManager {
public:
	EnemyManager();
private:
	std::vector<std::unique_ptr<Enemy>> mEnemy;
public:
	void update(Player *const &player);
	void draw() const;
};