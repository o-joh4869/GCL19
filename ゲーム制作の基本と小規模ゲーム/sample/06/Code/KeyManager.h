#pragma once

class KeyManager {
public:
	KeyManager();
private:
	int mKeyState[256];
public:
	void update();

	const int &operator[](int keyInput) {
		return (mKeyState[keyInput]);
	}
};

extern KeyManager gKey;