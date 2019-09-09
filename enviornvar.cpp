#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <fcntl.h>
#include <assert.h>
#define linesize 1024
using namespace std;

void env_var(char *cmd)
{
    FILE *fp;
    fp = fopen("bash.txt", "r");
    int line = 0, col = 0, pos = 0;
    char *position;
    char var[1000];
    if (strcmp(cmd, "$") == 0)
    {
        cout << "$:Command not found" << endl;
        return;
    }
    while ((fgets(var, 1000, fp)) != NULL)
    {
        line += 1;
        position = strstr(var, cmd);
        if (position != NULL)
        {
            // col = (position - var);
            break;
        }
    }

    if (line == 7)
    {
        cout << cmd << ":Command not found" << endl;
        return;
    }
    int i = 0;

    while (var[i] != '=')
    {
        i++;
    }
    i++;

    while (var[i] != '\0')
    {
        cout << var[i];
        i++;
    }
    // //     int linelength = strlen(cmd);
    //     col = col + linelength;
    //     pos = ftell(fp);
    //     pos = pos+1+linelength;
    // cout<<pos<<endl;
    //     fseek(fp, pos + 1, SEEK_CUR);
    //     fgets(var, 1000, fp);
    //     puts(var);
    //     cout << line << endl;
    //     cout << col << endl;
    return;
}