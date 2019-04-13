#include "pch.h"
#include "Cursor.h"
#include <conio.h>

//�R���X�g���N�^
Cursor::Cursor()
{
	cursorX = 0;
	cursorY = 0;
}

//�J�[�\����x���W�擾
int Cursor::getCursorX() const{
	return cursorX;
}

//�J�[�\����y���W�擾
int Cursor::getCursorY() const{
	return cursorY;
}

//�J�[�\������
char Cursor::operateCursor(const Board& board) {
	bool first = board.isFirstMove;
	switch (_getch()) {
	case 'w':
		if (!first && cursorY > 0) cursorY--;
		break;
	case 'a':
		if (!first && cursorX > 0) cursorX--;
		break;
	case 's':
		if (!first && cursorY < ROW - 1) cursorY++;
		break;
	case 'd':
		if (!first && cursorX < COL - 1) cursorX++;
		break;
	case 'f':
		return 'f';
	case 'e':
		return 'e';
	default:
		break;
	}
	return NULL;
}

Cursor::~Cursor()
{
}
