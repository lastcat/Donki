//initgroupsを実装せよ(setgruos()と8章の関数をつかうこと)
#define _BSD_SOURCE
#include <grp.h>
#include <pwd.h>
#include <limits.h>
#include "../lib/tlpi_hdr.h"
#include <unistd.h>
#include "ugid_functions.h"

gid_t groups[NGROUPS_MAX];
#define SG_SIZE (NGROUPS_MAX + 1)
int errorno;

int my_initgroups(const char *user, gid_t group){
  //initは本来あるべき形に戻す 8章の関数使って本来のgroupを探す
  //指定ユーザーが所属してるグループを確保
  setgrent();
  struct group *grp;
  char *member;
  int j = 0;
  while((grp = getgrent()) != NULL){
    //printf("group:%s\n", grp->gr_name);
    int i = 0;
    printf("check %s(%d)\n", grp -> gr_name, grp -> gr_gid);

    //ここかそもそもgetgrentだけではダメだという可能性
    //etc/groupでuser fieldが空欄になっているgroupについて正常に動作していない、というかそこの扱いわからない
    //Linuxで確認したい
    while( (member=(grp -> gr_mem)[i]) != NULL){

      if(strcmp(user, member) == 0){
        //groups[j] = (grp -> gr_gid);
        //printf("insert:%d\n", groups[j]);
        //strcpy(groups[j],  grp->gr_name);
        printf("belongs to:%s\n", grp -> gr_name);
        j++;
      }
      i++;
    }

  }
  /*
  for(int h = 0; h < j; h++){
    printf("%d\n",groups[h]);
  }
  //plus 指定 gid(group)
  //setgroups(j, groups);
  */
}

void  print_groups(void) {
  //現状のprocessの追加グループを出力する id_showより一部引用
  int i,j;
  char *p;
  gid_t suppGroups[SG_SIZE];
  int numGroups = getgroups(SG_SIZE, suppGroups);
  if (numGroups == -1)
      errExit("getgroups");

  printf("Supplementary groups (%d): ", numGroups);
  for (j = 0; j < numGroups; j++) {
      p = groupNameFromId(suppGroups[j]);
      printf("%s (%ld) ", (p == NULL) ? "???" : p, (long) suppGroups[j]);
      printf("\n");
  }

}
int main(int argc, char* argv[]){
  print_groups();
  gid_t test[] = {1};
  printf("--------RESET SUP GID----------\n");
  setgroups(1,test);
  print_groups();
  printf("--------INIT SUP GID----------\n");
  my_initgroups("root", -1);
  print_groups();
  printf("errorno:%d\n", errorno);
}
