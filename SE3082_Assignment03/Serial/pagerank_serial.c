#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define MAX_ITER 100
#define DAMPING 0.85

int main() {

    int i, j, iter;

    // Dynamically allocate adjacency matrix
    int **adj = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        adj[i] = (int *)malloc(N * sizeof(int));
    }

    double rank[N];
    double new_rank[N];
    int out_degree[N];

    // Generate random graph
    srand(42);

    for (i = 0; i < N; i++) {
        out_degree[i] = 0;

        for (j = 0; j < N; j++) {

            // 5% chance of connection
            adj[i][j] = (rand() % 100 < 5) ? 1 : 0;

            if (adj[i][j] == 1)
                out_degree[i]++;
        }

        // Avoid division by zero
        if (out_degree[i] == 0)
            out_degree[i] = 1;
    }

    // Initialize ranks
    for (i = 0; i < N; i++) {
        rank[i] = 1.0 / N;
    }

    clock_t start = clock();

    // PageRank iterations
    for (iter = 0; iter < MAX_ITER; iter++) {

        for (i = 0; i < N; i++) {

            new_rank[i] = 0.0;

            for (j = 0; j < N; j++) {

                if (adj[j][i] == 1) {
                    new_rank[i] += rank[j] / out_degree[j];
                }
            }

            new_rank[i] =
                (1.0 - DAMPING) / N +
                DAMPING * new_rank[i];
        }

        // Update ranks
        for (i = 0; i < N; i++) {
            rank[i] = new_rank[i];
        }
    }

    clock_t end = clock();

    double time_taken =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n===== SERIAL PAGERANK =====\n");
    printf("Nodes           : %d\n", N);
    printf("Iterations      : %d\n", MAX_ITER);
    printf("Execution Time  : %f seconds\n", time_taken);

    // Print first 10 ranks
    printf("\nSample PageRank Values:\n");

    for (i = 0; i < 10; i++) {
        printf("Node %d : %.6f\n", i, rank[i]);
    }

    // Free memory
    for (i = 0; i < N; i++) {
        free(adj[i]);
    }

    free(adj);

    return 0;
}