## ゲーム制作講座

スマートポインタの一つであるunique_ptrについて紹介する。  

# スマートポインタとは

動的にメモリを確保するためにnewというものがあった。  
Cのmallocというものもあったがクラスのコンストラクタを呼ぶことができないためnewを使うことが推奨される。  

しかしnewしたものはdeleteする必要があり、開放し忘れはメモリリークを引き起こす。  
このミスを防ぐために作られたのがスマートポインタというものである。  
仕組みを簡単に説明すると、newされたポインタの管理をクラスで行いデストラクタでdeleteするというものだ。  
(ポインタを管理する権利を所有権という)  

C++講座の方ではshared_ptrを紹介したが、ここでは本編の都合上unique_ptrを紹介する。  
大きな違いとしては、unique_ptrはコピーや代入を行った際に元のクラスのポインタをnullptrにするという点である。  
言い換えれば、そのポインタに対する所有権を持つunique_ptrはただ一つであるということだ。  
※正確にはコピーではなくムーブだが、わかりやすさのため詳細は省く  

# 書き方

unique_ptrを使用するにはshared_ptr同様memoryをインクルードする必要がある。  

```cpp
#include<memory>
```

書き方は
```cpp
std::unique_ptr<int> p;
```

である。  

# ポインタを渡す

このままではインスタンスは生成していない。  
生成したいクラスのコンストラクタの引数がunique_ptr側からはわからないのでインスタンスの生成は外部で行い、そのポインタを渡す必要がある。  

unique_ptrにポインタを渡す方法はいくつかある。  

一つ目はコンストラクタで渡す方法だ。  
```cpp
std::unique_ptr<int> p(new int(10));
```

二つ目はメンバ関数resetを利用する方法だ。
```cpp
std::unique_ptr<int> p;
p.reset(new int(10));
```
reset関数は、もともと所持していたポインタをdeleteして新しいポインタを所持する。  
コンストラクタでポインタを渡さなかった場合はnullptrを持っているので結果ポインタを渡しただけになる。  

# make_unique

unique_ptrにポインタを渡すとき、newをして渡していた。  
これではうまくいかない場合があるので用意されているmake_uniqueを利用する。    

```cpp
std::unique_ptr<int> p(std::make_unique<int>(10));
```

make_uniqueの返り値はunique_ptr型であるため、ここで呼ばれているのは通常のコンストラクタではなくムーブコンストラクタと呼ばれるものである。  
この時unique_ptr型の一時オブジェクトが持っているポインタを受け取ってpが生成され、一時オブジェクトは保持していたポインタをnullptrに書き換えてから解放される。  

こうしてunique_ptrにポインタを渡すことができた。  

また、make_uniqueを使う場合ムーブコンストラクタを呼んでいるので
```cpp
std::unique_ptr<int> p = std::make_unique<int>(10);
```

のように=の記号を使うこともできる。  
これは代入演算子ではないことに注意しよう。  

# 代入演算子

unique_ptrは代入演算子が定義されている。  
コピーは禁止されており、ムーブ代入のみが可能である。  

```cpp
std::unique_ptr<int> p1 = std::make_unique<int>(3);
std::unique_ptr<int> p2;

p2 = std::move(p1); //ムーブ代入
```

p1にはnullptrがはいり、p1にもともと入っていた(int)3のポインタはdeleteされずにp2に移る。  

また、nullptrを代入すると、所有権の放棄(メモリの開放)が行える。  
```cpp
std::unique_ptr<int> p = std::make_unique<int>(10);
p = nullptr;
```

# deleteされるタイミング

明示的に解放処理をしなかった場合、unique_ptrのデストラクタが呼ばれたときにdeleteされる。  

# 使い方

unique_ptrにはアロー演算子や*などが定義されていて、通常のポインタと同様に扱うことができる。  
```cpp
std::unique_ptr<int> p = std::make_unique<int>(10);
std::cout << (*p) << std::endl;
```

関数に渡すときはコピーが禁止されているため生のポインタを渡すか参照渡しをする必要がある。  
そのunique_ptrが持っているポインタを取得するメンバ関数がgetとreleaseである。  

get関数もrelease関数も持っているポインタが返ってくる。  
```cpp
std::unique_ptr<int> p = std::make_unique<int>(10);
int *p2 = p.get();
int *p3 = p.release(); //p2と同じ値
```

release関数もポインタが返ってくるが、所有権を放棄する。  
この関数を一度呼ぶとunique_ptrのデストラクタでdeleteはされず、自分でdeleteする必要がある。  
また、release後はnullptrを持つ。  
```cpp
int *p2;
{
    std::unique_ptr<int> p = std::make_unique<int>(10);
    p2 = p.release();
    //ここでpはnullptrを持つ
}
delete p2;
```

# unique_ptrとポリモーフィズム

スマートポインタでも仮想関数を利用したポリモーフィズムができる。  
仮想関数を持つクラスBaseを継承したDerivedクラスを用意して、
```cpp
Base *p = new Derived();
```
のように自動的にキャストされた。(派生クラスのポインタから基底クラスのポインタへのキャストとをアップキャストという。)  

スマートポインタでも同じように書くことができる。  
```cpp
std::unique_ptr<Base> p = std::make_unique<Derived>();
```

この時に一つ違う点がある。  
スマートポインタを使うとき、基底クラス(今回はBaseクラス)で純粋仮想関数を作成できないという点だ。  
これはunique_ptrの中でnewに準ずる処理をしていることに起因する。  

純粋仮想関数にしていた関数に何かしら定義を書く必要がある。  
コードの保守性を気にするなら呼ばれたらエラーを投げるようにthrowしてあげてもいいと思う。  
コンストラクタをprotectedにして外部からBaseクラスのインスタンスを生成しないように制限することで限定的に純粋仮想関数の機能を再現することもできる。  

# 練習問題

int型のunique_ptrを作成し、そのポインタをint*型を引数に持つ関数にget関数を用いて渡せ。  
関数は受け取ったポインタの先をcoutで表示する。    
