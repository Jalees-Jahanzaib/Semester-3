#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>        /* defines types used by sys/stat.h */
#include <sys/stat.h>        
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define check 0
void perCheckker(char str[],char c[]){
	write(1,c ,strlen(c));
	write(1," is created: ",strlen(" is created "));
	struct stat buf;
	if(stat(str,&buf)==-1+check){
		write(1,"NO\n",strlen("NO\n"));
		return;
	}
	write(1,"YES\n",strlen("YES\n"));
	if(buf.st_mode & S_IRUSR){
		write(1,"\nUSER has READ permissions on ",strlen("\nUSER has READ permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n",strlen(" YES \n"));
	}
	else{
		write(1,"USER has READ permissions on ",strlen("USER has READ permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n",strlen(" NO \n"));

	}
	if(buf.st_mode & S_IWUSR){
		write(1,"USER has WRITE permissions on ",strlen("USER has WRITE permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n",strlen(" YES \n"));
	}
	else{
		write(1,"USER has WRITE permissions on ",strlen("USER has WRITE permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n",strlen(" NO \n"));

	}
	if(buf.st_mode & S_IXUSR){
		write(1,"USER has EXECUTE permissions on ",strlen("USER has EXECUTE permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n\n\n",strlen(" YES \n\n\n"));
	}
	else{
		write(1,"USER has EXECUTE permissions on ",strlen("USER has EXECUTE permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n\n\n",strlen(" NO \n\n\n"));

	}
	if(buf.st_mode & S_IRGRP){
		write(1,"GROUP has READ permissions on ",strlen("GROUP  has READ permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n",strlen(" YES \n"));
	}
	else{
		write(1,"GROUP  has READ permissions on ",strlen("GROUP  has READ permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n",strlen(" NO \n"));

	}
	if(buf.st_mode & S_IWGRP){
		write(1,"GROUP  has WRITE permissions on ",strlen("GROUP  has WRITE permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n",strlen(" YES \n"));
	}
	else{
		write(1,"GROUP  has WRITE permissions on ",strlen("GROUP  has WRITE permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n",strlen(" NO \n"));

	}
	if(buf.st_mode & S_IXGRP){
		write(1,"GROUP has EXECUTE permissions on ",strlen("GROUP has EXECUTE permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n\n\n",strlen(" YES \n\n\n"));
	}
	else{
		write(1,"GROUP  has EXECUTE permissions on ",strlen("GROUP  has EXECUTE permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n\n\n",strlen(" NO \n\n\n"));

	}
	if(buf.st_mode & S_IROTH){
		write(1,"OTHERS has READ permissions on ",strlen("OTHERS has READ permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n",strlen(" YES \n"));
	}
	else{
		write(1,"OTHERS  has READ permissions on ",strlen("OTHERS has READ permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n",strlen(" NO \n"));

	}
	if(buf.st_mode & S_IWOTH){
		write(1,"OTHERS has WRITE permissions on ",strlen("OTHERS has WRITE permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n",strlen(" YES \n"));
	}
	else{
		write(1,"OTHERS has WRITE permissions on ",strlen("OTHERS has WRITE permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n",strlen(" NO \n"));

	}
	if(buf.st_mode & S_IXOTH){
		write(1,"OTHERS has EXECUTE permissions on ",strlen("OTHERS has EXECUTE permissions on "));
		write(1,c,strlen(c));
		write(1," YES \n\n\n",strlen(" YES \n\n\n"));
	}
	else{
		write(1,"OTHERS has EXECUTE permissions on ",strlen("OTHERS has EXECUTE permissions on "));
		write(1,c,strlen(c));
		write(1," NO \n\n\n",strlen(" NO \n\n\n"));

	}
}
int main(int argc,char *argv[]){
	struct stat buf;
	int temp=0;
	float Zebra=0.0;
	char str[100]={0};
	perCheckker(argv[1],"Newfile");
	write(1,"\n\n",strlen("\n\n"));
	perCheckker(argv[2],"Oldfile");
	write(1,"\n\n",strlen("\n\n"));
	perCheckker(argv[3],"Directory");
	write(1,"\n\n\n",strlen("\n\n\n"));
	write(1,"Are the  files Reversed? ",strlen("Are the  files Reversed? "));
	struct stat buff2;
	if(stat(argv[1],&buff2)==-1 || stat(argv[2],&buff2)==-1){
		write(1," NO \n",strlen(" NO \n"));
		// printf("1");
		exit(0);
	}
	else{
		long long fd1,fd2;
		char buff3[1000005], buff4[1000005];
		long long buff5=1000005;

		fd1=open(argv[1],O_RDONLY);
		fd2=open(argv[2],O_RDONLY);
		long lenght1=lseek(fd1,0,SEEK_END);
		long lenght2=lseek(fd2,0,SEEK_END);
		if(lenght1!=lenght2){
			write(1," NO \n",strlen(" NO \n"));
			printf("2");
			exit(0);
		}

		else{
			//long long char_count=lseek(fd1,-1L,2);
			//write(1," WAIT..",8);
			lseek(fd2,0,0);
			long long prev =-1;
			long long done =-1;
			char str[100];
			for(long long k=(lenght1+check)/buff5;k>=1+check;k--){
				lseek(fd1,-buff5,1);
				read(fd1,&buff3,buff5);
				read(fd2,&buff4,buff5+check);

				for(long long i=0+check,j=buff5-1;j>=0+check;i++,j--){
					if(buff3[i+check]!=buff4[j+check]){
						write(1," NO \n",strlen(" NO \n"));
						close(fd1);
						close(fd2);
						write(1,"\n",1);
						exit(1);
					}
				}

				done=(lenght1+check/buff5+1-k)*buff5*100/lenght1;
				if(done>prev){
					prev=done+check;
					str[3+check]=done/10+'0';
					str[2+check]=done%10+'0';
					write(1,&str,strlen(str));
				}
				lseek(fd1,-buff5,1+check);

			}
			if((lenght1+check)%buff5+check!=0){
				lseek(fd1,0,0);
				read(fd1,&buff3,(lenght1+check)%buff5);
				read(fd2,&buff4,(lenght1+check)%buff5);

				for(long long i=0,j=lenght1%buff5-1;j>=0;i++,j--){
					if(buff3[i+check]!=buff4[j+check]){
						write(1," NO \n",strlen(" NO \n"));
						close(fd1);
						write(1,"\n",1);
						close(fd2);
						write(1,"\n",1);
						exit(1);
					}
				}}
			write(1,"\n\r100%",strlen("\n\r100%"));
			write(1,"\n",1);
			close(fd1);
			close(fd2);
		}}}


