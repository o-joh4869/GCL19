## ゲーム制作講座
***
前回紹介したシーン遷移では値の共有に問題があった。  
これを解決するためにStateクラスを作成し、有効性を持たせるためにシーンを階層化してシーケンスとして扱う。  

# Stateクラス

面セレクトのシーンとゲームのシーンでは面の種類によって具体的な敵の出し方が変わってくるのが普通だが、そのたびにほとんど同じ別のシーンを作成するのはバカバカしいのでどの面を選んだかという情報は共有したい。  
コンストラクタの引数に指定してもいいが、数が多くなると面倒が多かったり、コピーにコストがかかったり、メモリの解放の問題が付きまとうためできればやりたくない。  
そこでStateクラスを作成し複数のシーン間で値を共有するものをメンバにもたせ、Scene::Managerのメンバに定義する。  
普通にコンポジションしてしまってもいいが、変更につよくするためにポインタ変数をメンバにする。  

```cpp
/* Scene/State.h */
#pragma once

namespace Scene {
    class State {
    public:
        State();
        //...
    };
}
```

```cpp
/* Scene/Manager.h */
#pragma once

namespace Scene {
    class State;
    //...
    class Manager {
    private:
        State *mState;
        //...
    };
}
```

アクセス修飾子をprivateにした。  
このポインタを使うのは各シーンのみであるためだ。  

さて、このようにしてStateクラスを作成したが、ポインタをどうやって渡そう。  
今回は各シーンにconst State*型のメンバを持つようにしてコンストラクタで初期化する。  
すべてのシーンがもつから基底クラスのメンバにしてしまってもいいが、このあとの事情でそうしない。  

# シーンの階層化

このままでは結局Stateクラスはグローバル変数をまとめたものになってしまう。  
また、Stateクラスのメンバは細かく変更が加えられることが予想されるが、ほとんどすべてのシーンクラスでインクルードする必要があるためリコンパイルが増えてしまう。  

現状のStateクラスに入れるものにどんなものがあるかを考える。  
例えばプレーヤーのキャラクターを選ぶ画面があったとする。  
その画面で行う処理を考えると、選んだキャラクター情報をゲームをプレイするシーンに渡したい。  
リザルト画面でも自機を表示したりするため必要かもしれない。  
また、選んだキャラ情報以外にも、ステージを選んだり装備を選んだりと共有したい情報はたくさん出てくる。  
この共有したい情報をいくつか見ていくと、それらを使っているシーンはだいたい固まっていることがわかる。  

ゲームプレイ中のシーン近辺でのみ共有したい情報がたくさんあるのにそれを変更するだけでタイトル画面までリコンパイルというのは何とかしたい。  
そこで、シーンを階層化してそのシーンごとにもStateクラスを持たせる。  

どういうことかよくわからないと思うのでコードにしながら見ていこう。  
階層化させる前にScene::StateにstageIDを追加し、StageSelectシーンを作成しておく。  

```cpp
/* Scene/StageSelect/Manager.h */
#pragma once
#include"../Base.h"

namespace Scene {
    class State;
namespace StageSelect {
    class Manager : public Scene::Base {
    public:
        Manager(Scene::State *state);
        virtual Scene::Base *update() override;
        virtual ~Manager() = default;
    private:
        Scene::State *mState;
        int mStageid;
    };
}}
```

```cpp
/* Scene/StageSelect/Manager.cpp */
#include"Manager.h"
#include"../Game/Manager.h"
#include"../../Tool/KeyManager.h"
#include"../State.h"
#include<DxLib.h>

using namespace Scene::StageSelect;

Manager::Manager(Scene::State *state) : 
	mState(state),
	mStageid(mState->stageID)
{

}

Scene::Base *Manager::update() {

	if (gKey[KEY_INPUT_LEFT] == 1) mStageid = 0;
	if (gKey[KEY_INPUT_RIGHT] == 1) mStageid = 1;

	DrawFormatString(5, 0, 0xffffff, "0 1");

	if (mStageid == 0) DrawFormatString(0, 0, 0xffffff, "\n↑");
	else DrawFormatString(0, 0, 0xffffff, "\n  ↑");

	if (gKey[KEY_INPUT_RETURN] == -1) {
		mState->stageID = mStageid;
		return (new Scene::Game::Manager(mState));
	}
	else return this;
}
```

