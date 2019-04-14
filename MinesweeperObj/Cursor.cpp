#include "pch.h"
#include "Cursor.h"
#include <cstdio>
#include <conio.h>

//コンストラクタ
Cursor::Cursor() {
	//最初のカーソル位置は真ん中
	cursorX = COL / 2;
	cursorY = ROW / 2;
}

//CursorXを取得
int Cursor::getCursorX() const {
	return cursorX;
}

//CursorYを取得
int Cursor::getCursorY() const {
	return cursorY;
}

//操作(fを押したらtrueを返す)
bool Cursor::operateCursor(Board& board) {
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
	case 'e':
		board.markBoard(*this); //ここでマークを出来るようにboardはconstにしてない
		break;
	case 'f':
		return true;
	default:
		break;
	}
	return false;
}

//カーソル反映(cursorで使用)
void Cursor::updateCursor(const Board& board, const Cursor& preCursor) {
	//カーソルを消す(元に戻す)
	int pcx = preCursor.getCursorX(), pcy = preCursor.getCursorY();
	std::printf("\033[%d;%dH", pcy + 3, pcx * 3 + 1); //変更する場合には微調整が必要
	switch (board.getDispState(pcx, pcy)) {
	case OPENED:
		if (board.getBombsNum(pcx, pcy) == NONE) std::printf("・ ");
		else std::printf(" %d ",board.getBombsNum(pcx, pcy));
		break;
	case CLOSED:
		std::printf("□ ");
		break;
	case MARKED:
		std::printf("◎ ");
		break;
	default:
		std::printf("no");
		break;
	}
	//カーソルを付ける(選択する)
	printf("\033[%d;%dH", cursorY + 3, cursorX * 3 + 1); //変更する場合は微調整が必要
	std::printf("● ");
	printf("\b\b\b");                                    //カーソル位置に点滅を合わすため
	                                                     //1マス(2文字)+カーソルを打つと進む距離(1文字)=3文字分
}

//カーソルコピー(preCursorで使用)
void Cursor::copyCursor(const Cursor& cursor) {
	this->cursorX = cursor.getCursorX();
	this->cursorY = cursor.getCursorY();
}

Cursor::~Cursor() {
}
