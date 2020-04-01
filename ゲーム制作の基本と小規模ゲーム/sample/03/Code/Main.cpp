#include<DxLib.h>
#include<memory>
#include<vector>

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
public:
	void update();
	void draw() const;
	const auto &getPos() {
		return mPos;
	}
};

Player::Player(const Vector2<float> &pos) :
	mPos(pos)
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
	DrawCircle((int)mPos[0], (int)mPos[1], 20, GetColor(0, 0, 255));
}

class Enemy {
public:
	Enemy(const Vector2<float> &pos = Vector2<float>());
	virtual ~Enemy() = default;
protected:
	Vector2<float> mPos;
public:
	virtual void update(const Vector2<float> &playerPos);
	virtual void draw() const;
};

Enemy::Enemy(const Vector2<float> &pos) :
	mPos(pos)
{}
void Enemy::update(const Vector2<float> &playerPos) {
	mPos += Vector2<float>(0.0f, 1.0f);
}

void Enemy::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], 20, GetColor(255, 0, 0));
}

class EnemyA : public Enemy {
public:
	EnemyA(const Vector2<float> &pos = Vector2<float>());
	virtual ~EnemyA() = default;
	virtual void update(const Vector2<float> &playerPos) override;
	virtual void draw() const override;
};

EnemyA::EnemyA(const Vector2<float> &pos) :
	Enemy(pos)
{}

void EnemyA::update(const Vector2<float> &playerPos) {
	mPos += (playerPos - mPos).getNormalized();
}

void EnemyA::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], 15, GetColor(0, 255, 0));
}

class EnemyManager {
public:
	EnemyManager();
private:
	std::vector<std::unique_ptr<Enemy>> mEnemy;
public:
	void update(const Vector2<float> &playerPos);
	void draw() const;
};

EnemyManager::EnemyManager() {
	mEnemy.emplace_back(std::make_unique<EnemyA>(Vector2<float>(200.0f, 200.0f)));
}

void EnemyManager::update(const Vector2<float> &playerPos) {
	if (gKey[KEY_INPUT_Z] == 1) mEnemy.emplace_back(std::make_unique<Enemy>(Vector2<float>(150.0f, 0.0f)));
	if (gKey[KEY_INPUT_X] == 1) mEnemy.erase(mEnemy.begin());

	for (auto &i : mEnemy) {
		i->update(playerPos);
	}
}

void EnemyManager::draw() const {
	for (const auto &i : mEnemy) {
		i->draw(); //updateと同様
	}
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

	Player player;
	EnemyManager enemyManager;

	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		gKey.update();

		player.update();
		enemyManager.update(player.getPos());
		player.draw();
		enemyManager.draw();

		if (gKey[KEY_INPUT_ESCAPE] == -1) break;
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}