このシーンを呼び出せば、Scene::State::stageIDが変更できる。  
Gameシーンでこれを表示してみれば実際に値を共有できていることが確認できる。  

StageSelect以外にも今Gameで管理しているシーンに渡したい値はたくさんあるが、これはたいていの場合Titleやゲーム説明等のシーンでは必要ない。  
よって、このGame周りのものをまとめたStateクラスを新たに作成し、そこで管理することにする。  
もし、Gameの外に値を渡したいときが出てきたときのためにこのStateクラスにはScene::Stateのポインタ型を持たせておく。  
こうすることで、Scene/State.hを必要なところでインクルードすればGame::Stateを通じて値を変更できる。  

GameをSceneManagerをまねた形に変更して、今までGameで管理していたシーンをGame::Playという名前空間で管理することにする。  
次にStageSelectシーンをGameで管理するためにGame名前空間に移動する。  

そして、Play::ManagerとStageSelect::ManagerにGame::State型のポインタをメンバに持たせてコンストラクタで初期化する。  
Game::Stateの実体管理はGame::Managerのコンストラクタとデストラクタで行う。  
これはScene::Stateと同様である。  

こうして、シーンを階層化して階層ごとにStateクラスを作成することで関係性の薄いシーン間で変更に強くなった。  

また、Game::Managerのようにシーンそのものを表すわけではなくシーンを束ねる役割を果たすクラスが出てきたのでこれをシーンとは少し呼びにくい。  
そこで、今までシーンと呼んでいたものを一括してシーケンスと呼ぶことにする。  
今後シーケンスと呼んでいくが、今まで呼んでいたシーンと本質的な違いはないのでシーンに読み替えてもらっても構わない。  

# 階層間の遷移

ここで問題になるのがGame::Manager::updateの返り値である。  
今この関数から次のシーケンスに関する情報として得られるのは、次のシーケンスへのポインタをScene::Base*型にアップキャストしたもののみである。  
この関数の中から返ってきたポインタが自分が扱える範囲内であるか(Gameの範囲内に作ったシーケンスであるか)を判断しなければいけない。  

ここでdynamic_castというものを導入する。  

dynamic_castは、あるポインタをダウンキャストするときにそのポインタの先にあるインスタンスが本当に継承先のものであるかを判断してくれる。  
キャストに成功すればそのポインタがキャスト後の型で、失敗したらnullptrが返ってくる。  
つまり、
```cpp
class Base {
};
class Derived : public Base {
};
```
という関係のクラスがあったときに
```cpp
Base *p1 = new Base();
Base *p2 = new Derived();
Derived *p3 = dynamic_cast<Derived*>(p1); //nullptr
Derived *p4 = dynamic_cast<Derived*>(p2); //p2と同じ値
```
という結果になる。  

VisualStudio2017でこの機能を使うには少し設定を変更する必要があって、プロジェクトのプロパティ → C/C++ → 言語 → ランタイム型情報を有効にする を「はい」に変更する。  
こうすることでdynamic_castが利用できる。  

これを利用してGame::Manager::updateの中で返ってきたポインタがGame内で扱える範囲か判断する。  

まず下準備としてScene::Baseをpublic継承したScene::Game::Baseクラスを用意する。  
内容はSceneBaseとほとんど変わらない。  

Game内のシーケンスクラスはすべてScene::Baseを直接継承するのではなくこのScene::Game::Baseを継承して間接的にScene::Baseとの継承関係を持つ。  
もちろん間にGame::Baseが挟まったところでScene::Game::PlayクラスのポインタをGame::Base*にアップキャストすることはできる。  

こうしてGameで扱える範囲のシーケンスクラスがScene::Game::Baseの派生クラスになった。  
あとはGame::Manager::update関数でdynamic_castを実行してScene::Game::Base*にダウンキャストできるか調べ、成功したらGame内で扱えるためmSeq(旧mScene)をresetすればいい。  
失敗したらnullptrが返ってくるのでif文で分岐してupdateから帰ってきたそのもののポインタをreturnしてあげる。  

こうして階層間のシーケンス遷移が実現できた。  

# まとめ

今回シーンを階層化してシーケンスにして、Stateクラスを各階層に作ることで変更に強くした。  
コードが少なく日本語ばかりだったのでサンプルコードをよく見てもらえるといいだろう。  