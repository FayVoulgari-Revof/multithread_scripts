
#include  <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>


#define  array_size 20000000
#define  NUM_THREADS  4
double sum2[array_size];
double arr1[array_size];
double result[NUM_THREADS];
int part=0;


void* sum(void * arr);

int main(){

int i;
double final=0.0;
 struct timeval t0,t1;
 gettimeofday(&t0, NULL); 



srand(time(NULL));
for (i=0;i<array_size;i++){
arr1[i]=(double)(rand()%361);
}
pthread_t tid[NUM_THREADS];

 gettimeofday(&t0, NULL); 

for(i=0;i<NUM_THREADS;i++){
pthread_create(&tid[i],NULL,sum,(void*)arr1);
}

for(i=0;i<NUM_THREADS;i++){
pthread_join(tid[i],NULL);
}
gettimeofday(&t1, NULL);

for(i=0;i<NUM_THREADS;i++){
printf("sum calculated by  %d thread is  %f\n",i+1,result[i]);
final+=result[i];
}

printf(" result is %f of   time = %.3f\n",final,
 (t1.tv_sec - t0.tv_sec + (t1.tv_usec-t0.tv_usec)/1.e6));

return 0;
}

void* sum(void * arr){

int  thread_part=++part;
result[thread_part-1]=0.0;
double *temp=(double*)arr;

for(int i=(thread_part-1)*array_size/NUM_THREADS;i<array_size*thread_part/NUM_THREADS;i++){
sum2[i]=pow(sin(arr1[i]),2) + pow(cos(arr1[i]),2);
result[thread_part-1]+=sum2[i];

}

}

