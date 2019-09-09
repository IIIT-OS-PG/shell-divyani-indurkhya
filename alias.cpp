#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <fcntl.h>
#include <assert.h>

using namespace std;
void alias_cmd(char **cmd)
{
    int i;
    
    unordered_map<string, string> map;
    string s1 = "", s2 = "", s3;
    if (strcmp(cmd[0], "alias") == 0)
    {
        for (i = 0; cmd[1][i] != '='; i++)
        {
            s3 = cmd[1][i];
            s1 = s1 + s3;
        }
        i += 2;
        int k = 1;
        while (cmd[k][i] != '\'')
        {
            if(cmd[k][i]=='\0')
            {
                s2=s2+" ";
                k++;
                i=0;
                continue;

            }
            s3 = cmd[k][i];
            s2 = s2 + s3;
            i++;
        }
        cout << s2 << s3;
    }
}
// int main()
// {
// char **arg=(char **)malloc(sizeof(char *) * 10);
// arg[0] = (char *)malloc(sizeof(char) * 100);
// arg[1] = (char *)malloc(sizeof(char) * 100);

// arg[0]='alias';
// arg[1]='\"cm=cat main.cpp\"';
// alias_cmd(arg);
// return 0;
// }