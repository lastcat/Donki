#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
//ファイホール対応のcpの意味がよくわからない。サンプルのcopy.c実行してもcopyされているように思う
//
int main(){
  /*
  //まずfile holeを作ってみる
  int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int outputFd = open("filehole.txt",openFlags, filePerms);
  //この時点でoffsetはzeroのはず
  write(outputFd, "hoge", 4);
  int nowOffset = lseek(outputFd, 100, SEEK_CUR);
  printf("now:%d\n", nowOffset);
  write(outputFd, "fuga", 4);
  close(outputFd);
  */
/*
  int readFd = open("nfilehole.txt", O_RDONLY, NULL);
  int numRead;
  char buf[1];
  int now;
  while((numRead = read(readFd, buf, 1)) > 0){
    write(STDIN_FILENO, buf, 1);
    now = lseek(readFd, 0, SEEK_CUR);
    printf("now:%d\n",now);
  }
*/
}
