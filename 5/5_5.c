#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>
//dupの動作確認的な

int main(int argc, char* argv[]){
  int openFlags =  O_CREAT | O_WRONLY | O_TRUNC;
  int fd = open("test.txt", openFlags, 0666);
  int dupped_fd = dup(fd);
  write(fd, "ohe", 3);
  //続きに書き込まれるはず
  write(dupped_fd , "two", 3);
  lseek(dupped_fd, 0, SEEK_SET);
  //先頭から書きこまれるはず　上書きされるので"threeo"となる
  write(fd, "three", 5);

  int flags = fcntl(fd, F_GETFL);
  int dupped_flags = fcntl(dupped_fd, F_GETFL);
  if(flags == dupped_flags)
    printf("open file status flag一致\n");
}
