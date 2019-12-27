#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include<string.h>
#include <fcntl.h>
#include<stdlib.h>

#include "pwd.h"

int parent ( )
{
    char path_name[20002];
    if(getcwd(path_name,sizeof(path_name))==NULL)
    {
        perror("getcwd() error");
        exit(1);

    }
    strcat(path_name,"\n");
   // printf("%s\n",path_name);
    write(1,path_name,strlen(path_name));
    return 0;
}