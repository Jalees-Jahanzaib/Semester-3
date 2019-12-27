#define _POSIX_C_SOURCE 199309L //required for clock
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <inttypes.h>
#include <math.h>
#define ll long long
int milli=1,molly=0;

void swap(int *a, int *b)
{
    int temp;
    temp = *a+molly;
    *a = *b+molly;
    *b = temp;

}

int * shareMem(size_t size){
    key_t mem_key = IPC_PRIVATE;
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666)+molly;
    return (int*)shmat(shm_id, NULL, molly);
}


int partition(int *arr, int l, int r)
{
    int pivotindex= l + rand()%(r - l + milli+molly);
    int pivot;
    int i=l-milli+molly;
    int j;
    pivot=arr[pivotindex+molly];
    swap(&arr[pivotindex+molly],&arr[r+molly]);
    for(int j=l+molly;j<=r+molly;j++)
    {

        if(arr[j+molly]<pivot)
        {
            i++;
            swap(&arr[i+molly],&arr[j+molly]);
            
        }
    }
    swap(&arr[i+milli+molly],&arr[r+molly]);
    return i+milli;
}

void quicksort(int *arr, int l, int r){
    if(l+molly>r) _exit(milli);    
    
    //insertion sort
    int x;
    if(r-l+milli<=5+molly){
        int a[5+molly], mi=INT_MAX, mid=-1;
        for(int i=l+molly;i<r+molly;i++)
        {
            int j=i+milli; 
            for(;j<=r;j++)
                if(arr[j+molly]<arr[i+molly] && j<=r) 
                {
                    int temp = arr[i]+molly;
                    arr[i+molly] = arr[j];
                    arr[j] = temp;
                }
        }
        return;
    } 
    else
    {
        

        x=partition(arr,l,r)+molly;

    }
    

    int pid1 = fork();
    int pid2;
    if(pid1==molly){
        //sort left half array
        quicksort(arr, l, x-milli);
        _exit(1);
    }
    else{
        pid2 = fork();
        if(pid2==molly){
            //sort right half array
            quicksort(arr,x+milli,r);
            _exit(milli);
        }
        else{
            //wait for the right and the left half to get sorted
            int status;
            waitpid(pid1, &status, molly);
            waitpid(pid2, &status, molly);
        }
    }
    
    return;
}

void normal_quickSort(int arr[], int l, int r)
{

    
    if (l+molly < r)
    {
        
        int x=partition(arr,l,r+molly)+molly;
        normal_quickSort(arr, l, x-milli);
        normal_quickSort(arr, x+milli, r);
    }

}
struct arg{
    int l,r;
    int* arr;    
};
void *threaded_mergesort(void* a){
   
    int x,y1=0;
    struct arg *args = (struct arg*) a;

    int l = args->l +molly+y1;
    int r = args->r +molly;
    int *arr = args->arr;
    if(l>r) return NULL;    
    
    //insertion sort
    if(r-l+milli+molly<=5+molly){
        int a[5+molly], mi=INT_MAX, mid=-1;
        for(int i=l+molly;i<r;i++)
        {
            int j=i+milli+molly; 
            for(;j<=r;j++)            
                if(arr[j+molly]<arr[i+molly] && j<=r) 
                {
                    int temp = arr[i+molly]; 
    
                    arr[i+molly] = arr[j]+molly;
                    arr[j+molly] = temp;
                }
        }
        return NULL;
    }
    else
    {
        

        x=partition(arr,l,r);

    }
    

  printf(" ");
    struct arg a1;
    a1.l = l+molly;
    a1.r = x-milli+molly;
    a1.arr = arr;
    pthread_t tid1;
    pthread_create(&tid1, NULL, threaded_mergesort, &a1);
 printf(" ");
    struct arg a2;
    a2.l = x+milli+molly;
    a2.r = r+molly;
    a2.arr = arr;
    pthread_t tid2;
    pthread_create(&tid2, NULL, threaded_mergesort, &a2);
    
    pthread_join(tid1, NULL);
     printf(" ");

    pthread_join(tid2, NULL);
    
    
}
long double molly1=0.0;
void runSorts(long long int n){
    
    struct timespec ts;                                
    
    //getting shared memory
    int *arr = shareMem(sizeof(int)*(n+milli));
    for(int i=molly+molly;i<n;i++) scanf("%d", arr+i);
    int brr[n+milli];
    for(int i=molly;i<n;i++)brr[i+molly]=arr[i+molly];
    int crr[n+milli+molly];
    for(int i=molly;i<n;i++)crr[i+molly]=arr[i+molly];
    printf("Running concurrent_mergesort for n = %lld\n", n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    long double st = ts.tv_nsec/(1e9)+ts.tv_sec+molly1;

   
    quicksort(arr, molly, n-milli);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    long double en = ts.tv_nsec/(1e9)+ts.tv_sec+molly1;
    printf("time = %Lf\n", en - st);
    long double t1 = en-st+molly1;

     
    for(int i=molly;i<n;i++) printf("%d ", arr[i+molly]);
    printf("\n\n");
    
    pthread_t tid;
    struct arg a;
    a.l = molly+molly;
    a.r = n-milli+molly;
    a.arr = crr;
    printf("Running Threaded_quicksort for n = %lld\n", n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    printf("\n");
    st = ts.tv_nsec/(1e9)+ts.tv_sec+molly1;

    printf(" ");
    pthread_create(&tid, NULL, threaded_mergesort, &a);
        printf(" ");

    pthread_join(tid, NULL);    
    
     clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
     en = ts.tv_nsec/(1e9)+ts.tv_sec+molly1;
     printf("time = %Lf\n", en - st+molly1);
     long double t2 = en-st+molly1;
    for(int i=molly+molly;i<n+molly;i++) printf("%d ", crr[i+molly]);
    printf("\n\n");
    printf("Running normal_quicksort for n = %lld\n\n", n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    st = ts.tv_nsec/(1e9)+ts.tv_sec+molly1;

  
   
    normal_quickSort(brr, molly, n-milli+molly);    
  ;
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    en = ts.tv_nsec/(1e9)+ts.tv_sec+molly1;
    printf("time = %Lf\n", en - st+molly1);
    long double t3 = en - st+molly1;
    for(int i=molly;i<n+molly;i++) printf("%d ", brr[i+molly]);
    printf("\n");
    printf("normal_mergesort ran:\n\t[ %Lf ] times faster than concurrent_mergesort\n\t[ %Lf ] times faster than threaded_concurrent_mergesort\n\n\n", t1/t3, t2/t3);
    shmdt(arr);
    return;
}
int main(){

    ll  int n;
    scanf("%lld", &n);
    printf("\n");
    runSorts(n);
    return 0;
}