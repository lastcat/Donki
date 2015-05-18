//仕様:atomic_append filename num-bytes [x]
//filenameをopenして、num-bytes分のデータを末尾に1byteずつ追加する
//多分てきとうなcharでいいと思う
//defaultではO_APPENDを、xオプションが与えられた時はAPPENDを使わずwriteの前にlseek(fd, 0 , SEEK_END)を実行する

#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
  //めんどくさいのでargcだけで決め打ち分岐
  int x_mode = 0;
  char *writeChar;
  if(argc == 5){
    x_mode = 1;
    writeChar = argv[4];
  }
  else if(argc == 4){
    x_mode = 0;
    writeChar = argv[3];
  }
  else
    usageErr("number of arguments invalid");

  int openFlags;
  if(x_mode == 1)
    openFlags = O_CREAT | O_WRONLY;
  else
    openFlags = O_CREAT | O_WRONLY | O_APPEND;

  int fd = open(argv[1], openFlags, 0666);
  for(int i = 0;i < atoi(argv[2]); i++){
    if(x_mode == 1)lseek(fd, 0 , SEEK_END);
    if((write(fd, writeChar, 1)) != 1){
      fatal("書き込み失敗");
    }
  }
  close(fd);
  //異なるプロセスで同じファイルをopenした場合、異なるオープンファイル情報で同じinodeテーブルを参照する。このとき
  //ファイルオフセットは共有されないので、
  //lseek1(file offset 1) -> (file offset 1に別プロセスがwrite) -> file offset 1に別プロセスがwrite
  //となり上書きされて消されてしまうことが起こると考えられる。
  //atomicだと上のような割り込みが生じないのでfile offsetを共有してなくても(順番はめちゃめちゃになるけど)ちゃんと2回分書き込まれる。 
}
