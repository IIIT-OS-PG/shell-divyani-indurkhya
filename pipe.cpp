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
void pipe_cmd(char **arguments, int num_pipe)
{
    int len = 0,pipe_vol[num_pipe][2];
    int i = 0;
    int j = 0, k = 0;
    char *pipeline[num_pipe+2][num_pipe+2];
    while (arguments[i] != NULL)
    {
        len++;
        if (strcmp(arguments[i], "|") == 0)
        {
            pipeline[j][k] = NULL;
            j++;
            k = 0;
           
        }
        else
        {
            pipeline[j][k] = arguments[i];
            //cout << pipeline[j][k];
            k++;
        }

        i++;
    }
    pipeline[j][k] = NULL;
    for(i=0; i<num_pipe;i++)
    {
        pipe(pipe_vol[i]);
    }
   
    for(i=0;i<=num_pipe;i++)
    {
        if(i == 0)
        {
            int pid;
            if ((pid = fork())==0)
            {
                dup2(pipe_vol[0][write_stdout],write_stdout);
                close(pipe_vol[0][write_stdout]);
                close(pipe_vol[0][read_stdin]);
                if(execvp(pipeline[i][0],pipeline[i]) < 0)
                {
                    cout<<"Error"<<endl;
                   exit(1);
                }
                
            }
            else
            {
                int stat;
            waitpid(pid, &stat, 0);
            close(pipe_vol[0][write_stdout]);
            }
            
        }
        else if(i!=0 && i!=num_pipe)
        {
            int pid;
            if ((pid = fork())==0)
            {
                dup2(pipe_vol[i][write_stdout],write_stdout);
                dup2(pipe_vol[i-1][read_stdin],read_stdin);
                close(pipe_vol[i][write_stdout]);
                close(pipe_vol[i-1][read_stdin]);
                if(execvp(pipeline[i][0],pipeline[i]) < 0)
                {
                    cout<<"Error"<<endl;
                    exit(1);
                }
            }
            else
            {
                int stat;
            waitpid(pid, &stat, 0);
            close(pipe_vol[i][write_stdout]);
            }
            
        }
       
        
        else
        {
            int pid;
            if ((pid = fork())==0)
            {
                dup2(pipe_vol[i-1][read_stdin],read_stdin);
                close(pipe_vol[i-1][read_stdin]);
                close(pipe_vol[i-1][write_stdout]);
                if(execvp(pipeline[i][0],pipeline[i]) < 0)
                {
                    cout<<"Error"<<endl;
                    exit(1);
                }
                exit(1);
            }
          else
            {
                int stat;
            waitpid(pid, &stat, 0);
            close(pipe_vol[i-1][write_stdout]);
            }
        }
        

    }




    return;
}