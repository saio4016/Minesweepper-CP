#pragma once
#include "Board.h"

class Board;

class Cursor
{
private:
	int cursorX; //�J�[�\����x���W
	int cursorY; //�J�[�\����y���W

public:
	Cursor();
	int getCursorX() const;
	int getCursorY() const;
	bool operateCursor(Board& board);
	void copyCursor(const Cursor& cursor);
	void updateCursor(const Board& board, const Cursor& preCursor);
	~Cursor();
};

