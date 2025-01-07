#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 20

sem_t sem_a, sem_b, sem_c;
void *print_a(void *arg) {
    for (int i = 1; i <= MAX_COUNT; i += 3) {
        sem_wait(&sem_a);
        printf("A%d\n", i);
        sem_post(&sem_b); 
    }
    return NULL;
}
void *print_b(void *arg) {
    for (int i = 2; i <= MAX_COUNT; i += 3) {
        sem_wait(&sem_b); 
        printf("B%d\n", i);
        sem_post(&sem_c); 
    }
    return NULL;
}
void *print_c(void *arg) {
    for (int i = 3; i <= MAX_COUNT; i += 3) {
        sem_wait(&sem_c);
        printf("C%d\n", i);
        sem_post(&sem_a);
    }
    return NULL;
}
int main() {
    pthread_t thread_a, thread_b, thread_c;
    sem_init(&sem_a, 0, 1); 
    sem_init(&sem_b, 0, 0);
    sem_init(&sem_c, 0, 0); 
    pthread_create(&thread_a, NULL, print_a, NULL);
    pthread_create(&thread_b, NULL, print_b, NULL);
    pthread_create(&thread_c, NULL, print_c, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    sem_destroy(&sem_a);
    sem_destroy(&sem_b);
    sem_destroy(&sem_c);

    return 0;
}

