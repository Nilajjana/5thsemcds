#include <stdio.h>

// Structure to represent an edge
struct Edge {
    int u, v, w;
};

// Function to find the parent of a node (with path compression)
int findParent(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = findParent(parent, parent[i]);
    return parent[i];
}

// Function to perform union of two sets
void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Function to sort edges by weight (simple bubble sort)
void sortEdges(struct Edge edges[], int m) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Main function implementing Kruskal's algorithm
int main() {
    int n, m;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &m);

    struct Edge edges[m];

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    sortEdges(edges, m);

    int parent[n + 1];
    int rank[n + 1];
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalWeight = 0;
    printf("\nEdge\tCost\n");

    for (int i = 0, e = 0; i < m && e < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        int setU = findParent(parent, u);
        int setV = findParent(parent, v);

        if (setU != setV) {
            printf("%d--%d\t%d\n", u, v, w);
            totalWeight += w;
            unionSets(parent, rank, setU, setV);
            e++;
        }
    }

    printf("\nTotal Weight of the Spanning Tree: %d\n", totalWeight);
    return 0;
}
