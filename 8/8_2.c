//setpwent. getpwent, endpwentを使ってgetpwnamを実装
#include "../lib/tlpi_hdr.h"
#include <pwd.h>
struct passwd *my_getpwnam(const char *name){
  struct passwd *pwd;
  //printf("user name:%s\n", name);
  while((pwd = getpwent()) != NULL){
    printf("name %s\n", pwd->pw_name);
    if (strcmp(pwd->pw_name, name) == 0)
      break;
  }
  endpwent;
  return pwd;
}


int main(){
  struct passwd *pwd = my_getpwnam("root");

  printf("my_getwnam's result is :%s\n",pwd->pw_gecos);
}
