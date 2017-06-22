/* 演習 社長からの課題
 *
 * スタート 2017年6月21日
 *
 * 作成者 平澤敬介
 */

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cstdio>
#include <cstdlib>

using namespace std;

//関数宣言
int get_line(const char* tmp);

int main(int argc,const char* argv[])
{
	//int count_line = get_line("origin.txt");									//関数により行数を得る テキストの行数をカウントする

	//ifstream ifstream_fail("origin.txt");										//素データ アドレス 細井延明
	//ofstream ofstream_fail("output.txt");										//出力ファイル名 コマンドライン引数で指定する

	int count_line = get_line(argv[1]);											//関数により行数を得る テキストの行数をカウントする

	//ファイルが無い場合 は修正処理を行いません
	if(count_line != -1) {

	ifstream ifstream_fail(argv[1]);											//素データ アドレス 細井延明
	ofstream ofstream_fail(argv[2]);											//出力ファイル名 コマンドライン引数で指定する

	const int change_line1 = 2;												//既存データを更新する行 0行目からスタートして実質3行目
	const string change_text1("FN:ゼネテック）細井延明");						//既存データに会社名を追加

	const int change_line2 = 4;												//既存データに新たにソートタグを追加する行
	const string change_text2("SORT-STRING:ゼネテック ノブアキ ホソイ");		//ソートタグを新たに追加する

	const int change_line3 = 6;												//追加した行を反映させ実質7行目の文字列を指定する
	const string change_text3("X-PHONETIC-LAST-NAME:ゼネテック）ホソイ");		//既存データに会社名を追加

	string text_copy[count_line];												//テキストファイルの文字列を行ごとに格納する配列

	//カウントした文字列分 ファイルを走査し、メモリに一時的にファイルの中身をコピー
	for (int i = 0; i < count_line; i++) {

		getline(ifstream_fail, text_copy[i]);									//1行の終端部分 改行文字までをメモリに格納
	}

	//カウントした文字列分 ファイルを走査し書き込みを行う 修正仕様により変更する手前まで走査
	for (int i = 0; i < change_line1; i++) {

		ofstream_fail << text_copy[i] << "\n";									//配列に格納されている1行分を改行文字を含めて書き込み
	}

	//修正仕様により会社名を追加する変更を行います
	ofstream_fail << change_text1 << "\n";

	//カウントした文字列分 ファイルを走査し書き込みを行う 修正仕様により変更する手前まで走査
	for (int i = change_line1 + 1; i < change_line2; i++) {

		ofstream_fail << text_copy[i] << "\n";									//配列に格納されている1行分を改行文字を含めて書き込み
	}

	//修正仕様によりソート文字列タグを追加します
	ofstream_fail << change_text2 << "\n";

	//カウントした文字列分 ファイルを走査し書き込みを行う 修正仕様により変更する手前まで走査
	for (int i = change_line2; i < change_line3 - 1; i++) {

		ofstream_fail << text_copy[i] << "\n";									//配列に格納されている1行分を改行文字を含めて書き込み
	}

	//修正仕様により会社名を追加する変更を行います
	ofstream_fail << change_text3 << "\n";

	//カウントした文字列分 ファイルを走査し書き込みを行う 修正仕様により変更する手前まで走査
	for (int i = change_line3; i < count_line; i++) {

		ofstream_fail << text_copy[i] << "\n";									//配列に格納されている1行分を改行文字を含めて書き込み
	}

	//正常に終了したことを確認するため表示します
	cout << "修正が完了しました\n";
	}

	//正常終了
	return 0;
}

//関数 ファイルの行数を調べる
//引数 ファイル名
//返却値 ファイルの行数
int get_line(const char* tmp) {

	int count = 0;													//返却用の変数 行数をカウント

	char line_max[1024];											//最大レコードを設定 この数値以下に文字列が収まっていることが条件
	FILE *fp = fopen(tmp , "r" );									//ファイルオープン char*型で受け取り ファイルを開く

	//ファイルが開けない場合 NULLが返却されるため
	if( NULL == fp){

		//ファイルが開けない場合に対応
		cout << tmp << "が開けません\n";

		return  -1;												//return で 行数 - 1を返却 ありえないため これ以降の処理を行わない
	}

	//行数をカウント ナル文字を見つけるまで行を探索する
	for(; NULL != fgets(line_max, 1024, fp); count++){
	}

	fclose(fp);													//ファイルを閉じる

	return count;
}
