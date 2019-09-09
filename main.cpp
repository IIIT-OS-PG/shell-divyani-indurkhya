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
#include <unordered_map>
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
    int k = 1;
    while (arguments[k] != NULL)
    {
        i = 0;
        cout << "imhere" << endl;
        if (arguments[k][i] != '\"')
        {
            if (arguments[k][i] == ' ')
            {
                s2 = s2 + " ";
                k++;
            }
            else
            {
                s3 = arguments[k][i];
                s2 = s2 + s3;
            }
        }
        i++;
    }
    cout << s2 << endl;

    return;
}

void execute_cmd(char **arguments)
{
    int i = 0, pipe = 0;
    //char *answer=(char*)malloc(sizeof(char)*10);
    while (arguments[i] != NULL)
    {
        if (strcmp(arguments[i], "|") == 0)
            pipe++;
        i++;
    }
    if (pipe > 0)
    {
        cout << pipe << endl;
        //pipeline(arguments);
    }

    else if (strcmp(arguments[0], "alias") == 0)
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
        getcwd(str,100);
        int k=0;
         while(str[k]!='D')
         k++;

        cout << getenv("USER") << ":";
        while(str[k]!='\0')
        {
            printf("\033[1;32m");
  printf("%c",str[k]);
  
            
            k++;
         }
         printf("\033[0m");
          cout<< "$ ";
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
