#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int n;

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the path recursively
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("->%d", j + 1);
}

// Dijkstra’s algorithm
void dijkstra(int graph[MAX][MAX], int src) {
    int dist[MAX];      // The output array. dist[i] will hold the shortest distance from src to i
    int visited[MAX];   // visited[i] will be true if vertex i is included in shortest path tree
    int parent[MAX];    // Array to store shortest path tree

    // Initialization
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0; // Distance of source vertex from itself is 0

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break; // No more reachable vertices
        visited[u] = 1;

        // Update dist[v] only if not visited, there is an edge from u to v,
        // and total weight of path from src to v through u is smaller than current value of dist[v]
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the results
    printf("\nSource\tDestination\tCost\tPath");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t", src + 1, i + 1);
        if (dist[i] == INF)
            printf("INF\tNo Path");
        else {
            printf("%d\t", dist[i]);
            if (i == src)
                printf("-");
            else {
                printf("%d", src + 1);
                printPath(parent, i);
            }
        }
    }
    printf("\n");
}

int main() {
    FILE *fp;
    int graph[MAX][MAX];
    int src;

    fp = fopen("inDiAdjMat1.dat", "r");
    if (!fp) {
        printf("Error: Cannot open input file 'inDiAdjMat1.dat'\n");
        return 1;
    }

    // Read adjacency matrix
    int temp[MAX][MAX];
    n = 0;
    while (!feof(fp)) {
        for (int j = 0; j < MAX; j++) {
            if (fscanf(fp, "%d", &temp[n][j]) != 1)
                break;
        }
        if (!feof(fp))
            n++;
    }
    fclose(fp);

    // Copy matrix to graph[n][n]
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = temp[i][j];

    printf("Enter the Number of Vertices: %d\n", n);
    printf("Enter the Source Vertex: ");
    scanf("%d", &src);
    src--; // Convert to 0-based index

    dijkstra(graph, src);

    return 0;
}
