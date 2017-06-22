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

	string change_text1("FN:");													//既存データに会社名を追加 するファクターを定義
	string set_text1("ゼネテック)");											//既存データに会社名を追加

	string insert_place2("X-PHONETIC-FIRST-NAME:");								//この文字列を検出したならばsort_string	を追加する

	string change_text2("SORT-STRING:ゼネテック ");								//ソートタグを新たに追加する

	string change_text3("X-PHONETIC-LAST-NAME:");								//既存データに会社名を追加するファクターを定義

	string text_copy[count_line];												//テキストファイルの文字列を行ごとに格納する配列

	//カウントした文字列分 ファイルを走査し、メモリに一時的にファイルの中身をコピー
	for (int i = 0; i < count_line; i++) {

		getline(ifstream_fail, text_copy[i]);									//1行の終端部分 改行文字までをメモリに格納
	}

	//文字列の書き込みを行うためにループします
	for(int i=0; i < count_line; i++) {

		//会社名を追加する条件に合致するならば書き込み パターン1
		if(!text_copy[i].find(change_text1)) {

			//FN: のところに会社名を追加します
			text_copy[i].insert(3,set_text1);

		//会社名を追加する条件に合致するならば書き込み パターン2
		} else if(!text_copy[i].find(change_text3)) {

			//X-PHONETIC-LAST-NAME: のところに会社名を追加します
			text_copy[i].insert(21,set_text1);

		//sort_tagを追加する条件
		} else if(!text_copy[i].find(insert_place2)) {

			change_text2 += text_copy[i].substr(22);							//22はinsert_place2の文字数 この後ろに名前のフリガナがある
			change_text2 += " ";												//空白で苗字と名前を区切ります
			change_text2 += text_copy[i + 1].substr(21);						//21はchange_text3の文字数 この後ろに苗字のフリガナがある

			//先にストリームに挿入してソートタグを追加する
			ofstream_fail << change_text2<< " \n";

			//挿入したので素のソートタグに戻します
			change_text2 = "SORT-STRING:ゼネテック ";
		}

			//配列に格納されている文字列を書き込みます
			ofstream_fail << text_copy[i] << "\n";
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
