#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <fcntl.h>
#include <assert.h>
#include <fstream>
//#include "/home/divyani/Desktop/sampleshell/finalshell/final/grep.cpp"
//#include "/home/divgyani/Desktop/sampleshell/finalshell/final/alias.cpp"
#include "/home/divyani/Desktop/sampleshell/finalshell/final/history.cpp"
#include "/home/divyani/Desktop/sampleshell/finalshell/final/bashrc.cpp"
#include "/home/divyani/Desktop/sampleshell/finalshell/final/enviornvar.cpp"
#include "/home/divyani/Desktop/sampleshell/finalshell/final/pipe.cpp"
#include "/home/divyani/Desktop/sampleshell/finalshell/final/ioredirection.cpp"
#include <unordered_map>
#include <iostream>
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
void alias_cmd(char **arguments)
{
    int i;

    string s1 = "", s2 = "", s3;

    for (i = 0; arguments[1][i] != '='; i++)
    {
        s3 = arguments[1][i];
        s1 = s1 + s3;
    }
    i++;
    int k = 1, j = 0;
    while (arguments[1][i] != '\0')
    {

        cout << "imhere" << endl;
        // if (arguments[1][i] != '\"')
        // {
        //     if (arguments[1][i] == ' ')
        //     {
        //         s2 = s2 + " ";
        //         k++;
        //     }
        //     else
        //     {
        s3 = arguments[1][i];
        s2 = s2 + s3;
        // }}
        i++;
    }
    // while (strcmp(arguments[j], NULL) != 0)
    //     j++;
    int len = (sizeof(arguments) / sizeof(char **));
    cout << len << endl;
    cout << s2 << endl;

    return;
}

void execute_cmd(char **arguments)
{
    int i = 0, pipe = 0, out_single = 0, out_double = 0;
    //char *answer=(char*)malloc(sizeof(char)*10);

    while (arguments[i] != NULL)
    {
        if (strcmp(arguments[i], "|") == 0)
            pipe++;
        else if (strcmp(arguments[i], ">") == 0)
        {

            out_single++;
        }
        else if (strcmp(arguments[i], ">>") == 0)
        {
            out_double++;
        }
        i++;
    }
    //  cout<<out_single<<endl;
    // cout<<out_double<<endl;

    if (pipe > 0)
    {
        //cout << pipe << endl;
        pipe_cmd(arguments, pipe);
    }
    else if (out_double > 0 || out_single > 0)
    {
        output_redirect(arguments, out_single, out_double);
    }
    if (strcmp(arguments[0], "alias") == 0)
    {
        cout << "here" << endl;

        alias_cmd(arguments);
    }
    else if (strcmp(arguments[0], "history") == 0)
    {
        history_cmd();
    }
    else if (arguments[0][0] == '$')
    {
        env_var(arguments[0]);
    }
    else if (strcmp(arguments[0], "cd") == 0)
    {

        chdir(arguments[1]);
        return;
    }
    else if (strcmp(arguments[0], "echo") == 0 && (arguments[1][0] == '$'))
    {
        env_var(arguments[1]);
    }
    else
        execvp(arguments[0], arguments);
    return;
}

int main()
{
    bashinitial();
    char buffer[1000];
    char **arguments;
    char **cmd = (char **)malloc(sizeof(char *) * 10);

    int j = 0;
    int hist_count = 1;
    //char prompt_ret[8]="$PROMPT",*prompt=(char*)malloc(sizeof(char)*10);
    //     ofstream myfile;
    // myfile.open ("history.txt", ios::out | ios::app | ios::binary);
    while (1)
    {
        char str[100];
        getcwd(str, 100);
        int k = 0;
        while (str[k] != 'D')
            k++;
        printf("\033[1;36m");
        cout << getenv("USER") << ":";
        printf("\033[0m");
        while (str[k] != '\0')
        {
            printf("\033[1;32m");
            printf("%c", str[k]);

            k++;
        }
        printf("\033[0m");
        cout << "$ ";
        FILE *f;
        f = fopen("history.txt", "a");
        string s = "";
        fgets(buffer, 1000, stdin);
        // while (buffer[j] != '\0')
        // {
        //     s = s + buffer[j];
        //     j++;FILE *f;
        f = fopen("history.txt", "a");
        // }
        fputs(buffer, f);
        fclose(f);
        //         if (myfile.is_open())
        //   {
        //     myfile<<hist_count;
        //     myfile<<" ";
        //     myfile << s;
        //     myfile<<"\n";
        //     hist_count++;
        //   }

        // fprintf(fp,buffer);
        int pipe = 0;
        arguments = tokenization(buffer);
        int i;
        // int len = (sizeof(arguments) / sizeof(char **));
        // cout << len << endl;
        // for (i = 0; i < len; i++)
        if (strcmp(arguments[0], "exit") == 0)
        {
            return 0;
        }

        int temp;
        pid_t pID;
        pID = fork();
        if (pID == 0)
        {
            // if (strcmp(arguments[0], "alias") == 0)
            // {
            //     char **alias_arr = (char **)malloc(sizeof(char *) * 10);
            //     char *token = strtok(buffer, " \n");
            //     cout<<token<<endl;

            //     char *token1 = strtok(buffer, "=\n");
            //     cout<<token1<<endl;
            //     int i = 0;
            //     while (token != NULL)
            //     {
            //         alias_arr[i] = (char *)malloc(sizeof(char) * 100);
            //         alias_arr[i] = token1;
            //         token1 = strtok(NULL, " \n");
            //         i++;
            //     }
                
            // }
            execute_cmd(arguments);
        }
        else if (pID > 0)
        {
            
            int stat;
            waitpid(pID, &stat, 0);
        }
        else
            printf("Failed to create proccess \n");
    }

    return 0;
}
