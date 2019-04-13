// MinesweeperObj.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>

int main()
{
	Cursor cursor;
	Board board;

	while (true) {
		system("cls"); //画面クリア
		board.dispBoard(cursor); //盤面出力

		switch (cursor.operateCursor()) { //カーソル操作
			case 'f': break;
			case 'e': board.markBoard(cursor); continue;
			default : continue;
		}
		if (!board.isOpenSquare(cursor)) continue; //指定したマスを開けられるか

		if (board.isGameOver(cursor)) { //敗北
			system("cls");
			board.endDispBoard(cursor);
			std::cout << "You lose..." << std::endl;
			break;
		}

		board.openSquare(cursor.getCursorX(), cursor.getCursorY()); //マスを開ける

		if (board.isGameClear()) { //勝利
			system("cls");
			board.endDispBoard(cursor);
			std::cout << "You win !!" << std::endl;
			break;
		}
	}

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
