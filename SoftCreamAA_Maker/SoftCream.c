#include <direct.h>
#include <stdio.h>
#include <string.h>
#define STR_SIZE 100000

int SoftCream(long under_bar);
void output_txt(char* str);

void strcat_space(char* str, long num);
void strcat_under_bar(char* str, long num);

int main(void) {
  char font;
  char result[STR_SIZE] = "";

  puts("デジタルソフトクリームを製造します");
  puts("");

  while (1) {
    puts("使用するフォントを選択してください");
    puts("[A]：MSゴシック");
    puts("[B]：MSPゴシック");
    printf("ここに入力：");
    scanf("%c", &font);
    puts("");

    if (font == 'A') {
      // MSゴシックの場合はアンダーバーが2つ
      SoftCream(2);

    } else if (font == 'B') {
      // MSPゴシックの場合はアンダーバーが3つ
      SoftCream(3);
    } else {
      puts("");
      puts("値が変なので再入力お願いします");

      // 文字の変数に文字列を入力すると変なのが残るのでバッファをクリア
      // 改行コードまでの文字列を読み飛ばし＋改行コードを読み飛ばし
      scanf("%*[^\n]%*c");
      continue;
    }

    break;
  }

  return 0;
}

int SoftCream(long under_bar) {
  long n;
  char result[STR_SIZE] = "";

  while (1) {
    puts("ソフトクリームの段数を入力してください");
    puts("※ゼロやマイナスや変な文字列だと再入力になる");
    printf("ここに入力：");

    int scan = scanf("%ld", &n);

    if (scan != 1 || n <= 0) {
      puts("入力エラーです。やり直してください。\n");

      // 数字の変数に文字を入力すると変なのが残るのでバッファをクリア
      // 改行コードまでの文字列を読み飛ばし＋改行コードを読み飛ばし
      scanf("%*[^\n]%*c");
    } else {
      break;
    }
  }

  puts("");
  puts("デジタルソフトクリームの製造を開始します");

  long space = n;

  strcat_space(result, space);
  strcat(result, "人\n");
  space--;

  for (long i = 1;; i++) {
    strcat_space(result, space);
    strcat(result, "(");
    strcat_under_bar(result, under_bar);
    strcat(result, ")\n");
    space--;
    under_bar += 2;

    if (i == n) {
      break;
    }
  }

  printf("%s", result);
  output_txt(result);
  return 0;
}

void output_txt(char* str) {
  // ファイルの書き込みメモ
  //  https://9cguide.appspot.com/17-01.html#S3
  //  https://bituse.info/c_func/46
  //  https://jp.mathworks.com/help/matlab/ref/fprintf.html
  //  http://www.isl.ne.jp/pcsp/beginC/C_Language_16.html
  //  https://programming-place.net/ppp/contents/c/rev_res/file000.html

  char file_pass[STR_SIZE] = "OutPut_SoftCream\\";
  char tmp_file_pass[STR_SIZE];
  char name[STR_SIZE];

  // フォルダの作成メモ
  //  https://programming.pc-note.net/c/file9.html
  //  https://help.scilab.org/docs/6.1.0/ja_JP/mkdir.html

  mkdir(file_pass);

  while (1) {
    strcpy(tmp_file_pass, file_pass);

    puts("");
    puts("ソフトクリームに名前を付けましょう");
    puts("※これはC言語なのでC++やC#と違って、");
    puts("　日本語の名前を付けることはやや難しい！");
    puts("　なので今回は日本語非対応です！残念だ！");
    printf("ここに入力：");
    scanf("%s", name);
    strcat(name, ".txt");

    FILE* exist = fopen(strcat(tmp_file_pass, name), "r");
    if (exist != NULL) {
      puts("");
      puts("おや…その名前のソフトクリームはもう存在するようです");
      puts("違う名前を考えてみてください");
      puts("");
      fclose(exist);
      continue;
    }
    fclose(exist);

    break;
  }

  FILE* soft_cream = fopen(strcat(file_pass, name), "w");
  fprintf(soft_cream, str, strlen(str));
  fclose(soft_cream);

  puts("");
  puts("ソフトクリームが完成しました。");
  printf("ソフトクリームのファイル名:「%s」\n", name);
  puts("「OutPut_SoftCream」ディレクトリに出ました\n");
}

void strcat_space(char* str, long num) {
  for (long i = 0; i < num; i++) {
    strcat(str, " ");
  }
}

void strcat_under_bar(char* str, long num) {
  for (long i = 0; i < num; i++) {
    strcat(str, "_");
  }
}