#include <DxLib.h>

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

		if (gKey[KEY_INPUT_A] <= 0) {
			DrawFormatString(0, 0, GetColor(255, 255, 255), "Push Key A");
		}
		else {
			DrawFormatString(0, 0, GetColor(255, 255, 255), "Key A is On.");
		}

		if (gKey[KEY_INPUT_ESCAPE] == -1) break;

		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}