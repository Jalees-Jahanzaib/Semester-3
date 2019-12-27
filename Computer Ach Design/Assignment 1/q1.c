#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
extern int errno;
struct stat sb;
char ar2[5];
int inttostr(int n){
	// for(int j=0;j<5;j++)
		// ar2[j]=
	int i=0;
	int x=n;
	while(n){
		i++;
		n/=10;
		// ar2[]
	}
	ar2[i]='%';
	int ans=i+1;
	i--;
	while(x){
		int y=x%10;
		ar2[i--]=(y+'0');
		x/=10;
	}
	return ans;
}
int main(int argc,char **argv){
	if(stat("./Assignment",&sb)==-1){
		mkdir("./Assignment",0700);
	}
	// else{
	// 	write(1,"Directory named Assignment already created\n",44);
	// 	// printf("afjk");
	// }
	int fd=open(argv[1],O_RDONLY);
	char arr[100];
	arr[0]='.',arr[5+2]=arr[8+2]='n',arr[6+2]='m',arr[7+2]='e';
	arr[1+2]=arr[2+2]='s',arr[3+2]='i',arr[4+2]='g',arr[9+2]='t';
	arr[10+2]=arr[1]='/';
	arr[2]='A';
	// printf("%s\n",argv[1]);
	int j=13;
	for(int i=0;argv[1][i]!='\0';i++){
		if(argv[1][i]=='/'){
			j=13;
		}
		else{
			arr[j++]=argv[1][i];
		}
	}
	arr[j]='\0';
	// printf("%s\n",arr);
	int fd1=open(arr,O_WRONLY|O_CREAT,0600);
	int fsize=lseek(fd,0,SEEK_END);
	// printf("filesize of your file is %d\n",fsize);
	int max1=25;
	int fix=fsize;
	int sz1=0.;
	while(fsize){
		if(fsize<max1)
			max1=fsize;
		char ar1[max1+1];
		fsize-=max1;
		lseek(fd,fsize,SEEK_SET);
		int x=read(fd,ar1,max1);
		lseek(fd,-1,SEEK_CUR);
		// printf("%d ",x);
		ar1[max1]='\0';
		// printf("%s\n",ar1);
		for(int i=0;i<max1/2;i++){
			char x=ar1[i];
			ar1[i]=ar1[max1-1-i];
			ar1[max1-1-i]=x;
		}
		// printf("%s\n",ar1);
		write(fd1,ar1,max1);
		sz1+=max1;
		int sz=sz1*100;
		int pr=sz/fix;
		int len=inttostr(pr);
		write(1,ar2,len);
		if(pr!=100)
			write(1,"\r",1);
	}
	write(1,"\n",1);
	close(fd);
	close(fd1);
}