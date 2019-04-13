#pragma once
#include <vector>
#include "Square.h"
#include "Cursor.h"

const int ROW = 20;                  //�Ֆʂ̏c�̒���
const int COL = 30;                  //�Ֆʂ̉��̒���
const int BOMBS_NUM = ROW * COL / 15; //���e�̐�

//�ՖʂɊւ���N���X
class Board
{
private:
	//�萔
	const int mx8[8] = { 0,1,1,1,0,-1,-1,-1 };
	const int my8[8] = { 1,1,0,-1,-1,-1,0,1 };

	//�ϐ�
	std::vector<std::vector<Square>> board; //�Ֆ�
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

