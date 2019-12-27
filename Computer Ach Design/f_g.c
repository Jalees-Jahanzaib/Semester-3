#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include "f_g.h"
#include "shell.h"

int fg(char *s,char *q,int t)
{

    pid_t pid;
    pid=fork();
    
    
    if(pid == 0)
    {
         
        
     
        int x;
        if(strlen(q)==0)
        {
            
            x=execlp(s,s,NULL);
        }
        else
        {
            
            char *args[3];
            args[0]=s;
            args[1]=q;
            
            args[2]=NULL;
            
            x=execvp(args[0],args);
        }
        
        if(x==-1)
        {
            printf("exec :No such command \n");
        }
    }
     else if(pid>0)
    {
        if(strcmp(q,"&")==0 || t==1)
        {
        
            int i;
            for( i=0;i<msize;i++)
            {
                if(p_num[i]==-1)
                {
                    p_num[i]=pid;
                    p_name[i]=s;
                    break;
                }
            }
            if(i==msize)
            {
                perror("Too many Background Process");
                return 0;
            }
        }
        else
        {
      
            if(wait(0)==-1)
            {
                perror("wait");
            }

        }
        
        
    }
    return 0;
}