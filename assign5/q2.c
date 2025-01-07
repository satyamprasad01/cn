#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUMBER 20

sem_t sem_odd, sem_even;
void *print_odd(void *arg) {
    for (int i = 1; i <= MAX_NUMBER; i += 2) {
        sem_wait(&sem_odd); // Wait for odd semaphore
        printf("Thread A (Odd): %d\n", i);
        sem_post(&sem_even); // Signal even semaphore
    }
    return NULL;
}
void *print_even(void *arg) {
    for (int i = 2; i <= MAX_NUMBER; i += 2) {
        sem_wait(&sem_even); // Wait for even semaphore
        printf("Thread B (Even): %d\n", i);
        sem_post(&sem_odd); // Signal odd semaphore
    }
    return NULL;
}
int main() {
    pthread_t thread_odd, thread_even;
    sem_init(&sem_odd, 0, 1); 
    sem_init(&sem_even, 0, 0); 
    pthread_create(&thread_odd, NULL, print_odd, NULL);
    pthread_create(&thread_even, NULL, print_even, NULL);
    pthread_join(thread_odd, NULL);
    pthread_join(thread_even, NULL);
    sem_destroy(&sem_odd);
    sem_destroy(&sem_even);

    return 0;
}

