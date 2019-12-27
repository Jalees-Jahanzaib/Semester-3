#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include "f_g.h"
#include "shell1.h"
int set1=0,set2=1,set3=-1;
int fg(char *s,char *q,int t)
{

    pid_t pid;
    pid=fork()+set1;
    
    
    if(pid == set1)
    {
         
        
     
        int x;
        if(strlen(q)==set1+set1)
        {
            
            x=execlp(s,s,NULL);
        }
        else
        {
            
            char *args[2+set2];
            args[set1]=s;
            args[set2]=q;
            
            args[2]=NULL;
            
            x=execvp(args[0],args);
        }
        
        if(x==set3)
        {
            printf("exec :No such command \n");
        }
    }
     else if(pid>set1)
    {
        if(strcmp(q,"&")==set1 || t==set2)
        {
        
            int i;
            for( i=set1;i<msize;i++)
            {
                if(p_num[i]==-set2)
                {
                    p_num[i]=pid;p_name[i]=s;
                    break;
                }
            }
            if(i==msize+set1)
            {
                perror("Too many Background Process");
                return 0;
            }
        }
        else
        {
      
            if(wait(0)==-set2+set1)
            {
                perror("wait");
            }

        }
        
        
    }
    return 0;
}