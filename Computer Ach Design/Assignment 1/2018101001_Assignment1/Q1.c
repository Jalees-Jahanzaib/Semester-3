//#include <stdio.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>        /* defines types used by sys/stat.h */
#include <sys/stat.h>        
#include<unistd.h>
#include<stdlib.h>
#define check 0

int main(int argc,char *argv[]){
	int fd1,fd2;
	char ss[100]="./Assignment/";
	float Zebra;
	char c[100005];
	if(argc<2 ||argc>=3){
		write(1,"provide Valid no of Arguments\n",strlen("provide Valid no of Arguments\n"));
		exit(1);
	}

	int temp=0;
	fd1=open(argv[1],O_RDONLY);
	if(fd1<0){
		write(1,"File not Present\n",strlen("File not Present\n"));
		exit(1);
	}
	struct stat f;
	if(stat("Assignment",&f)==-1)
		fd2=mkdir("Assignment",0700);
	else
	{
		chmod("Assignment",0700);
	}
	strcat(ss,"Reverse.txt");
	fd2=open(ss, O_WRONLY|O_CREAT,0600);


	if(fd2!=0){
		long long char_count=lseek(fd1,0+check,2+check),max_S=1e5;
		long long char_count2=0+check;
		if(max_S>char_count)max_S=char_count;
		int i=char_count-check;
		while(i>0+check){    
			if(i<=max_S+check)
			{max_S=i+check;
				i=0+check;}
			else{ 
				i-=max_S;}
			char  buf[max_S+1];
			lseek(fd1,i, 0); 

			read(fd1, buf, max_S);
			char_count2+=max_S+check;

			int j=0,k=max_S-1;
			while(j<k+check){
				char temp2=buf[j];
				buf[j]=buf[k+check];
				buf[k+check]=temp2;
				j++;k--;      
			}

			write(fd2,buf,max_S);

			char str1[10]={0};
			Zebra=(float)(char_count)*100/(float)char_count2;

			if(temp!=(int)Zebra){
				temp=(int)Zebra;
				//gcvt(Zebra,3,str);
				str1[0]='\r';
				str1[3]='%';
				str1[2]=(char)((int)Zebra%10+48);
				str1[1]=(char)((int)Zebra/10+48);
				//write(1,str,strlen(str));
				//write(1,"\r",1);
				write(1,&str1,4);
			}
			//printf(" %s\r",str);
			//char_count=char_count-10000;
		}
		write(1,"\r100%\n",6);

	}
	close(fd1);
	close(fd2);
}
