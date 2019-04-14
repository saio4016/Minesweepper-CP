// MinesweeperObj.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

  /********************************************
  Name      ：MinesweeperObj.cpp
  Function  ：Minesweeper
  Author    ：saio4016
  Date      ：2019/04/14(last update:2019/04/14)
  Language  ：C++
  IDE/Editor：Visual Studio 2017
  Time      ：2days
  Notices   ： Guide(↓)
			  ・w = up, a = left, s = down, d = right
			  ・e = flag, f = select

  ********************************************/

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

int main()
{
	//カーソル非表示(コピペ)
	HANDLE hOut;
	CONSOLE_CURSOR_INFO cci;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);               //出力用ハンドルの取得
	GetConsoleCursorInfo(hOut, &cci);                     //CONSOLE_CURSOR_INFO構造体の現在の状態を取得する
	cci.bVisible = false;                                 //メンバ変数のbVisibleがカーソルの表示・非表示を制御する変数
	SetConsoleCursorInfo(hOut, &cci);                     //変更した構造体情報をコンソールWindowにセットする

	char c;
	std::printf("Press to start"); _getch();
	std::system("cls");

	//////////ここからゲーム開始

	Cursor cursor, preCursor;                             //カーソル
	Board board, preBoard;                                //盤面

	board.dispFirstBoard();                               //基準となる盤面表示
	while (true) {
		board.updateRest();                               //残り(爆弾/空きマス)数更新
		cursor.updateCursor(board, preCursor);            //カーソル更新
		preCursor.copyCursor(cursor);                     //カーソル位置保存

		if (!cursor.operateCursor(board)) continue;       //カーソル操作
		if (board.isFirstOpen()) board.initBombs(cursor); //爆弾設定
		if (!board.isOpenSquare(cursor)) continue;        //指定したマスを開けられるか

		if (board.isGameOver(cursor)) {                   //敗北
			system("cls"); std::printf("\x1b[31m");       //画面クリア/文字色を赤に
			board.dispEndBoard(cursor);
			std::printf("You died...\n");
			break;
		}

		board.openSquare(cursor.getCursorX(),
			             cursor.getCursorY());            //マスを開ける
		board.updateBoard(preBoard);

		if (board.isGameClear()) {                        //勝利
			system("cls"); std::printf("\x1b[36m");       //画面クリア/文字色をシアンに
			board.dispEndBoard(cursor);
			std::printf("You survived !\n");
			break;
		}
	}

	//////////ここでゲーム終了
	for (int i = 0; i < 10; i++) _getch();
	std::system("cls");
	std::printf("\x1b[39m");
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
