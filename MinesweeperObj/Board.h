#pragma once
#include <vector>
#include "Square.h"
#include "Cursor.h"

const int ROW = 16;                  //�Ֆʂ̏c�̒���
const int COL = 30;                  //�Ֆʂ̉��̒���
const int BOMBS_NUM = ROW * COL / 8; //���e�̐�(ROW*COL/8 = 60��)

//�T���p�̒萔
const int mx8[8] = { 0,1,1,1,0,-1,-1,-1 };
const int my8[8] = { 1,1,0,-1,-1,-1,0,1 };


//�ՖʂɊւ���N���X
class Board
{
private:
	std::vector<std::vector<Square>> board; //�Ֆ�(�񎟌�)
	int restBombs;                          //�c��̔��e��(�}�[�N�������猸��)
	int restNones;                          //�c��̕��}�X��

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

