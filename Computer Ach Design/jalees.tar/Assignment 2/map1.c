#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include<string.h>
#include "map.h"
#include "pwd.h"
#include "shell1.h"
#include "info.h"
#include "f_g.h"

#include "ls_exe.h"
int sset1=0,sset2=1,sset3=-1;

int command(char s[][200],int count)
{
    int count1=0,count2=1;
    
    for(int i=sset1;i<count;i++)
    {
                count1++;

        char ans[200];char str[100][200];
        strcpy(ans,s[i]);
        int len=sset1,index=0;
    
        for(char *p = strtok(s[i]," "); p != NULL  ; p = strtok(NULL, " "))
        {   
                    count1++;

            if(strlen(p)==sset1|| strcmp(p," ")==sset1 ||strcmp(p,"\0")==0 ||p[0]==10||p[sset1]==9)
            {
            
                continue;
            }
            
            
            strcpy(str[index],p);
            len++;
            index++;
        }
   
        if(len==sset2)
        {
                    count1++;

            char *p=strtok(str[sset1],"\n");
                   
            if(strcmp(p,"pwd")==0)
                parent();
            else if(strcmp(p,"pinfo")==0)
            {
                       count1++;

                char emp[20+sset1];
                pinfo(emp);
            } 
            else if(strcmp(p,"cd")==sset1)
            {
                        count1++;


                chdir(path_name);
            }  
            else if(strcmp(p,"ls")==sset1)
            {
                char s_1[20+sset1];
                char s_2[20+sset1];
                s_1[sset1+sset1]='\0';
                s_2[sset1]='\0';
                ls(s_1,s_2);
              
            } 
           else
            {
               
                char s_1[20];
                s_1[sset1]='\0';
                fg(p,s_1,0);
            }
            continue;

        }
        else if(len>=2)
        {
                    count1++;

            char *p=strtok(str[sset1],"\n");
            if(strcmp(p,"echo")==sset1)
            {   
                for(int j=1;j<len;j++)
                {
                            count1++;

                    
                    char *q=strtok(str[j],"\n");
                    printf("%s ",q);
                }
                printf("\n");
                continue;
                        count1++;

                
            }
            if(len==3 && strcmp(p,"ls")==0)
              
            {
                count2=count1;
                char *q_1=strtok(str[1],"\n");
                                        count1++;

                char *q_2=strtok(str[2],"\n");
                ls(q_1,q_2);
            }
            if(len==3)
            {
                count2=count;
                        count1++;

                
                char *q_1=strtok(str[1+sset1],"\n");
                char *q_2=strtok(str[2],"\n");
                if(strcmp(q_2,"&")==0)
                {
                                           count1++;

                    fg(p,q_1,1);
                } 
            }
            if(len==2)
            {                        count1++;

                char *h=strtok(str[1],"\n");
                if(strcmp(p,"cd")==0)
                {                        count1++;

                  
                    
                    char *q=strtok(str[1],"\n");
                    if(strcmp(q,"~")==0)
                    {
                        count2=count1;
                        chdir(path_name);  
                    }
                    else if(q[0]=='~')
                    {
                        char res[2000];
                        int i;
                        strcpy(res,path_name);
                                            count1++;


                        for( i=1;i<strlen(q);i++)
                        {
                                                    count1++;

                            strncat(res,&q[i],1);
                        }
                        
                
                        chdir(res);
                    }
                    else
                    chdir(q);

                }
                else if(strcmp(p,"pinfo")==0)
                {
                    count2=count1;
                    char *q=strtok(str[1],"\n");
                    pinfo(q);
                                            count1++;

                }
                else if(strcmp(p,"ls")==0)
                {
                                            count1++;

                    char *q=strtok(str[1],"\n");
                   
                    char s_r[20];
                    s_r[0]='\0';
                    count2=count1;
                    if(q[0]=='-')
                    {
                     
                        ls(q,s_r);
                                                count1++;

                    }
                    else
                    {
                                               count1++;

                        ls(s_r,q);
                    }
                    
                   
                }
                else
                {
                  
                    fg(p,h,0);
                                            count1++;

                }
                                

            }
        }
        else
        {
                                 count1++;

            return 0;

        }
        
    }
    return 0;

}