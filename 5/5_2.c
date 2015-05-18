#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
  int openFlags = O_CREAT | O_WRONLY | O_APPEND;
  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int fd = open("test.txt",openFlags,NULL);
  printf("now file offset:%lld\n",   lseek(fd,0,SEEK_SET));
  write(fd, "hoge", 4);
  close(fd);
}
//結論:末尾に書き込まれる。つまり、APPENDフラグが優先される
//APPENDフラグは単に最初のfile offsetを末尾にするだけではなくて、その後の書き込みに対しても
//file offsetを末尾移動して書き込む、という動作をatomicに行うということを指しているので、このようになる
