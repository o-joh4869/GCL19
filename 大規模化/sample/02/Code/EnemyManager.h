#pragma once
#include<memory>
#include<vector>
class Enemy;
class Player;

class EnemyManager {
public:
	EnemyManager();
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager &operator= (const EnemyManager&) = delete;
private:
	std::vector<std::unique_ptr<Enemy>> mEnemy;
public:
	void update(Player *const &player);
	void draw() const;
};