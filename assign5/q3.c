#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 20

sem_t sem_a, sem_b;
void *print_a(void *arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem_a);
        printf("A");
        fflush(stdout); 
        sem_post(&sem_b); 
    }
    return NULL;
}
void *print_b(void *arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem_b); 
        printf("B");
        fflush(stdout);
        sem_post(&sem_a); 
    }
    return NULL;
}
int main() {
    pthread_t thread_a, thread_b;
    sem_init(&sem_a, 0, 1); 
    sem_init(&sem_b, 0, 0); 
    pthread_create(&thread_a, NULL, print_a, NULL);
    pthread_create(&thread_b, NULL, print_b, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    sem_destroy(&sem_a);
    sem_destroy(&sem_b);

    return 0;
}

