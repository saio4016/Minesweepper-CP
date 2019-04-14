#include "pch.h"
#include "Board.h"
#include <cstdio>
#include <random> //爆弾生成用

//コンストラクタ
Board::Board() {
	initBoard();
}

//初期設定(コンストラクタで呼び出し)
void Board::initBoard() {
	//盤面確保
	board = std::vector<std::vector<Square>>(ROW, std::vector<Square>(COL));
	//盤面初期化
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].DispState = CLOSED;
			board[y][x].NonDispState = NONE;
		}
	}
	//変数の初期化
	restBombs = BOMBS_NUM; //表示の関係で最初から爆弾があることとする
	restNones = ROW * COL;
}

//爆弾設定
void Board::initBombs(const Cursor& cursor) {
	int cx = cursor.getCursorX(), cy = cursor.getCursorY();
	//盤面に爆弾を配置する
	std::random_device rnd;
	while (restNones != ROW*COL-BOMBS_NUM) {
		int x = rnd() % COL, y = rnd() % ROW;
		//(cx,cy)から、ある程度開くようにする
		if (cx - 1 <= x && x <= cx + 1 && cy - 1 <= y && y <= cy + 1) continue;
		//すでに(x,y)に爆弾があれば選び直し
		if (board[y][x].NonDispState == BOMB) continue;
		board[y][x].NonDispState = BOMB;
		restNones--;
	}
	//任意のマスの周囲の爆弾の数を数える
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			board[y][x].BombsNum = countBombs(x, y);
		}
	}
}

//周囲の爆弾の数を数える(initBombsで使用)
int Board::countBombs(int x, int y) {
	int ret = 0;
	for (int k = 0; k < 8; k++) {
		int nx = x + mx8[k], ny = y + my8[k];
		if (!(0 <= nx && nx < COL && 0 <= ny && ny < ROW)) continue;
		if (board[ny][nx].NonDispState == BOMB) ret++;
	}
	return ret;
}

//盤面表示(基準)
void Board::dispFirstBoard() {
	std::printf("Rest Bombs: %d\n", BOMBS_NUM);
	std::printf("Rest Nones: %d\n", ROW * COL);
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			std::printf("□ ");
		}
		std::printf("\n");
	}
}

//盤面表示(最後)
void Board::dispEndBoard(const Cursor& cursor) {
	std::printf("Bombs num : %d\n", BOMBS_NUM);
	std::printf("Rest Nones: %d\n", restNones);
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (x == cursor.getCursorX() && y == cursor.getCursorY() &&
				board[y][x].NonDispState == BOMB) {
				std::printf("☆ "); //爆発した場所
			}
			else {
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == 0) std::printf("・ ");
					else std::printf(" %d ",board[y][x].BombsNum);
					break;
				case CLOSED:
					if (board[y][x].NonDispState == BOMB) std::printf(" B ");
					else std::printf("□ ");
					break;
				case MARKED:
					if (board[y][x].NonDispState == BOMB) std::printf("◎ ");
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

//rest表示反映
void Board::updateRest() {
	//変更する場合は微調整が必要
	std::printf("\033[1;12H %d  ", restBombs);
	std::printf("\033[2;12H %d  ", restNones);
}

//盤面反映(boardで使用)
void Board::updateBoard(const Board& preboard) {
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (board[y][x].DispState != preboard.getDispState(x, y)) { //前の盤面との変更点
				std::printf("\033[%d;%dH", y + 3, x * 3 + 1);           //変更する場合には微調整が必要
				switch (board[y][x].DispState) {
				case OPENED:
					if (board[y][x].BombsNum == NONE) std::printf("・ ");
					else std::printf(" %d ", board[y][x].BombsNum);
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
			}
		}
	}
}

//マークを付ける/消す
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

//board[y][x].DispStateを開ける(isOpenSquareで確認してから使う)
void Board::openSquare(int x, int y) {
	board[y][x].DispState = OPENED;
	restNones--;
	if (board[y][x].BombsNum == 0) {
		for (int k = 0; k < 8; k++) {
			int nx = x + mx8[k], ny = y + my8[k];
			if (!(0 <= nx && nx < COL && 0 <= ny && ny < ROW)) continue;
			if (board[ny][nx].DispState != CLOSED) continue; //OPENEDまたはMARKED
			openSquare(nx, ny);
		}
	}
}

//盤面コピー(preBoardで使用)
void Board::copyBoard(const Board& board) {
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			this->board[y][x].DispState = board.getDispState(x, y);
		}
	}
}

//board[y][x].DispStsteを取得
int Board::getDispState(int x, int y) const {
	return board[y][x].DispState;
}

//board[y][x].BombsNumを取得
int Board::getBombsNum(int x, int y) const {
	return board[y][x].BombsNum;
}

//初手ならtrueを返す
bool Board::isFirstOpen() {
	if (restNones == ROW * COL) return true;
	else return false;
}

//指定マスに置ければtrueを返す
bool Board::isOpenSquare(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].DispState == CLOSED) return true;
	else return false; //置ける
}

//指定マスに爆弾があればtrueを返す
bool Board::isGameOver(const Cursor& cursor) {
	if (board[cursor.getCursorY()][cursor.getCursorX()].NonDispState == BOMB) return true;
	else return false;
}

//空けられるマスがなければtrueを返す
bool Board::isGameClear() {
	if (restNones == 0) return true;
	else return false;
}

Board::~Board() {
}
