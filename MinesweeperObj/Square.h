#pragma once

//表示盤面の状態
typedef int DispState;
const DispState OPENED = 0; //開いている
const DispState CLOSED = 1; //閉じている
const DispState MARKED = 2; //マークあり

//内部盤面の状態
typedef int NonDispState;
const NonDispState NONE = 0; //何もなし
const NonDispState BOMB = 1; //爆弾あり

//マスに関する構造体
struct Square
{
	int DispState;     //表示盤面
	int NonDispState;  //内部盤面
	int BombsNum;      //周囲の爆弾の数
};