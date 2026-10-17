#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t temp, pressure;
    int status;

    setbuf(stdout, NULL);

    temp = fork();

    if (temp == 0) {
        printf("Temperature sensor: Sampling data...\n");
        printf("Temperature sensor: Sampling completed.\n");
        exit(0);
    }

    pressure = fork();

    if (pressure == 0) {
        printf("Pressure sensor: Sampling data...\n");
        printf("Pressure sensor: Sampling completed.\n");
        exit(0);
    }

    waitpid(temp, &status, 0);
    printf("Temperature child exit status: %d\n",
           WIFEXITED(status) ? WEXITSTATUS(status) : -1);

    waitpid(pressure, &status, 0);
    printf("Pressure child exit status: %d\n",
           WIFEXITED(status) ? WEXITSTATUS(status) : -1);

    printf("Both sensors completed. Safety index can be calculated.\n");
    printf("Parent gateway process exits.\n");

    return 0;
}
