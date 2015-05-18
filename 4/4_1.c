#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char* argv[]){
  //file name読み取り
  if(argc == 1){
    usageErr("tee (-a) output file: -a option is append mode");
  }
  //オプション数一つだとgetopt使うの微妙なので普通にargv見る
  int fileArg = argc - 1;
  // open output file(パーミッションてきとう)
  int openFlags;
  //optionでmode変える
  if(strcmp(argv[1], "-a") == 0)
    openFlags = O_CREAT | O_WRONLY | O_APPEND;
  else
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int outputFd = open(argv[fileArg], openFlags, filePerms);

  //標準入力read
  char buf[BUF_SIZE];
  ssize_t numRead;
  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0){
    if(write(STDOUT_FILENO, buf, numRead) != numRead){
      fatal("書き込み失敗\n");
      if(numRead == -1)
        errExit("read");
    }
    if(write(outputFd, buf, numRead) != numRead){
      fatal("書き込み失敗\n");
      if(numRead == -1)
        errExit("read");
    }
  }

  //閉じる
  if(close(outputFd) == -1)
    errExit("close output");

    exit(EXIT_SUCCESS);


}
