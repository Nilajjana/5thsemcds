#include <stdio.h>
#include <limits.h>

#define MAX 50
#define INF 9999

int main() {
    int n, start;
    int cost[MAX][MAX], visited[MAX] = {0};
    int i, j, u, v, min, total = 0;
    int mst[MAX][MAX];

    FILE *fp = fopen("inUnAdjMat.dat", "r");
    if (fp == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Read adjacency matrix from file
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            mst[i][j] = 0;

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);

    printf("\nContent of the input file:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fp, "%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INF;
            printf("%3d ", (cost[i][j] == INF ? 0 : cost[i][j]));
        }
        printf("\n");
    }
    fclose(fp);

    visited[start - 1] = 1;

    printf("\nOutput:\n");

    // Prim's algorithm
    for (int count = 0; count < n - 1; count++) {
        min = INF;
        u = v = -1;

        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u != -1 && v != -1) {
            visited[v] = 1;
            mst[u][v] = mst[v][u] = min;
            total += min;
        }
    }

    // Display MST adjacency matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", mst[i][j]);
        }
        printf("\n");
    }

    printf("\nTotal Weight of the Spanning Tree: %d\n", total);
    return 0;
}
