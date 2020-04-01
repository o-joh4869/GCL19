#include<DxLib.h>
#include<memory>
#include<vector>
#include<algorithm>
#include<array>

class KeyManager {
public:
	KeyManager() {
		for (int i = 0; i < 256; i++) {
			mKeyState[i] = 0;
		}
	}
private:
	int mKeyState[256];
public:
	void update() {
		char buf[256];
		GetHitKeyStateAll(buf);

		for (int i = 0; i < 256; i++) {
			if (buf[i]) {
				mKeyState[i]++;
				if (mKeyState[i] == 0) mKeyState[i]++;
			}
			else {
				if (mKeyState[i] > 0) mKeyState[i] = -1;
				else mKeyState[i] = 0;
			}
		}
	}

	const int &operator[](int keyInput) {
		return (mKeyState[keyInput]);
	}
};

KeyManager gKey;

template<class T>
class Vector2 {
public:
	Vector2() :
		x((T)0),
		y((T)0)
	{}
	Vector2(T x, T y) :
		x(x),
		y(y)
	{}
	T x, y;

	const T &operator[] (const int &o) const {
		if (o == 0) {
			return x;
		}
		else if (o == 1) {
			return y;
		}
		else {
			throw "out of range at Vector2::operator()";
			return x;
		}
	}
	const Vector2 &operator() (const T &x, const T &y) {
		this->x = x;
		this->y = y;
		return (*this);
	}

	Vector2 operator+ (const Vector2 &o) const {
		return Vector2(x + o.x, y + o.y);
	}
	Vector2 operator- (const Vector2 &o) const {
		return Vector2(x - o.x, y - o.y);
	}
	const Vector2 &operator+= (const Vector2 &o) {
		(*this) = (*this) + o;
		return (*this);
	}
	const Vector2 &operator-= (const Vector2 &o) {
		(*this) = (*this) - o;
		return (*this);
	}
	const Vector2 &operator++ () {
		x++;
		y++;
		return (*this);
	}
	const Vector2 &operator-- () {
		x--;
		y--;
		return (*this);
	}

	Vector2 operator* (const T &o) const {
		return Vector2(x * o, y * o);
	}
	Vector2 operator/ (const T &o) const {
		if (o != 0) {
			return Vector2(x / o, y / o);
		}
		else {
			//throw "Vector2::operator/ div 0";
			return Vector2();
		}
	}
	const Vector2 &operator*= (const T &o) {
		(*this) = (*this) * o;
		return (*this);
	}
	const Vector2 &operator/= (const T &o) {
		(*this) = (*this) / o;
		return (*this);
	}

	T operator* (const Vector2 &o) const {
		return (x*o.x + y * o.y);
	} //内積
	T crossProduct(const Vector2 &o) const {
		return (x*o.y - y * o.x);
	} //外積

	T length2() const {
		return (x*x + y * y);
	}
	T length() const {
		return (T)sqrt((double)(length2()));
	}
	const Vector2 &normalize() {
		return (*this) /= length();
	}
	Vector2 getNormalized() const {
		return (*this) / length();
	}
	T getCos() const {
		return (x / length());
	}
	T getCos(const Vector2 &v) const {
		return (*this) * v / (T)sqrt((double)(length2() * v.length2()));
	}
	T getSin() const {
		return (y / length());
	}
	T getSin(const Vector2 &v) const {
		return (crossProduct(v) / (T)sqrt((double)(length2() * v.length2())));
	}

};

template<class T>
inline Vector2<T> operator* (const T &t, const Vector2<T> &o) {
	return (o * t);
}
template<class T>
inline Vector2<T> operator/ (const T &t, const Vector2<T> &o) {
	return (o / t);
}

class Player {
public:
	Player(const Vector2<float> &pos = Vector2<float>());
private:
	Vector2<float> mPos;
	float mRadius;
	int mHP;
public:
	void update();
	void draw() const;
	const auto &getPos() const {
		return mPos;
	}
	const auto &getRadius() const {
		return mRadius;
	}
	const auto &getHP() const {
		return mHP;
	}
	void decHP() {
		mHP--;
	}
};

Player::Player(const Vector2<float> &pos) :
	mPos(pos),
	mHP(3),
	mRadius(20)
{
}

void Player::update() {
	Vector2<float> dPos(0.0f, 0.0f);
	if (gKey[KEY_INPUT_LEFT] > 0) dPos -= Vector2<float>(1.0f, 0.0f);
	if (gKey[KEY_INPUT_UP] > 0) dPos -= Vector2<float>(0.0f, 1.0f);
	if (gKey[KEY_INPUT_RIGHT] > 0) dPos += Vector2<float>(1.0f, 0.0f);
	if (gKey[KEY_INPUT_DOWN] > 0) dPos += Vector2<float>(0.0f, 1.0f);
	mPos += dPos.getNormalized() * 5.0f;
}
void Player::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(0, 0, 255));
}

