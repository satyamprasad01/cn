#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void copy_file_content(const char *file1, const char *file2) {
    FILE *src = fopen(file1, "r");
    FILE *dest = fopen(file2, "w");

    if (!src || !dest) {
        perror("Error opening files");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), src)) {
        fputs(buffer, dest);
    }

    fclose(src);
    fclose(dest);
}

void display_file_content(const char *file) {
    FILE *fp = fopen(file, "r");

    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }

    fclose(fp);
}

void display_sorted_reverse(const char *file) {
    FILE *fp = fopen(file, "r");

    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    char *lines[100];
    int count = 0;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        lines[count] = strdup(buffer);
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(lines[i], lines[j]) < 0) {
                char *temp = lines[i];
                lines[i] = lines[j];
                lines[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
}

int main() {
    pid_t pid1, pid2, pid3;

    // Create first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid1 == 0) {
        printf("First child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        copy_file_content("file1.txt", "file2.txt");
        exit(0);
    }

    sleep(1);

    // Create second child process
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid2 == 0) {
        printf("Second child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Content of file2:\n");
        display_file_content("file2.txt");
        exit(0);
    }

    sleep(1);

    // Create third child process
    pid3 = fork();
    if (pid3 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid3 == 0) {
        printf("Third child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Sorted content of file2 in reverse order:\n");
        display_sorted_reverse("file2.txt");
        exit(0);
    }

    sleep(1);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent process: PID = %d. All child processes have completed.\n", getpid());

    return 0;
}

