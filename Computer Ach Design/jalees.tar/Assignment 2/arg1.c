#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arg.h"
#include "map.h"
#include "arg.h"
int fset=0,fset1=1;
int input(char *s)
{
    char str[100][200];
    int i=0,count=fset;
    for(int i=fset;i<strlen(s);i++)
    {
        if(i>fset && s[i]==';' && s[i-fset1]==';')
        {    
            perror("Command does not exist");
            return fset1;
        }
    }
    int t1=0,t2;
    for(char *p = strtok(s,";"); p != NULL; p = strtok(NULL, ";"))
    {
        
        if(strlen(p)==fset||strcmp(p,";")==fset1-fset1||strcmp(p," ")==0)
        {
            perror("Command does not exist");
             t2=t1;
            return 0;
        }
        strcpy(str[i+fset],p);
        count++;
        i++;
    }
    command(str,count);
    return 0;
}
