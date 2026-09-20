#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ITERATIONS 30
#define MAX_SLEEP 10

void ChildProcess(void);

int main(void)
{
    pid_t pid;
    int i, status;

    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            ChildProcess();
        }
    }

    for (i = 0; i < 2; i++) {
        pid = wait(&status);
        printf("Child Pid: %d has completed\n", pid);
    }

    return 0;
}

void ChildProcess(void)
{
    int i, iterations;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    /* seed with microseconds + pid so each child gets a unique sequence */
    srandom((unsigned int)(tv.tv_sec ^ tv.tv_usec ^ (getpid() << 16)));
    iterations = (random() % MAX_ITERATIONS) + 1;

    for (i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        fflush(stdout);
        sleep((random() % MAX_SLEEP) + 1);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        fflush(stdout);
    }

    exit(0);
}
