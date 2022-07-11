/*C program to implement Readers and Writers problem using Semaphores*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<semaphore.h>
#include<pthread.h>
sem_t wrt;
pthread_mutex_t mutex;
int count=1,numreader=0;
void *writer(void *Wno)
{
    sem_wait(&wrt);
    count*=2;
    printf("\nWriter %d modified count to %d",((int *)Wno),count);
    sem_post(&wrt);
}
void *reader(void *Rno)
{
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader==1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);
    printf("\nReader %d read count as %d",*((int *)Rno),count);
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader==0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
}
void main()
{
    pthread_t read[10],write[5];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    for(int i=0;i<10;i++)
        pthread_create(&read[i],NULL,(void *)reader,(void *)&a[i]);
    for(int i=0;i<10;i++)
        pthread_create(&write[i],NULL,(void *)writer,(void *)&a[i]);
    for(int i=0;i<10;i++)
        pthread_join(read[i],NULL);
    for(int i=0;i<10;i++)
        pthread_join(write[i],NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
}