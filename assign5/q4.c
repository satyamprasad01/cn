#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 10

sem_t sem_a, sem_b;
void *countdown(void *arg) {
    for (int i = MAX_COUNT; i >= 1; i--) {
        sem_wait(&sem_a);
        printf("Thread A (Countdown): %d\n", i);
        sem_post(&sem_b);
    }
    return NULL;
}
void *countup(void *arg) {
    for (int i = 1; i <= MAX_COUNT; i++) {
        sem_wait(&sem_b);
        printf("Thread B (Countup): %d\n", i);
        sem_post(&sem_a);
    }
    return NULL;
}
int main() {
    pthread_t thread_a, thread_b;
    sem_init(&sem_a, 0, 1); 
    sem_init(&sem_b, 0, 0); 
    pthread_create(&thread_a, NULL, countdown, NULL);
    pthread_create(&thread_b, NULL, countup, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    sem_destroy(&sem_a);
    sem_destroy(&sem_b);

    return 0;
}

