#include "pch.h"
#include "Cursor.h"
#include "Board.h"
#include <conio.h>

//コンストラクタ
Cursor::Cursor()
{
	cursorX = ROW/2;
	cursorY = COL/2;
}

//カーソルのx座標取得
int Cursor::getCursorX() const{
	return cursorX;
}

//カーソルのy座標取得
int Cursor::getCursorY() const{
	return cursorY;
}

//カーソル操作
char Cursor::operateCursor() {
	switch (_getch()) {
	case 'w':
		if (cursorY > 0) cursorY--;
		break;
	case 'a':
		if (cursorX > 0) cursorX--;
		break;
	case 's':
		if (cursorY < ROW - 1) cursorY++;
		break;
	case 'd':
		if (cursorX < COL - 1) cursorX++;
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
