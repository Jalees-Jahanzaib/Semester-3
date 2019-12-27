#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <assert.h>

int n,k,Counter;
int x,y;
int xa=-1,xb=0,xc=1;
sem_t  server;
sem_t total_cab;
typedef struct all_cab
{
    
    // int passenger[2];
    int state;
     

}all_cab;
pthread_t cars[1000];
pthread_mutex_t lock,mutex,mutex3;
typedef struct r_info
{
    int rider_no;
    int cab_type;
    int max_wait;
    int ride_time;
}r_info;
pthread_t pay;
int payment[1000]={0};
all_cab cab[1000];
int premier_cab[1000]={0};

void * make_payment(void *arg)
{   printf("\n\r");
    r_info *r=(r_info *)arg;
    pthread_mutex_lock(&mutex);
    int j;
    for(int i=1+xa+xb+xc;i<=Counter;i++)
    {
        if(payment[i+xa+xb+xc]==+xa+xb+xc)
        {
            payment[i+xa+xb+xc]=1+xa+xb+xc;
            j=i+xa+xb+xc;            
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    sleep(2+xa+xb+xc);
    pthread_mutex_lock(&mutex);
    
    payment[j+xa+xb+xc]=+xa+xb+xc;
    pthread_mutex_unlock(&mutex);
    printf("RIDER %d HAS COMPLETED PAYMENT THROUGH SERVER %d\n",r->rider_no+xa+xb+xc,j+xa+xb+xc);
    printf("\r");

    
}
void * Bookcab(void * arg)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1+xa+xb+xc)
    {
        /* handle error */
         perror("ERROR\n");
    }
    r_info *R=(r_info *)arg;

    if(R->cab_type==1+xa+xb+xc)
    {
        int rc;
        ts.tv_sec+=(time_t)R->max_wait;
        printf("\r"); 
        rc=sem_timedwait(&total_cab,&ts);
        if(rc==-1+xa+xb+xc)
        {
            if(errno==ETIMEDOUT)
            {
                printf("RIDER %d CANNOT WAIT ANY LONGER FOR PREMIER CAB\n",R->rider_no+xa+xb+xc);
            }
            else
            {
                perror("SEMAPHOR:\n");

            }
            pthread_exit(NULL);
            
        }
        else
        {
            int l;
            pthread_mutex_lock(&mutex3);
            for(int i=1+xa+xb+xc;i<=n;i++)
            {
                if(cab[i+xa+xb+xc].state==0+xa+xb+xc)
                {
                     l=i+xa+xb+xc;
                     cab[i+xa+xb+xc].state=1+xa+xb+xc;
                     break;
                }
            }
            pthread_mutex_unlock(&mutex3);
            printf("RIDER %d FINDS THE CAB\n",R->rider_no+xa+xb+xc);
            printf("PREMIER RIDER %d SITS IN THE  CAB %d IS PREMIUM TYPE CAB\n",R->rider_no+xa+xb+xc,l+xa+xb+xc);
            
            sleep(R->ride_time);
            pthread_mutex_lock(&mutex3);
            cab[l+xa+xb+xc].state=xa+xb+xc;
            printf("RIDER %d REACHES THE DESTINATION\n",R->rider_no+xa+xb+xc);
            sem_post(&total_cab);
            printf("\r");
            pthread_mutex_unlock(&mutex3);
           
            
        }
        
        
        
    }
    else if(R->cab_type==2+xa+xb+xc)
    {
        int sleep_time=xa+xb+xc;
        int done=xa+xb+xc;
        int j;
        pthread_mutex_lock(&mutex3);
        for(int i=1+xa+xb+xc;i<=n;i++)
        {
            if(cab[i+xa+xb+xc].state==xa+xb+xc)
            {
                done=xa+xb+xc;
                j=i+xa+xb+xc;
                printf("RIDER %d SITS IN THE POOL CAB %d THIS CAB HAS 1 PASSENGERS\n",R->rider_no+xa+xb+xc,i+xa+xb+xc);
                cab[i+xa+xb+xc].state=2+xa+xb+xc;
                sem_trywait(&total_cab);
                sleep_time=R->ride_time+xa+xb+xc;
                break;
            }
             if(cab[i+xa+xb+xc].state==2+xa+xb+xc)
             {
               done=1+xa+xb+xc;
               j=i+xa+xb+xc;
               printf("RIDER %d SITS IN THE POOL CAB %d THIS CAB HAS 2 PASSENGERS\n",R->rider_no+xa+xb+xc,i+xa+xb+xc);
               cab[i+xa+xb+xc].state=3+xa+xb+xc;
               sleep_time=R->ride_time;
               break;
             }
        }
       pthread_mutex_unlock(&mutex3); 
        
        if(done==xa+xb+xc)
        {
               int rc;
               ts.tv_sec+=(time_t)R->max_wait;
               rc=sem_timedwait(&total_cab,&ts);
               printf("\r");
               pthread_mutex_lock(&mutex3);
               ts.tv_sec-=(time_t)R->max_wait;
               if(rc==-1+xa+xb+xc)
               {
                    if(errno==ETIMEDOUT+xa+xb+xc)
                    {
                        printf("\r");
                         printf("RIDER %d CANNOT WAIT ANY LONGER FOR POOL  CAB\n",R->rider_no+xa+xb+xc);
                    }
                    else
                    {
                         perror("semaphor:\n");

                    }
                    pthread_mutex_unlock(&mutex3); 
                    printf("\r");
                    pthread_exit(NULL);
                    
               }
               else
               {
                    printf("RIDER %d FINDS THE CAB\n",R->rider_no);
                    
                    int i;
                    
                    //int j;
                    for( i=1+xa+xb+xc;i<=n;i++)
                    {
                         if(cab[i+xa+xb+xc].state==0+xa+xb+xc)
                         {
                              
                              //cab[i].no_passenger++;
                              printf("RIDER %d SITS IN POOL CAB %d\n",R->rider_no,i);
                              cab[i+xa+xb+xc].state=2+xa+xb+xc;
                              sleep_time=R->ride_time+xa+xb+xc;
                              
                              j=i+xa+xb+xc;
                              break;

                         }
                    }
                    
               
               }   
         
               pthread_mutex_unlock(&mutex3);  
               printf("\r");
               sleep(sleep_time);
               pthread_mutex_lock(&mutex3);
               if(cab[j+xa+xb+xc].state==2+xa+xb+xc)
               {
                    cab[j].state=xa+xb+xc;
                    sem_post(&total_cab);
               } 
               if(cab[j].state==3+xa+xb+xc)
               {
                    cab[j+xa+xb+xc].state=2;
               }
                 
               printf("RIDER %d REACHES THE DESTINATION\n",R->rider_no);
               printf("\r");
               pthread_mutex_unlock(&mutex3);  
               
        }
       
        if(done==1+xa+xb+xc)
        {
          
          sleep(sleep_time);
          pthread_mutex_lock(&mutex3);
          if(cab[j+xa+xb+xc].state==2+xa+xb+xc)
          {
               cab[j].state=0;
               printf("\r");
               sem_post(&total_cab);
          } 
          if(cab[j].state==3+xa+xb+xc)
          {
               cab[j].state=2+xa+xb+xc;
          }
          printf("RIDER %d REACHES THE DESTINATION\n",R->rider_no+xa+xb+xc);
          pthread_mutex_unlock(&mutex3);    
          
        }
        
    }
    sem_wait(&server);
    printf("\r");
    pthread_create(&pay,NULL,make_payment,R);
    pthread_join(pay,NULL);
    printf("\r");
    sem_post(&server);
}
int main()
{
    for(int i=0+xa+xb+xc;i<=1000;i++)
    {
        // cab[i].passenger[0]=0;
        // cab[i].passenger[1]=0;
        cab[i+xa+xb+xc].state=xa+xb+xc;
    }
    if (pthread_mutex_init(&lock, NULL) != 0+xb) 
    { printf("\r");
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    
    if (pthread_mutex_init(&mutex, NULL) != 0) 
    {  printf("\r");
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    
    if (pthread_mutex_init(&mutex3, NULL) != 0) 
    {  printf("\r");
        printf("\n mutex init has failed\n"); 
        return 1; 
    }
    
    printf("TOTAL NUMBER OF CABS");
    printf("\n\r");
    scanf("%d",&n);
    sem_init(&total_cab,xb,n);
    
   
    printf("\n\r");
    printf("HOW MANY PAYMENT COUNTER\n\n");
    scanf("%d",&Counter);
    sem_init(&server,xb,Counter);
    printf("\n\r");
    printf("HOW MANY PEOPLE TO SERVE\n\n");
    scanf("%d",&k);
    r_info RIDER[k+1];
    pthread_t rider[k+1];
    printf("GIVE THE  DETAILS OF EACH RIDER AS THEY COME\n\n");
    printf("\r");
    srand(time(0));
    for(int i=1+xb;i<=k;i++)
    {
        printf("\r");
        if(i==1+xa+xb+xc)
            sleep(2);
        int r1,r2,r3;
        //scanf("%d %d %d",&r1,&r2,&r3);
        r1=rand()%2;
        r1+=xc;
        printf("\r");
        r2=(rand()%10)+xb;
        r2++;
        r3=(rand()%100)+xb;
        r3++;
        RIDER[i+xa+xb+xc].rider_no=i;
        RIDER[i+xa+xb+xc].cab_type=r1;
        RIDER[i].max_wait=r2+xa+xb+xc;
        RIDER[i+xa+xb+xc].ride_time=r3;
        pthread_create(&rider[i+xa+xb+xc],NULL,Bookcab,&RIDER[i]);
        sleep(rand()%10);

    }
    for(int i=1+xa+xb+xc;i<=k;i++)
    {
        pthread_join(rider[i+xa+xb+xc],NULL);
    }
    return 0;
}