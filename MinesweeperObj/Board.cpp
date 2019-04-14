#include "pch.h"
#include "Board.h"
#include <cstdio>
#include <random> //���e�����p

//�R���X�g���N�^
Board::Board() {
	initBoard();
}

//�����ݒ�(�R���X�g���N�^�ŌĂяo��)
void Board::initBoard() {
	//�Ֆʊm��
	board = std::vector<std::vector<Square>>(ROW, std::vector<Square>(COL));
	//�Ֆʏ�����
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].DispState = CLOSED;
			board[y][x].NonDispState = NONE;
		}
	}
	//�ϐ��̏�����
	restBombs = BOMBS_NUM; //�\���̊֌W�ōŏ����甚�e�����邱�ƂƂ���
	restNones = ROW * COL;
}

//���e�ݒ�
void Board::initBombs(const Cursor& cursor) {
	int cx = cursor.getCursorX(), cy = cursor.getCursorY();
	//�Ֆʂɔ��e��z�u����
	std::random_device rnd;
	while (restNones != ROW*COL-BOMBS_NUM) {
		int x = rnd() % COL, y = rnd() % ROW;
		//(cx,cy)����A������x�J���悤�ɂ���
		if (cx - 1 <= x && x <= cx + 1 && cy - 1 <= y && y <= cy + 1) continue;
		//���ł�(x,y)�ɔ��e������ΑI�ђ���
		if (board[y][x].NonDispState == BOMB) continue;
		board[y][x].NonDispState = BOMB;
		restNones--;
	}
	//�C�ӂ̃}�X�̎��͂̔��e�̐��𐔂���
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].BombsNum = countBombs(x, y);
		}
	}
}

//���͂̔��e�̐��𐔂���(initBombs�Ŏg�p)
int Board::countBombs(int x, int y) {
	int ret = 0;
	for (int k = 0; k < 8; k++) {
		int nx = x + mx8[k], ny = y + my8[k];
		if (!(0 <= nx && nx < COL && 0 <= ny && ny < ROW)) continue;
		if (board[ny][nx].NonDispState == BOMB) ret++;
	}
	return ret;
}

//�Ֆʕ\��(�)
void Board::dispFirstBoard() {
	std::printf("Rest Bombs: %d\n", BOMBS_NUM);
	std::printf("Rest Nones: %d\n", ROW * COL);
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			std::printf("�� ");
		}
		std::printf("\n");
	}
}

//�Ֆʕ\��(�Ō�)
void Board::dispEndBoard(const Cursor& cursor) {
	std::printf("Bombs num : %d\n", BOMBS_NUM);
	std::printf("Rest Nones: %d\n", restNones);
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (x == cursor.getCursorX() && y == cursor.getCursorY() &&
				board[y][x].NonDispState == BOMB) {
				std::printf("�� "); //���������ꏊ
			}
			else {
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == 0) std::printf("�E ");
					else std::printf(" %d ",board[y][x].BombsNum);
					break;
				case CLOSED:
					if (board[y][x].NonDispState == BOMB) std::printf(" B ");
					else std::printf("�� ");
					break;
				case MARKED:
					if (board[y][x].NonDispState == BOMB) std::printf("�� ");
					else std::printf(" x ");
					break;
				default:
					std::printf("no");
					break;
				}
			}
		}
		std::printf("\n");
	}
}

//rest�\�����f
void Board::updateRest() {
	//�ύX����ꍇ�͔��������K�v
	std::printf("\033[1;12H %d  ", restBombs);
	std::printf("\033[2;12H %d  ", restNones);
}

//�Ֆʔ��f(board�Ŏg�p)
void Board::updateBoard(const Board& preboard) {
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (board[y][x].DispState != preboard.getDispState(x, y)) { //�O�̔ՖʂƂ̕ύX�_
				std::printf("\033[%d;%dH", y + 3, x * 3 + 1);           //�ύX����ꍇ�ɂ͔��������K�v
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == NONE) std::printf("�E ");
					else std::printf(" %d ", board[y][x].BombsNum);
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
			}
		}
	}
}

//�}�[�N��t����/����
void Board::markBoard(const Cursor& cursor) {
	int cx = cursor.getCursorX(), cy = cursor.getCursorY();
	switch (board[cy][cx].DispState) {
	case CLOSED:
		board[cy][cx].DispState = MARKED;
		restBombs--;
		break;
	case MARKED:
		board[cy][cx].DispState = CLOSED;
		restBombs++;
		break;
	}
}

//board[y][x].DispState���J����(isOpenSquare�Ŋm�F���Ă���g��)
void Board::openSquare(int x, int y) {
	board[y][x].DispState = OPENED;
	restNones--;
	if (board[y][x].BombsNum == 0) {
		for (int k = 0; k < 8; k++) {
			int nx = x + mx8[k], ny = y + my8[k];
			if (!(0 <= nx && nx < COL && 0 <= ny && ny < ROW)) continue;
			if (board[ny][nx].DispState != CLOSED) continue; //OPENED�܂���MARKED
			openSquare(nx, ny);
		}
	}
}

//�ՖʃR�s�[(preBoard�Ŏg�p)
void Board::copyBoard(const Board& board) {
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			this->board[y][x].DispState = board.getDispState(x, y);
		}
	}
}

//board[y][x].DispStste���擾
int Board::getDispState(int x, int y) const {
	return board[y][x].DispState;
}

//board[y][x].BombsNum���擾
int Board::getBombsNum(int x, int y) const {
	return board[y][x].BombsNum;
}

//����Ȃ�true��Ԃ�
bool Board::isFirstOpen() {
	if (restNones == ROW * COL) return true;
	else return false;
}

//�w��}�X�ɒu�����true��Ԃ�
bool Board::isOpenSquare(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].DispState == CLOSED) return true;
	else return false; //�u����
}

//�w��}�X�ɔ��e�������true��Ԃ�
bool Board::isGameOver(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].NonDispState == BOMB) return true;
	else return false;
}

//�󂯂���}�X���Ȃ����true��Ԃ�
bool Board::isGameClear() {
	if (restNones == 0) return true;
	else return false;
}

Board::~Board() {
}
