#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MaxItems 3
#define BufferSize 3
sem_t empty;
sem_t full;
int in=0,out=0;
int buffer[BufferSize];
pthread_mutex_t mutex;
void *produecr(void *pro)
{
    int item;
    for(int i=0;i<MaxItems;i++)
    {
        item=rand()%100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        printf("\nProducer %d: Inserted item %d at %d",*((int *)pro),buffer[in],in);
        in=(in + 1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{
    for(int i=0;i<MaxItems;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item=buffer[out];
        printf("\nConsumer %d: REmove item %d from %d",*((int *)cno),buffer[out],out);
        out=(out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
void main()
{
    pthread_t pro[3],con[3];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);
    int a[5]={1,2,3,4,5};
    for(int i=0;i<5;i++)
        pthread_create(&pro[i],NULL,(void *)produecr,(void *)&a[i]);
    for(int i=0;i<3;i++)
        pthread_create(&con[i],NULL,(void *)consumer,(void *)&a[i]);
    for(int i=0;i<3;i++)
        pthread_join(pro[i],NULL);
    for(int i=0;i<3;i++)
        pthread_join(con[i],NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}