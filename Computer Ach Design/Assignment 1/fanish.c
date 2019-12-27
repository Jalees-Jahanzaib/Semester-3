
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
clock_t t; 
    t = clock(); 
    int source, dest, n, max=10000000;
    int filesize;
    int i;
    int percentreversed=0;
    int bytesread=0;
    //if (mkdir("Assignment", 0777) == -1) printf("error\n");

    if (argc != 3) {
        //if you wanna print what is the error
        //fprintf(stderr, "usage %s <source> <dest>", argv[0]);
        exit(-1);
    }

    if ((source = open(argv[1], 0400)) < 0) { //read permission for user on source
        //if you wanna print what is the error
        //fprintf(stderr, "can't open source");
        exit(-1);
    }

//    if ((dest = open(argv[2],O_CREAT|O_APPEND|O_RDWR, 0700)) < 0) { //rwx permission for user on dest
    if ((dest = creat(argv[2], 0700)) < 0) { //rwx permission for user on dest
        //if you wanna print what is the error
        //fprintf(stderr, "can't create dest");
        exit(-1);
    }

    filesize = lseek(source, (off_t) 0, SEEK_END); //filesize is lastby +offset
    printf("fz %d\n",filesize);    
    if(max>filesize)max=filesize;
    i=filesize;
    while(i>0){    
    printf("%d\n",i);
        if(i<=max){max=i;i=0;}else i-=max;
    char*  buf=(char*)malloc(sizeof(char) * (max+1));
        lseek(source, (off_t) i, SEEK_SET); 

        n = read(source, buf, max);
        bytesread+=max;
       // printf("%s",buf);
        /*if (n != 1) {
            //if you wanna print what is the error
            //fprintf(stderr, "can't read 1 byte");
            exit(-1);
        }*/
            int j=0,k=max-1;
            while(j<k){
                char temp=buf[j];
                buf[j]=buf[k];
                buf[k]=temp;
                j++;k--;      
            }
//printf("fuck off\n");
        n=write(dest,buf,max);
        /*if (n != 1) {
            //if you wanna print what is the error
            //fprintf(stderr, "can't write 1 byte");
            exit(-1);
        }*/

        //temp displays current percentage of file reversed
        percentreversed=(bytesread*100)/filesize;
        char temp[6];
        temp[0]=(percentreversed/100)%10+'0';
        temp[1]=(percentreversed/10)%10+'0';
        temp[2]=percentreversed%10+'0';
        temp[3]=' ';
        temp[4]='%';
        temp[5]='\r';
        write(1," ",1);
        if(temp[0]=='0') write(1,temp+1,5);
        else write(1,temp,6);
        free(buf);
    }
    write(STDOUT_FILENO, " DONE :)\n", 9);
        t = clock() - t; 
            double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
                printf("fun() took %f seconds to execute \n", time_taken); 

    close(source);
    close(dest);



    return 0;
}

