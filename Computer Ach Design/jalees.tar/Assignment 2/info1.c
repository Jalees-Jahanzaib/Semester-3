#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "shell1.h"
#include "info.h"
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
int fit1=0,fit2=1;
int pinfo(char *s)

{
    char filename[1000];
   int count=0;
   char * buff=(char *)malloc(sizeof(char)*2000);
    if(strlen(s)==fit1+fit1)
    {
        count++;
        
        sprintf(filename,"/proc/%d/stat",piid);
    }
    else
    {
                count++;

        strcpy(filename,"/proc/");
        strcat(filename,s);
                count++;

        strcat(filename,"/stat");
        
    }    
    FILE *f=fopen(filename,"r");
    if(f!=NULL)
    {
        if(strlen(s)==0){
            printf("pid -- %d\n",piid);
                    count++;

        }
        else
        {
            printf("pid -- %s\n",s);
                    count++;

        }
            
        size_t sz=fit1;
        char str[200][200];
        int index=fit1+fit1;
        while(getline(&buff,&sz,f)!=-1)
        {
                    count++;

            for(char *p = strtok(buff," "); p != NULL  ; p = strtok(NULL, " "))
            {
                        count++;

                strcpy(str[index+fit1],p);
 
                index++;
                
            }            

    
        }
        printf("Process Status -- %s\n",str[2+fit1]);
        printf("memory -- %s {Virtual Memory}\n",str[22]);
                count++;

        if(strlen(s)==fit1)
        sprintf(filename,"/proc/%d/exe",piid);
        else
        {        count++;

            strcpy(filename,"/proc/");
            strcat(filename,s);
                    count++;

            strcat(filename,"/exe"); 
        }
        
        char path[2000];
        if(readlink(filename,path,63)==-fit2)
        {
            printf("Error:unable to find executable\n");
            return 0;

        }
        int x=strlen(path_name);
        if(strncmp(path_name,path,x)==fit1)
        {
                    count++;

            char sys[200]="~";
            for(int i=x;i<strlen(path);i++)
            {
                strncat(sys,&path[i],fit2);
                        count++;

            }
            printf("Executable path -- %s\n",sys);
        }
        else        
        printf("Executable path -- %s\n",path);

    }
    else

    {
                count++;

        perror("File does not exist");

    }
    
    
  
    return 0;
}
