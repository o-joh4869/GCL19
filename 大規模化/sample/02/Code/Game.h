#pragma once
#include"SceneBase.h"
#include<memory>

class Player;
class EnemyManager;

class Game : public SceneBase {
public:
	Game();
	Game(const Game&) = delete;
	Game &operator= (const Game&) = delete;
	~Game();
	virtual void update() override;
private:
	Player *mPlayer;
	EnemyManager *mEnemyManager;
};