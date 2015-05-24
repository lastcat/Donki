#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt){
  int sumBytes = 0;
  for(int i = 0; i < iovcnt; i++){
    if(read(fd, iov[i].iov_base, iov[i].iov_len) != 0)
      sumBytes += iov[i].iov_len;
    else
      return 0;
  }
  return sumBytes;
}

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt){
  //バッファを利用してatomicity(?)を実現する
  int sumBytes = 0;
  for(int i = 0; i < iovcnt; i++){
    sumBytes += iov[i].iov_len;
  }
  char *buf = (char*)calloc(sumBytes, 1);
  for(int i = 0; i < iovcnt; i++){
    strcat(buf, iov[i].iov_base);
  }
  write(fd, buf, sumBytes);
  return sumBytes;
}

int main(int argc, char *argv[]){
/*
  //簡単なwritevの検証
  struct iovec array[3];
  array[0].iov_base = "one\n";
  array[0].iov_len = 4;

  array[1].iov_base = "two\n";
  array[1].iov_len = 4;

  array[2].iov_base = "three\n";
  array[2].iov_len = 6;

  my_writev(STDIN_FILENO, array, 3);
  */

//本のコードのreadvをmyreadvに置き換えたもの。問題なさそう？(readvの検証)
  int fd;
      struct iovec iov[3];
      struct stat myStruct;
      int x;
  #define STR_SIZE 100
      char str[STR_SIZE];
      ssize_t numRead, totRequired;

      if (argc != 2 || strcmp(argv[1], "--help") == 0)
          usageErr("%s file\n", argv[0]);

      fd = open(argv[1], O_RDONLY);
      if (fd == -1)
          errExit("open");

      totRequired = 0;

      iov[0].iov_base = &myStruct;
      iov[0].iov_len = sizeof(struct stat);
      totRequired += iov[0].iov_len;

      iov[1].iov_base = &x;
      iov[1].iov_len = sizeof(x);
      totRequired += iov[1].iov_len;

      iov[2].iov_base = str;
      iov[2].iov_len = STR_SIZE;
      totRequired += iov[2].iov_len;

      numRead = my_readv(fd, iov, 3);
      if (numRead == -1)
          errExit("readv");

      if (numRead < totRequired)
          printf("Read fewer bytes than requested\n");

      printf("total bytes requested: %ld; bytes read: %ld\n",
              (long) totRequired, (long) numRead);
      exit(EXIT_SUCCESS);
}
