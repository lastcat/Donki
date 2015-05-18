#include <stdio.h>
#include <stdlib.h>

int main(){
  printf("before:%p\n", sbrk(0));
  char *str = (char*)malloc(10);
  str[0] = 'a';
  str[1] = 'b';
  printf("after:%p\n", sbrk(0));
  printf("%c, %c\n", str[0], str[1]);
  return 0;
}
