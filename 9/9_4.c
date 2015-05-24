//situation:real=X effective=Y saved=Y
//setuid seteuid setreuid setresuidを使って
//1) effective=real => effective=saved
//2)effective=real and saved=real

//適当にroot idをsetuidして、入力によって処理が分岐するようにする
#include "../lib/tlpi_hdr.h"


void problemA(void) {
  //effective=real
  uid_t real = getuid();
  uid_t effective = geteuid();
  uid_t saved = getresuid();

  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);
}

int main(){
  ploblemA();
}
