#include"EnemyManager.h"
#include"Enemy.h"
#include"EnemyA.h"
#include"KeyManager.h"
#include"Player.h"
#include<DxLib.h>
#include<algorithm>

EnemyManager::EnemyManager() {
	mEnemy.emplace_back(std::make_unique<EnemyA>(Vector2<float>(200.0f, 200.0f)));
}

void EnemyManager::update(Player *const &player) {
	if (gKey[KEY_INPUT_Z] == 1) mEnemy.emplace_back(std::make_unique<Enemy>(Vector2<float>(150.0f, 0.0f)));
	if (gKey[KEY_INPUT_C] == 1) mEnemy.emplace_back(std::make_unique<EnemyA>(Vector2<float>(150.0f, 0.0f)));

	//if (gKey[KEY_INPUT_X] == 1) mEnemy.erase(mEnemy.begin());

	const auto &itr = std::remove_if(mEnemy.begin(), mEnemy.end(),
		[&player](std::unique_ptr<Enemy>& i) {
		i->update(player->getPos());
		return i->judge(player);
	}
	);
	mEnemy.erase(itr, mEnemy.end());
}

void EnemyManager::draw() const {
	for (const auto &i : mEnemy) {
		i->draw(); //update‚Æ“¯—l
	}
}
