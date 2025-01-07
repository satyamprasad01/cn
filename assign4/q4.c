#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Function to generate Fibonacci series
void generate_fibonacci(int *fib, int length) {
    if (length > 0) fib[0] = 0;
    if (length > 1) fib[1] = 1;
    for (int i = 2; i < length; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main() {
    int length;
    printf("Enter the length of the Fibonacci series: ");
    scanf("%d", &length);

    if (length <= 0) {
        printf("Invalid length. Exiting.\n");
        return 1;
    }

    int fib[length];
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: Generate Fibonacci series
        printf("Child process: Generating Fibonacci series.\n");
        generate_fibonacci(fib, length);
        // Pass the array to parent through shared memory or IPC in real applications.
        exit(0);
    } else {
        // Parent process: Wait for child to complete
        wait(NULL);
        printf("Parent process: Fibonacci series of length %d:\n", length);

        generate_fibonacci(fib, length); // Simulate shared memory in this simplified example

        for (int i = 0; i < length; i++) {
            printf("%d ", fib[i]);
        }
        printf("\n");

        // Find and display prime Fibonacci numbers
        printf("Parent process: Prime Fibonacci numbers:\n");
        for (int i = 0; i < length; i++) {
            if (is_prime(fib[i])) {
                printf("Position: %d, Value: %d\n", i + 1, fib[i]);
            }
        }
    }

    return 0;
}
