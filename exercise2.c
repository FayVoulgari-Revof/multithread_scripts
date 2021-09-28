#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#define  NUM_THREADS  3
#define  SEM_THREADS  6
// shared vars

int  a2, b1, c1, c2, x, y, z ;
sem_t * semaphores;

sem_t  sa2, sc1, sy, sx, sb1 ,sb2, sc1, sz, sc2;


int main(int argc, char *argv[]){

thread_handles = (pthread_t *)malloc(NUM_THREADS   * sizeof(pthread_t));


sem_init(&sa2, 0, 0);
sem_init(&sc2, 0, 0);
sem_init(&sz, 0, 0);
sem_init(&sy, 0, 0);
sem_init(&sx, 0, 0);
sem_init(&c1, 0, 0);
sem_init(&sb1, 0, 0);



pthread_create(&thread_handles[0], NULL, t1, NULL)
pthread_create(&thread_handles[1], NULL, t2, NULL)
pthread_create(&thread_handles[2], NULL, t3, NULL)


pthread_join(thread_handles[0], NULL);
pthread_join(thread_handles[1], NULL);
pthread_join(thread_handles[2], NULL);


free(thread_handles);



}

void* t1(){

int a1 = 10;
a2 = 11;
sem_post(&sa2);
sem_wait(&sc1);
y = a1 + c1;
sem_post(&sy);
sem_wait(&sx);
print("%d",x)


}

void* t2(){

b1 = 20;
sem_post(&sb1);
int b2 = 21;
sem_wait(&sc2);
w = b2 + c2;
sem_wait(&sy);
sem_wait(&sz);
x = z - y + w
sem_post(&sx);


}

void* t3(){

c1 = 30;
sem_post(&sc1);
c2 = 31;
sem_post(&sc2);
sem_wait(&sb1);
sem_wait(&sa2);
z = a2 + b1;
sem_post(&sz);

}