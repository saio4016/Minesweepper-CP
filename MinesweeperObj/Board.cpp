#include "pch.h"
#include "Board.h"
#include <iostream>
#include <random> //爆弾生成用

//コンストラクタ
Board::Board() {
	initBoard();
}

//盤面生成
void Board::initBoard() {
	//盤面確保
	board = std::vector<std::vector<Square>>(ROW, std::vector<Square>(COL));
	//盤面をすべて閉じる
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].DispState = CLOSED;
			board[y][x].NonDispState = NONE;
		}
	}

	restBombs = BOMBS_NUM;
	restNones = ROW * COL - BOMBS_NUM;
}

//爆弾配置
void Board::initBombs(int cx, int cy) {
	//盤面に爆弾を配置する
	std::random_device rnd;
	int cnt = 0;
	while (cnt != BOMBS_NUM) {
		int x = rnd() % COL, y = rnd() % ROW;
		//初手である程度開くようにする
		if (cx - 1 <= x && x <= cx + 1 &&
			cy - 1 <= y && y <= cy + 1) continue;
		if (board[y][x].NonDispState == BOMB) continue;

		board[y][x].NonDispState = BOMB;
		cnt++;
	}
	//周囲の爆弾の数を数える
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].BombsNum = countBombs(x, y);
		}
	}
}

//周囲の爆弾の数を数える(initBombsでのみ使用)
int Board::countBombs(int x, int y) {
	int ret = 0;
	for (int k = 0; k < 8; k++) {
		int nx = x + mx8[k], ny = y + my8[k];
		if (!(0 <= nx && nx < COL && 0 <= ny && ny < ROW)) continue;
		if (board[ny][nx].NonDispState == BOMB) ret++;
	}
	return ret;
}

//盤面表示
void Board::dispBoard(const Cursor& cursor) {
	std::cout << "Rest Bombs: " << restBombs << std::endl;
	std::cout << "Rest Nones: " << restNones << std::endl;
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (x == cursor.getCursorX() && y == cursor.getCursorY()) {
				//カーソル位置
				std::cout << "● ";
			}
			else {
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == NONE) std::cout << "・ ";
					else std::cout << " " << board[y][x].BombsNum << " ";
					break;
				case CLOSED:
					std::cout << "□ ";
					break;
				case MARKED:
					std::cout << "◎ ";
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

//盤面表示(終局)
void Board::endDispBoard(const Cursor& cursor) {
	std::cout << "Bombs num: " << BOMBS_NUM << std::endl;
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (x == cursor.getCursorX() && y == cursor.getCursorY() && board[y][x].NonDispState == BOMB) {
				std::cout << "☆ "; //爆発した場所
			}
			else {
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == 0) std::cout << "・ ";
					else std::cout << " " << board[y][x].BombsNum << " ";
					break;
				case CLOSED:
					if (board[y][x].NonDispState == BOMB) std::cout << " B ";
					else std::cout << "□ ";
					break;
				case MARKED:
					if (board[y][x].NonDispState == BOMB) std::cout << "◎ ";
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

//マークを付ける/消す
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

//board[y][x].DispStateを開ける(isOpenSquareで確認してから使う)
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

//指定マスに置ければtrueを返す
bool Board::isOpenSquare(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].DispState != CLOSED) return false;
	else return true; //置ける
}

//指定マスに爆弾があればtrueを返す
bool Board::isGameOver(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].NonDispState != BOMB) return false;
	else return true; 
}

//空けられるマスがなければtrueを返す
bool Board::isGameClear() {
	if (restNones != 0) return false;
	else return true;
}

Board::~Board()
{
}
