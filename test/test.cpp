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

	string change_text1("N:");													//既存データに会社名を追加 するファクターを定義
	string change_text11("ORG:");
	string change_text111("株式会社");
	string company_set("社名読み: ");											//会社名を設定するファクター
	string company_search("グループ: ");										// \n 文字を検出できないのでその次の文字列を検出します
	string set_text1(" ");														//既存データに会社名を追加

	string insert_place2("X-PHONETIC-FIRST-NAME:");								//この文字列を検出したならばsort_string	を追加する

	string change_text2("SORT-STRING:");										//ソートタグを新たに追加する

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

			//各個人の最初の項目 を検出した際会社名を更新する
			for(int j=i;; j++) {

				//社名読みを検出するまで操作します
				if(text_copy[j].rfind(change_text11) != -1) {

					int len1 = text_copy[j].rfind(change_text11);				//ORG読みまでの先端からの長さ

					string tmp = change_text11;
					tmp += change_text111;

					if(text_copy[j].rfind(tmp) != -1) {

						set_text1 = text_copy[j].substr(len1 + change_text11.length() + change_text111.length());

					} else {

						set_text1 = text_copy[j].substr(len1 + change_text11.length(),
								text_copy[j].length() - change_text11.length() - change_text111.length());
					}

					break;
				}
			}

			//N: のところに会社名を追加します
			text_copy[i].insert(2,set_text1);
			text_copy[i].insert(2 + set_text1.length(),") ");


		//会社名を追加する条件に合致するならば書き込み パターン2
		} else if(!text_copy[i].find(change_text3)) {

			//X-PHONETIC-LAST-NAME: のところに会社名を追加します
			text_copy[i].insert(change_text3.length(),set_text1);
			text_copy[i].insert(change_text3.length() + set_text1.length(),") ");

		//sort_tagを追加する条件
		} else if(!text_copy[i].find(insert_place2)) {

			//各個人の最初の項目 を検出した際会社名を更新する
			for(int j=i;; j++) {

				//社名読みを検出するまで操作します
				if(text_copy[j].rfind(company_set) != -1) {

					int len1 = text_copy[j].rfind(company_set);					//社名読みまでの先端からの長さ
					int len2 = text_copy[j].rfind(company_search);				//改行文字の2つ後ろまでの長さ

					//rfind は検出した文字の先頭を返すので検出した文字分進めるか戻す必要がある -2 は改行文字数
					set_text1 = text_copy[j].substr(len1 + company_set.length(),len2 - len1 - company_search.length() - 2);

					break;
				}
			}

			change_text2 += set_text1;
			change_text2 += " ";
			change_text2 += text_copy[i + 1].substr(21);						//21はchange_text3の文字数 この後ろに苗字のフリガナがある
			change_text2 += " ";												//空白で苗字と名前を区切ります
			change_text2 += text_copy[i].substr(22);							//22はinsert_place2の文字数 この後ろに名前のフリガナがある

			//先にストリームに挿入してソートタグを追加する
			ofstream_fail << change_text2<< " \n";

			//挿入したので素のソートタグに戻します
			change_text2 = "SORT-STRING:";
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
