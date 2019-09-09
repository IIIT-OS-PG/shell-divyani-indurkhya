#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
using namespace std;

void bashinitial()
{
  FILE *fp;
  fp = fopen("bash.txt", "w");
  // struct passwd *pw = getpwuid(getuid());

  // const char *homedir = pw->pw_dir;
  // const char *homedir1 = pw->pw_shell;
  // setenv("USER", pw->pw_name, 1);
  // printf("%s\n",getenv("USER"));
  fprintf(fp, "$PATH=");
  fprintf(fp, getenv("PATH"));
  fprintf(fp, "\n");
  fprintf(fp, "$HOME=");
  fprintf(fp, getenv("HOME"));
  fprintf(fp, "\n");
  fprintf(fp, "$USER=");
  fprintf(fp, getenv("USER"));
  fprintf(fp, "\n");
  fprintf(fp, "$USERNAME=");
  fprintf(fp, getenv("USERNAME"));
  fprintf(fp, "\n");
  fprintf(fp, "$PWD=");
  fprintf(fp, getenv("PWD"));
  fprintf(fp, "\n");
  fprintf(fp, "$LOGNAME=");
  fprintf(fp, getenv("LOGNAME"));
  fprintf(fp, "\n");
  fprintf(fp, "$PROMPT=$\n");
  fclose(fp);

}