#include <stdio.h>
 #include <fcntl.h>
#include <sys/types.h>        /* defines types used by sys/stat.h */
#include <sys/stat.h>        
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
void perCheckker(char str[],char c[]){
    write(1,c ,strlen(c));
    write(1," is created: ",strlen(" is created "));
    struct stat buf;
    if(stat(str,&buf)==-1){
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
char buff3,buff4;

fd1=open(argv[1],O_RDONLY);
fd2=open(argv[2],O_RDONLY);
long lenght1=lseek(fd1,-1,SEEK_END);
printf("lenght1= %ld\n",lenght1);
long lenght2=lseek(fd2,-1,SEEK_END);
if(lenght1!=lenght2){
     write(1," NO \n",strlen(" NO \n"));
    printf("2");
    exit(0);
}

else{
    //long long char_count=lseek(fd1,-1L,2);
    //write(1," WAIT..",8);
    write(1,"   ",3);
    lseek(fd2,0,SEEK_SET);
    while(lenght1+1!=0){
    read(fd1,&buff3,1);
    read(fd2,&buff4,1);
    
    
    if(buff3!=buff4){
    printf("3\n");
    // printf("char_count= %ld\n",lenght1);
    // printf("buff1 = %d\n",buff3);
    //  printf("buff2 = %d\n",buff4);
        close(fd1);
        close(fd2);
     write(1,"\b\b\b NO \n",strlen("\b\b\b\b NO \n"));

     exit(0); 
    }
    Zebra=(float)(lenght2-lenght1)*100/(float)lenght2;
    if(temp!=(int)Zebra){
    temp=(int)Zebra;
//gcvt(Zebra,3,str);

str[0]='\b';
str[1]='\b';
str[2]='\b';
str[5]='%';
str[4]=(char)((int)Zebra%10+48);
str[3]=(char)((int)Zebra/10+48);
//write(1,str,strlen(str));
//write(1,"\r",1);
  write(0,&str,6);}
    lseek(fd1,-2L,1);
    lenght1--;
}
write(1,"\b\b\b YES\n",strlen("\b\b\b YES\n"));
}
}
}
    

