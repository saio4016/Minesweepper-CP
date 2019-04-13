#pragma once
#include <vector>
#include "Square.h"
#include "Cursor.h"

const int ROW = 20;                  //盤面の縦の長さ
const int COL = 30;                  //盤面の横の長さ
const int BOMBS_NUM = ROW * COL / 15; //爆弾の数

//盤面に関するクラス
class Board
{
private:
	//定数
	const int mx8[8] = { 0,1,1,1,0,-1,-1,-1 };
	const int my8[8] = { 1,1,0,-1,-1,-1,0,1 };

	//変数
	std::vector<std::vector<Square>> board; //盤面
	int restBombs;
	int restNones;

public:
	Board();
	void initBoard();
	void initBombs(int cx, int cy);
	int countBombs(int x, int y);
	void dispBoard(const Cursor& cursor);
	void endDispBoard(const Cursor& cursor);
	void markBoard(const Cursor& cursor);
	void openSquare(int x, int y);
	bool isFirstOpen() const;
	bool isOpenSquare(const Cursor& cursor);
	bool isGameOver(const Cursor& cursor);
	bool isGameClear();
	~Board();
};

