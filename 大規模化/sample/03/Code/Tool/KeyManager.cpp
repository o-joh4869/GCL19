#include"KeyManager.h"
#include<DxLib.h>

KeyManager::KeyManager() {
	for (int i = 0; i < 256; i++) {
		mKeyState[i] = 0;
	}
}

void KeyManager::update() {
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

KeyManager gKey;