#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include <grp.h>
#include "shell1.h"
#include "ls_exe.h"
int ls(char *s1, char *s2)
{
  int count1=0,count2=1,count3=-1;
  
    if(strlen(s1)==0 && strlen(s2)==0)
    
    {
        count2=count1;
        struct dirent *de;
        DIR *dr=opendir("./");
        if(dr==NULL)
        {
                    count2=count1;

            perror("Could not open the directory");
            return 0;
            count1++;
        }  
        while((de=readdir(dr))!=NULL)
        {   
             count1++;
            if ( !strncmp(de->d_name, ".",1) || !strcmp(de->d_name, "..") )
            {
                        count2=count1;

                continue;
            }
             count1++;
            printf("%s\n",de->d_name);
        }
        
        closedir(dr);
        
    
    }
    else if(strlen(s1)!=0 && strlen(s2)==0)
    {
        if(strcmp(s1,"-a")==0)
        {    count1++;
            struct dirent *de;
            DIR *dr=opendir(".");
                    count2=count1;

            if(dr==NULL)
            {
                perror("Could not open the directory");
                return 0;
            }  
            while((de=readdir(dr))!=NULL)
            {   
                
                    count2=count1;

                printf("%s\n",de->d_name);
            }
            closedir(dr);
        }
        else if(strcmp(s1,"-l")==0)
        {    count1++;
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            int i;
             count1++;                    
            count2=count1;

            struct dirent *myfile;
            struct stat fileStat;
             count1++;
            mydir=opendir(".");
            stat(".",&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                int check11=0;
                    if(!strncmp(myfile->d_name, ".",1) || !strcmp(myfile->d_name, ".."))    
                        continue;
                    stat(myfile->d_name,&fileStat);
                     count1++;  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    check11++;
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    check11++;
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    check11++;
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    printf("%ld ",fileStat.st_nlink);
                                         count1++;  


                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                                       count2=count1;

                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                                         count1++;  

                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                   count2=count1;
                    

                    for(i=4;i<=15;i++)
                       count1++;  
                    printf("%c",c[i]);
                    printf(" ");
                    count2=count1;
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;
        }   
        else if(strcmp(s1,"-al")==0)
        {  
             count2=count1;

            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            count2=count1;
            int i;
            struct dirent *myfile;
                               count2=count3;

            struct stat fileStat;
            mydir=opendir(".");
            stat(".",&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                                       count2=count1;

                    stat(myfile->d_name,&fileStat);  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                                       count2=count1;

                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                                       count2=count1;

                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    count1++;
                    printf("%ld ",fileStat.st_nlink);
                    count2=count1;
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                            count2=count1;

                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%4ld ",fileStat.st_size);
                            count2=count1;

                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                    printf("%c",c[i]);
                    printf(" ");
                                       count2=count1;

                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;           
        }
    }
    
    else if(strlen(s1)==0 && strlen(s2)!=0)
    {                     count1++;  
           count2=count1;

        struct dirent *de;
          if(s2[0]=='~')
        {                     count1++;  

                        char res[2000];
                        int i;
                                count2=count1;

                        strcpy(res,path_name);
                                          count1++;  


                        for( i=1;i<strlen(s2);i++)
                        {
                                                 count1++;  

                            strncat(res,&s2[i],1);
                            count2=count1;
                        }
                        strcpy(s2,res);
                                            count2=count1;

                        
        }
        DIR *dr=opendir(s2);
        if(dr==NULL)
        {                      count1++;  

            perror("Could not open the directory");
            return 0;
        }  
        while((de=readdir(dr))!=NULL)
        {                        count1++;  

          count2=count1;
              
            if ( !strncmp(de->d_name, ".",1) || !strcmp(de->d_name, "..") )
            {                      count1++;  

                continue;
            }
            
            printf("%s\n",de->d_name);
        }
                count2=count1;

        closedir(dr);
      
    }
    else if(strlen(s1)!=0 && strlen(s2)!=0)
    {                     count1++;  

        if(s2[0]=='~')
        {
                        char res[2000];
                        int i;
                        strcpy(res,path_name);
                                         count1++;  


                        for( i=1;i<strlen(s2);i++)
                        {
                            
                          count2=count1;
                            strncat(res,&s2[i],1);
                        }
                        strcpy(s2,res);
                        
        }
        if(strcmp(s1,"-a")==0)
        {
            struct dirent *de;
            DIR *dr=opendir(s2);
            if(dr==NULL)
            {                      count1++;  

                perror("Could not open the directory");
                return 0;
            }  
            while((de=readdir(dr))!=NULL)
            {   
             

                        count2=count1;

                printf("%s\n",de->d_name);
            }
            closedir(dr);  
        }
        else if(strcmp(s1,"-l")==0)
        {
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
                    count2=count1;

            int i;
            struct dirent *myfile;
            struct stat fileStat;
            mydir=opendir(s2);
                    count2=count1;

            stat(s2,&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            { int checks=0;
                    if(!strncmp(myfile->d_name, ".",1) || !strcmp(myfile->d_name, ".."))    
                        continue;
                    stat(myfile->d_name,&fileStat);
                    checks=checks+1;  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                                        checks=checks+1;  

                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                                        checks=checks+1;  

                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                                        checks=checks+1;  

                    printf("%ld ",fileStat.st_nlink);
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                                        checks=checks+1;  

                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                checks++;
                    printf("%c",c[i]);
                    printf(" ");
                    count2=count1;
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir); 
                                count2=count1;

 
            return 0;
        }
        else if(strcmp(s1,"-al")==0)
        {
            count2=count1;
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            count1++;
            int i;
            struct dirent *myfile;
            struct stat fileStat;
            mydir=opendir(s2);
            count1++;
            stat(s2,&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                   count2=count1;
                    stat(myfile->d_name,&fileStat);  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    count1++;
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                       count2=count1;

                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    count2=count1;

                    printf(" ");
                    printf("%ld ",fileStat.st_nlink);
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                                       count2=count1;

                    printf("%c",c[i]);
                    printf(" ");
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;           
        }
    }
   
    
    return 0;
}