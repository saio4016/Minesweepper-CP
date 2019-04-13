#pragma once
#include "Board.h"

class Cursor
{
private:
	int cursorX;
	int cursorY;

public:
	Cursor();
	int getCursorX() const;
	int getCursorY() const;
	char operateCursor(const Board& board);
	~Cursor();
};

