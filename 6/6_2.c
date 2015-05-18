#include <setjmp.h>
#include <unistd.h>
//#include "../lib/tlpi_hdr.h"

//すでにreturnした関数内にlongjmp
static jmp_buf env;

void jumpSet(void){
  setjmp(env);
  write(STDIN_FILENO, "jump set\n", 9);
  return;
}

void do_jump(void){
  write(STDIN_FILENO, "jump do\n", 8);
  longjmp(env, 1);
  return;
}

int main(int argc, char* argv[]){
  jumpSet();
  do_jump();
  //output;jump set -> jump do -> jump set つまりreturnした後の関数にもjumpできている。
  //本によるとスタックにない関数を探して異常な動作をするとあるが、はて。スタックフレームの理解がまちがっている？
  //模範解答(bad longjump)のように、一つ「またいで」いると落ちる、直接だと普通にmainに帰ってくる
  //IDEONEだと無限にjumpsetを繰り返して落ちている。処理系依存っぽい。
  //サンプルコード(bad_longjump.c)が関数を二重にしている理由は謎。
  write(STDIN_FILENO, "main\n", 5);
  perror("error?");
  return 0;
}