class Enemy {
public:
	Enemy(const Vector2<float> &pos = Vector2<float>());
protected:
	Enemy(const Vector2<float> &pos, const float &radius);
public:
	virtual ~Enemy() = default;
protected:
	Vector2<float> mPos;
	float mRadius;
public:
	virtual void update(const Vector2<float> &playerPos);
	virtual void draw() const;
	virtual bool judge(Player *const &player) const;
	const auto &getRadius() {
		return mRadius;
	}
};

Enemy::Enemy(const Vector2<float> &pos) :
	mPos(pos),
	mRadius(20)
{}
Enemy::Enemy(const Vector2<float> &pos, const float &radius) :
	mPos(pos),
	mRadius(radius)
{}
void Enemy::update(const Vector2<float> &playerPos) {
	mPos += Vector2<float>(0.0f, 1.0f);
}

void Enemy::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(255, 0, 0));
}

bool Enemy::judge(Player *const &player) const {
	bool flag = (mPos - player->getPos()).length() < (mRadius + player->getRadius());
	if (flag) player->decHP();
	return flag;
}

class EnemyA : public Enemy {
public:
	EnemyA(const Vector2<float> &pos = Vector2<float>());
	virtual ~EnemyA() = default;
	virtual void update(const Vector2<float> &playerPos) override;
	virtual void draw() const override;
	virtual bool judge(Player *const &player) const override;
};

EnemyA::EnemyA(const Vector2<float> &pos) :
	Enemy(pos, 15.0f)
{}

void EnemyA::update(const Vector2<float> &playerPos) {
	mPos += (playerPos - mPos).getNormalized();
}

void EnemyA::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(0, 255, 0));
}

bool EnemyA::judge(Player *const &player) const {
	bool flag = (mPos - player->getPos()).length() < (mRadius + player->getRadius());
	if (flag) player->decHP();
	return flag;
}

class EnemyManager {
public:
	EnemyManager();
private:
	std::vector<std::unique_ptr<Enemy>> mEnemy;
public:
	void update(Player *const &player);
	void draw() const;
};

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
		i->draw(); //updateと同様
	}
}

class SceneBase;

class SceneManager {
public:
	SceneManager();
	enum GameMode {
		GAMEMODE_TITLE,
		GAMEMODE_GAME,

		GAMEMODE_SIZE
	};
	void changeScene(const GameMode &next);
	void update();
private:
	std::array<std::unique_ptr<SceneBase>, static_cast<size_t>(GAMEMODE_SIZE)> mScene;
	GameMode mGameMode;
};

SceneManager gSceneManager;

void SceneManager::changeScene(const GameMode &next) {
	mGameMode = next;
}

class SceneBase {
protected:
	SceneBase() {}
public:
	virtual void update() {}
	virtual ~SceneBase() = default;
};

void SceneManager::update() {
	mScene[mGameMode]->update();
}

class Title : public SceneBase {
public:
	Title();
	virtual void update() override;
	virtual ~Title() = default;
};

Title::Title() {

}
void Title::update() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Title");
	if (gKey[KEY_INPUT_SPACE] == -1) gSceneManager.changeScene(SceneManager::GAMEMODE_GAME);
}

class Game : public SceneBase {
public:
	Game();
	virtual void update() override;
	virtual ~Game() = default;
private:
	Player mPlayer;
	EnemyManager mEnemyManager;
};

Game::Game() : 
	mPlayer(),
	mEnemyManager()
{
}

void Game::update() {
	mPlayer.update();
	mEnemyManager.update(&mPlayer);
	mPlayer.draw();
	mEnemyManager.draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", mPlayer.getHP());
}

SceneManager::SceneManager() :
	mGameMode(GAMEMODE_TITLE)
{
	mScene[GAMEMODE_TITLE] = std::make_unique<Title>();
	mScene[GAMEMODE_GAME] = std::make_unique<Game>();
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(640, 480, 32);//画面サイズ指定
	SetMainWindowText("sample");//ウインドウに表示されるタイトルを指定
	SetAlwaysRunFlag(TRUE);//非アクティブ時も処理を続行
	if (DxLib_Init() == -1) { return -1; }//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
	SetWindowSizeChangeEnableFlag(TRUE); //ウィンドウを自由に拡大縮小できるように設定
	SetDrawMode(DX_DRAWMODE_BILINEAR); //拡大縮小で負荷を重くしてきれいに描画できるようにする

	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		gKey.update();

		gSceneManager.update();

		if (gKey[KEY_INPUT_ESCAPE] == -1) break;
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}