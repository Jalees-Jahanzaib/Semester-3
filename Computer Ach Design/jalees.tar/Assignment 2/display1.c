#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include<string.h>

#include "display1.h"
int x=-1,y=1,z=0;
int dis(char * original_path)
{
    char s[20001];char host_name[20001];
    s[0]='~';
    
    int hostname;
    hostname=getlogin_r(host_name,sizeof(host_name));
    if(hostname==x)
    {
    
        perror("gethostname");
        exit(y);
    }
   
    struct utsname sys_data;
    int ret=uname(&sys_data);
    if(ret==x)
    {
        perror("uname");
        exit(y);
    }
  
    char path_n[20001];
    if(getcwd(path_n,sizeof(path_n))==NULL)
    {
        perror("getcwd() error");
        exit(y);

    }
    int x=strlen(original_path);
    if(strcmp(path_n,original_path)==z )
    {
        
        s[0]='~';
        s[y]='\0';
        printf("\e[1m\e[31m<%s@%s\e[0m:\e[1m\e[36m%s>\e[0m",host_name,sys_data.sysname,s);
    }
    else
    {
        if(strncmp(path_n,original_path,x)==z && path_n[x]=='/')
        {
            for( ;x<strlen(path_n);x++)
            {

                strncat(s,&path_n[x],y);
            }    
            printf("\e[1m\e[31m<%s@%s\e[0m:\e[1m\e[36m%s>\e[0m",host_name,sys_data.sysname,s); 
            
        }
        else
        printf("\e[1m\e[31m<%s@%s\e[0m:\e[1m\e[36m%s>\e[0m",host_name,sys_data.sysname,path_n);
    }
    
    return 0;
    

}