#include "pch.h"
#include "Board.h"
#include <iostream>
#include <random> //���e�����p

//�R���X�g���N�^
Board::Board() {
	initBoard();
}

//�Ֆʐ���
void Board::initBoard() {
	//�Ֆʊm��
	board = std::vector<std::vector<Square>>(ROW, std::vector<Square>(COL));
	//�Ֆʂ����ׂĕ���
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].DispState = CLOSED;
			board[y][x].NonDispState = NONE;
		}
	}

	restBombs = BOMBS_NUM;
	restNones = ROW * COL - BOMBS_NUM;
}

//���e�z�u
void Board::initBombs(int cx, int cy) {
	//�Ֆʂɔ��e��z�u����
	std::random_device rnd;
	int cnt = 0;
	while (cnt != BOMBS_NUM) {
		int x = rnd() % COL, y = rnd() % ROW;
		//����ł�����x�J���悤�ɂ���
		if (cx - 1 <= x && x <= cx + 1 &&
			cy - 1 <= y && y <= cy + 1) continue;
		if (board[y][x].NonDispState == BOMB) continue;

		board[y][x].NonDispState = BOMB;
		cnt++;
	}
	//���͂̔��e�̐��𐔂���
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].BombsNum = countBombs(x, y);
		}
	}
}

//���͂̔��e�̐��𐔂���(initBombs�ł̂ݎg�p)
int Board::countBombs(int x, int y) {
	int ret = 0;
	for (int k = 0; k < 8; k++) {
		int nx = x + mx8[k], ny = y + my8[k];
		if (!(0 <= nx && nx < COL && 0 <= ny && ny < ROW)) continue;
		if (board[ny][nx].NonDispState == BOMB) ret++;
	}
	return ret;
}

//�Ֆʕ\��
void Board::dispBoard(const Cursor& cursor) {
	std::cout << "Rest Bombs: " << restBombs << std::endl;
	std::cout << "Rest Nones: " << restNones << std::endl;
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (x == cursor.getCursorX() && y == cursor.getCursorY()) {
				//�J�[�\���ʒu
				std::cout << "�� ";
			}
			else {
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == NONE) std::cout << "�E ";
					else std::cout << " " << board[y][x].BombsNum << " ";
					break;
				case CLOSED:
					std::cout << "�� ";
					break;
				case MARKED:
					std::cout << "�� ";
					break;
				default:
					std::cout << "no";
					break;
				}
			}
		}
		std::cout << std::endl;
	}
}

//�Ֆʕ\��(�I��)
void Board::endDispBoard(const Cursor& cursor) {
	std::cout << "Bombs num: " << BOMBS_NUM << std::endl;
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (x == cursor.getCursorX() && y == cursor.getCursorY() && board[y][x].NonDispState == BOMB) {
				std::cout << "�� "; //���������ꏊ
			}
			else {
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == 0) std::cout << "�E ";
					else std::cout << " " << board[y][x].BombsNum << " ";
					break;
				case CLOSED:
					if (board[y][x].NonDispState == BOMB) std::cout << " B ";
					else std::cout << "�� ";
					break;
				case MARKED:
					if (board[y][x].NonDispState == BOMB) std::cout << "�� ";
					else std::cout << " x ";
					break;
				default:
					std::cout << "no";
					break;
				}
			}
		}
		std::cout << std::endl;
	}
}

//�}�[�N��t����/����
void Board::markBoard(const Cursor& cursor) {
	switch (board[cursor.getCursorY()][cursor.getCursorX()].DispState) {
	case CLOSED:
		board[cursor.getCursorY()][cursor.getCursorX()].DispState = MARKED;
		restBombs--;
		break;
	case MARKED:
		board[cursor.getCursorY()][cursor.getCursorX()].DispState = CLOSED;
		restBombs++;
		break;
	default: break;
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
			if (board[ny][nx].DispState != CLOSED) continue;
			openSquare(nx, ny);
		}
	}
}

bool Board::isFirstOpen() const{
	if (restNones != ROW * COL - BOMBS_NUM) return false;
	else return true;
}

//�w��}�X�ɒu�����true��Ԃ�
bool Board::isOpenSquare(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].DispState != CLOSED) return false;
	else return true; //�u����
}

//�w��}�X�ɔ��e�������true��Ԃ�
bool Board::isGameOver(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].NonDispState != BOMB) return false;
	else return true; 
}

//�󂯂���}�X���Ȃ����true��Ԃ�
bool Board::isGameClear() {
	if (restNones != 0) return false;
	else return true;
}

Board::~Board()
{
}
