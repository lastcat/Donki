//9_4と同じことをやる。ただし、
//real=X, effective=0, saved=0
#include "../lib/tlpi_hdr.h"


void problemA(void) {
  //effective=real
  uid_t real;
  uid_t effective;
  uid_t saved;
  getresuid(&real, &effective, &saved);
  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);

  //setresuid(-1, real, -1);
  ///* or
  seteuid(real);
  //*/
  getresuid(&real, &effective, &saved);
  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);

  //setresuid(-1, saved, -1);
  ///*
  seteuid(saved);
  //*/
  getresuid(&real, &effective, &saved);
  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);

}

void problemB(void){
  uid_t real;
  uid_t effective;
  uid_t saved;
  getresuid(&real, &effective, &saved);
  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);

  setresuid(-1, real, -1);
  getresuid(&real, &effective, &saved);
  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);

  setresuid(-1, -1, real);
  getresuid(&real, &effective, &saved);
  printf("initial real:%d, effective:%d, saved%d\n", real, effective, saved);
}

int main(){
  problemB();
}
