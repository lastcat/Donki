//getenvとputenvを使ってsetenvとunsetenvを実装
#include "../lib/tlpi_hdr.h"
#define BUF 1024
extern char **environ;
int my_setenv(const char *name, const char *value, int overwrite){
  //putenvの引数はname=strなんでその形に整形する
  char str[BUF] = { 0 };
  strcat(str, name);
  strcat(str, "=");
  strcat(str, value);

  if(overwrite != 0)
    putenv(str);
  else{
    if((getenv(name)) == NULL)
      putenv(str);
    else
      return 0;
  }
}
int my_unsetenv(char* string){
  //unsetは適当にnull入れればいいのだろうか。
  if(getenv(string) != NULL){
    int i;
    for(i = 0; environ[i] != NULL; i++);
    environ[i-1] = NULL;
  }
  else
    return 0;
}

void print_env(void){
  for(int i = 0; environ[i] != NULL; i++){
    printf("%d:%s\n", i, environ[i]);
  }
}

int main(int argc, char* argv[]){
  print_env();
  my_setenv("hoge", "fuga", 0);
  print_env();
  my_setenv("hoge", "piyo", 1);
  //overwriteするので入れ替わる
  print_env();
  my_setenv("hoge", "uoooo", 0);
  //overwriteしない
  print_env();
  my_unsetenv("hoge");
  print_env();
}
