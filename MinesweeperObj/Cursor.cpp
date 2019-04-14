#include "pch.h"
#include "Cursor.h"
#include <cstdio>
#include <conio.h>

//�R���X�g���N�^
Cursor::Cursor() {
	//�ŏ��̃J�[�\���ʒu�͐^��
	cursorX = COL / 2;
	cursorY = ROW / 2;
}

//CursorX���擾
int Cursor::getCursorX() const {
	return cursorX;
}

//CursorY���擾
int Cursor::getCursorY() const {
	return cursorY;
}

//����(f����������true��Ԃ�)
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
		board.markBoard(*this); //�����Ń}�[�N���o����悤��board��const�ɂ��ĂȂ�
		break;
	case 'f':
		return true;
	default:
		break;
	}
	return false;
}

//�J�[�\�����f(cursor�Ŏg�p)
void Cursor::updateCursor(const Board& board, const Cursor& preCursor) {
	//�J�[�\��������(���ɖ߂�)
	int pcx = preCursor.getCursorX(), pcy = preCursor.getCursorY();
	std::printf("\033[%d;%dH", pcy + 3, pcx * 3 + 1); //�ύX����ꍇ�ɂ͔��������K�v
	switch (board.getDispState(pcx, pcy)) {
	case OPENED:
		if (board.getBombsNum(pcx, pcy) == NONE) std::printf("�E ");
		else std::printf(" %d ",board.getBombsNum(pcx, pcy));
		break;
	case CLOSED:
		std::printf("�� ");
		break;
	case MARKED:
		std::printf("�� ");
		break;
	default:
		std::printf("no");
		break;
	}
	//�J�[�\����t����(�I������)
	printf("\033[%d;%dH", cursorY + 3, cursorX * 3 + 1); //�ύX����ꍇ�͔��������K�v
	std::printf("�� ");
	printf("\b\b\b");                                    //�J�[�\���ʒu�ɓ_�ł����킷����
	                                                     //1�}�X(2����)+�J�[�\����łƐi�ދ���(1����)=3������
}

//�J�[�\���R�s�[(preCursor�Ŏg�p)
void Cursor::copyCursor(const Cursor& cursor) {
	this->cursorX = cursor.getCursorX();
	this->cursorY = cursor.getCursorY();
}

Cursor::~Cursor() {
}
