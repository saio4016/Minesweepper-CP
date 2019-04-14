#pragma once
#include "Board.h"

class Board;

class Cursor
{
private:
	int cursorX; //カーソルのx座標
	int cursorY; //カーソルのy座標

public:
	Cursor();
	int getCursorX() const;
	int getCursorY() const;
	bool operateCursor(Board& board);
	void copyCursor(const Cursor& cursor);
	void updateCursor(const Board& board, const Cursor& preCursor);
	~Cursor();
};

