#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <fcntl.h>
#include <assert.h>
#include "/home/divyani/Desktop/sample shell/finalshell/grep.cpp"
using namespace std;

char **tokenization(char *cmd)
{
    char **arg = (char **)malloc(sizeof(char *) * 10);
    char *token = strtok(cmd, " \n");
    int i = 0;
    while (token != NULL)
    {
        arg[i] = (char *)malloc(sizeof(char) * 100);
        arg[i] = token;
        token = strtok(NULL, " \n");
        i++;
    }
    arg[i] = NULL;
    return arg;
}
void execute_cmd(char ** arguments)
{
 /* int i=0,pipe=0;
        while(arguments[i]!=NULL)
        {
            if(strcmp(arguments[i],"|")==0)
            pipe++;
            i++;
        }
       if (pipe>0)
       {
           cout<<pipe<<endl;
            pipe_handle(arguments);
       }*/
if (execvp(arguments[0], arguments) == 0)
            {
                cout << "error execvp" << endl;
            }
}

int main()
{
    char buffer[1000];
    char **arguments;
    char **cmd = (char **)malloc(sizeof(char *) * 10);
    while (1)
    {
        fgets(buffer, 1000, stdin);
        int pipe = 0;
        arguments = tokenization(buffer);
        int i;
        // int len = (sizeof(arguments) / sizeof(char **));
        // cout << len << endl;
        // for (i = 0; i < len; i++)
        int temp;
        pid_t pID;
        pID = fork();
        if (pID == 0)
        {
           execute_cmd(arguments);
        }
        else if (pID > 0)
        {
           // printf("%d\n", pID);
            int stat;
            waitpid(pID, &stat, 0);
        }
        else
            printf("Failed to create proccess \n");
    }
    
    return 0;
}
