#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <fcntl.h>
#include <assert.h>
#define linesize 1024
using namespace std;


void history_cmd()
{
    FILE *fp;
  fp = fopen("history.txt", "r");
  char history_dis[1000];
  int linelength=0;
  int hisline=1;
  while(fgets(history_dis, linesize, fp) != NULL) 
    {
        linelength = strlen(history_dis);
printf("%d ",hisline);
        puts (history_dis);
       history_dis[linelength - 1]= ((history_dis[linelength - 1] == '\n')?'\0': history_dis[linelength - 1]);
hisline++;
    }
fclose(fp);
   
}