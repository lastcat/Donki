#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include "../lib/get_num.h"
#include <sys/stat.h>
#include <fcntl.h>

//fcntlでdupとdup2を実装
//dup:old fdを引数にとって、新しい(複製した)fdを返す
//dup2:old fdをnew fdを引数にとってswapする

int my_dup(int oldfd){
  return fcntl(oldfd, F_DUPFD, 0);
}

int my_dup2(int oldfd, int newfd){
  //oldfdとnewfdが一致してるケース、oldfdが有効か確かめる必要がある、とあるがよくわからない。
  //この実装だと、有効な場合、先に閉じてしまうので一致してたら何もしないというのを書けばそれで良いと思うのだけど。
  if(oldfd == newfd)
    return oldfd;
  close(newfd);
  return fcntl(oldfd, F_DUPFD, oldfd);
}

int main(int argc, char *argv[]){
  int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  int fd1 = open("file1.txt", openFlags, 0666);
  int fd2 = open("file2.txt", openFlags, 0666);

  //これはfile1に書き込まれるはず
  write(fd1, "hoge", 4);
  int fd1_dupped = my_dup(fd1);
  //これもfile1に書き込まれるはず
  write(fd1_dupped, "fuga", 4);
  //fd2のfdをstdinにdupする
  my_dup2(STDIN_FILENO, fd2);
  //これは標準出力に書き込まれるはず
  write(fd2, "piyo", 4);
  //my_dup2のfd一致処理
  my_dup2(fd2, fd2);
  write(fd2, "ugauga", 6);

}
