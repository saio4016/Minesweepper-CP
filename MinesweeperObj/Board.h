#pragma once
#include <vector>
#include "Square.h"
#include "Cursor.h"

const int ROW = 20;                  //”Õ–Ê‚Ìc‚Ì’·‚³
const int COL = 30;                  //”Õ–Ê‚Ì‰¡‚Ì’·‚³
const int BOMBS_NUM = ROW * COL / 15; //”š’e‚Ì”

//”Õ–Ê‚ÉŠÖ‚·‚éƒNƒ‰ƒX
class Board
{
private:
	//’è”
	const int mx8[8] = { 0,1,1,1,0,-1,-1,-1 };
	const int my8[8] = { 1,1,0,-1,-1,-1,0,1 };

	//•Ï”
	std::vector<std::vector<Square>> board; //”Õ–Ê
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

