#pragma once
#include <vector>
#include "Square.h"
#include "Cursor.h"

const int ROW = 16;                  //盤面の縦の長さ
const int COL = 30;                  //盤面の横の長さ
const int BOMBS_NUM = ROW * COL / 8; //爆弾の数(ROW*COL/8 = 60個)

//探索用の定数
const int mx8[8] = { 0,1,1,1,0,-1,-1,-1 };
const int my8[8] = { 1,1,0,-1,-1,-1,0,1 };


//盤面に関するクラス
class Board
{
private:
	std::vector<std::vector<Square>> board; //盤面(二次元)
	int restBombs;                          //残りの爆弾数(マークをしたら減る)
	int restNones;                          //残りの閉じマス数

public:
	Board();
	void initBoard();
	void initBombs(const Cursor& cursor);
	int countBombs(int x, int y);
	void dispFirstBoard();
	void dispEndBoard(const Cursor& cursor);
	void updateRest();
	void updateBoard(const Board& preBoard);
	void markBoard(const Cursor& cursor);
	void openSquare(int x, int y);
	void copyBoard(const Board& board);
	int getDispState(int x, int y) const;
	int getBombsNum(int x, int y) const;
	bool isFirstOpen();
	bool isOpenSquare(const Cursor& cursor);
	bool isGameOver(const Cursor& cursor);
	bool isGameClear();
	~Board();
};

