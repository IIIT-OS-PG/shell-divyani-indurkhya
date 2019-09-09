#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <fcntl.h>
#include <assert.h>
#include <fstream>
#include <unordered_map>
#include <iostream>
#define read_stdin 0
#define write_stdout 1
using namespace std;
void output_redirect(char **arguments, int outs, int outd)
{
    int i = 0, len = 0;
    string s = "";

    i = 0;
    if (outs > 0)
    {
        //cout << arguments[len - 1] << endl;
        // while (arguments[len - 1][i] != '\0')
        // {
        //     s=s+arguments[len - 1][i];

        // }
        while (arguments[i] != NULL)
        {
            len++;
            if (strcmp(arguments[i], ">") == 0)
            {
                arguments[i] = NULL;
            }
            i++;
        }
        int fd = open(arguments[len - 1], O_WRONLY | O_CREAT, 0700);

        dup2(fd, write_stdout);
        if (execvp(arguments[0], arguments) < 0)
        {
            cout << "Error" << endl;
            exit(1);
        }

        close(fd);
    }
    if (outd > 0)
    {
        i = 0;
        while (arguments[i] != NULL)
        {
            len++;
            if (strcmp(arguments[i], ">>") == 0)
            {
                arguments[i] = NULL;
            }
            i++;
        }

        //  cout << arguments[len - 1] << endl;
        int fd = open(arguments[len - 1], O_WRONLY | O_CREAT | O_APPEND, 0700);

        dup2(fd, write_stdout);
        if (execvp(arguments[0], arguments) < 0)
        {
            cout << "Error" << endl;
            exit(1);
        }

        close(fd);
    }
    return;
}