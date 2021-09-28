#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>



#define MaxItems 10 
#define BufferSize 10 
#define MAXNUM 100 



sem_t full;
sem_t empty;


int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;



void *producer()
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%MAXNUM; 
        //meiwnoyme to shmaforo gia na eleksoyme an einai gematos o buffer
	sem_wait(&empty);
	//kleidwnoyme ton dyadiko shmaforo wste na yparxei apokleistikh prospbash ths synarthshs sthn shared memory
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer : Insert Item %d at %d\n", buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
//ksekleidwnoyme ton dyadiko shmaforo wste opoia synarthsh thelei na mporei na mpei sthn shared memory 
        //ayksanoyme to shmaforo gia na dei3oyme oti exei proste8ei stoixeio kai na mporei na proxwrisei o consumer
	sem_post(&full);
    }
}


void *consumer()
{   
    for(int i = 0; i < MaxItems; i++) {
        //elegxoyme an einai adeios o buffer
	sem_wait(&full);
//kleidwnoyme ton dyadiko shmaforo wste na yparxei apokleistikh prospbash ths synarthshs sthn shared memory
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer : Remove Item %d from %d\n",item, out);
        out = (out+1)%BufferSize;
        //ksekleidwnoyme ton dyadiko shmaforo wste opoia synarthsh thelei na mporei na mpei sthn shared memory 
	pthread_mutex_unlock(&mutex);
        //ayksanoyme ton shmaforo gia na deiksoyme ston producer oti mporei na balei kai allo antikeimeno ston buffer
	sem_post(&empty);
    }
}

int main()
{   
//arxikopoihseis shmaforwn kai nhmawn
    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);


    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }
//katastrefoyme toys shmaforoys
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
	

    return 0;
    
}