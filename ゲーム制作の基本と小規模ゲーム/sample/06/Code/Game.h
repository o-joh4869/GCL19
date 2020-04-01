#pragma once
#include"SceneBase.h"
#include"Player.h"
#include"EnemyManager.h"

class Game : public SceneBase {
public:
	Game();
	virtual void update() override;
	virtual ~Game() = default;
private:
	Player mPlayer;
	EnemyManager mEnemyManager;
};