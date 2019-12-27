#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include "display1.h"
#include "arg.h"
#include "shell1.h"
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
int main();
int  loop();

int set=-1,z1=0;
char path_name[20002];
int piid;
int p_num[1022];
int msize=1022;
char * p_name[1022];

int main()
{
    for(int i=z1;i<msize;i++)
    {
        p_num[i]=set;
    }
     
    piid=getpid();
    char filename[1000]={0};
    sprintf(filename,"/proc/%d/exe",piid);
    char path[2003];
    if(readlink(filename,path,63)==set)
    {
        printf("Error:unable to find executable\n");
        return 0;
    }

    strncpy(path_name,path,strlen(path)-6);

    loop();
    return 0;
}
int  loop()
{
    
    char str[20002];

    do{
        int pid;int pid_status;
        while((pid=waitpid(set,&pid_status, WNOHANG | WUNTRACED))>0)
        {
            if(WIFEXITED(pid_status)){
                for(int i=z1;i<msize;i++)
                {
                    if(p_num[i]==pid)
                    {
                        
                        printf("%s with pid %d exited normally.\n",p_name[i],p_num[i]);
                        p_num[i+z1]=set;
                        break;
                    }
                }
            }
        }
        break;
    }while(1);

    dis(path_name);


    
    fgets(str,2000,stdin);
    
    input(str);

    loop();
    return 0;    
    
}