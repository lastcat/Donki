#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
  int fd1 = open("file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  int fd2 = dup(fd1);
  int fd3 = open("file", O_RDWR);
  write(fd1, "Hello,", 6);
  write(fd2, " world", 6);
  //ここまでで"file"ファイルが"Hello,world"
  lseek(fd2, 0, SEEK_SET);
  write(fd1, "HELLO,", 6);
  //HELLO<world
  write(fd3, "Gidday", 6);
  //ここでfd3はfile offsetは共有していないので結局上書きされて"Gidday world"になる

}
