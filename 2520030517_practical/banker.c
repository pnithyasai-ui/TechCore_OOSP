#include <stdio.h>

int n, m, alloc[10][10], max[10][10];
int avail[10], need[10][10], finish[10], seq[10];
int count = 0;

void safe(int k) {
    int i, j, ok;

    if (k == n) {
        count++;
        printf("Safe sequence %d: ", count);
        for (i = 0; i < n; i++)
            printf("P%d ", seq[i]);
        printf("\n");
        return;
    }

    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            ok = 1;

            for (j = 0; j < m; j++)
                if (need[i][j] > avail[j])
                    ok = 0;

            if (ok) {
                for (j = 0; j < m; j++)
                    avail[j] += alloc[i][j];

                finish[i] = 1;
                seq[k] = i;

                safe(k + 1);

                finish[i] = 0;
                for (j = 0; j < m; j++)
                    avail[j] -= alloc[i][j];
            }
        }
    }
}

int main() {
    int i, j;

    printf("Enter processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter maximum matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    safe(0);

    if (count > 0)
        printf("System is in SAFE state.\n");
    else
        printf("System is in UNSAFE state. No safe sequence exists.\n");

    return 0;
}
