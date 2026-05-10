#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000
#define MAX_ITER 100
#define DAMPING 0.85

int main(int argc, char *argv[]) {

    int rank_id, num_procs;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int i, j, iter;

    int rows_per_proc = N / num_procs;
    int start = rank_id * rows_per_proc;
    int end = start + rows_per_proc;

    // Allocate adjacency matrix
    int **adj = (int **)malloc(N * sizeof(int *));

    for (i = 0; i < N; i++) {
        adj[i] = (int *)malloc(N * sizeof(int));
    }

    double rank[N];
    double new_rank[N];
    int out_degree[N];

    srand(42);

    // Generate graph
    for (i = 0; i < N; i++) {

        out_degree[i] = 0;

        for (j = 0; j < N; j++) {

            adj[i][j] = (rand() % 100 < 5) ? 1 : 0;

            if (adj[i][j] == 1)
                out_degree[i]++;
        }

        if (out_degree[i] == 0)
            out_degree[i] = 1;
    }

    // Initialize ranks
    for (i = 0; i < N; i++) {
        rank[i] = 1.0 / N;
    }

    double start_time = MPI_Wtime();

    // PageRank iterations
    for (iter = 0; iter < MAX_ITER; iter++) {

        // Compute partial ranks
        for (i = start; i < end; i++) {

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

        // Gather all updated ranks
        MPI_Allgather(
            &new_rank[start],
            rows_per_proc,
            MPI_DOUBLE,
            rank,
            rows_per_proc,
            MPI_DOUBLE,
            MPI_COMM_WORLD
        );
    }

    double end_time = MPI_Wtime();

    // Only master prints
    if (rank_id == 0) {

        printf("\n===== MPI PAGERANK =====\n");
        printf("Processes Used  : %d\n", num_procs);
        printf("Nodes           : %d\n", N);
        printf("Iterations      : %d\n", MAX_ITER);
        printf("Execution Time  : %f seconds\n",
               end_time - start_time);

        printf("\nSample PageRank Values:\n");

        for (i = 0; i < 10; i++) {
            printf("Node %d : %.6f\n", i, rank[i]);
        }
    }

    // Free memory
    for (i = 0; i < N; i++) {
        free(adj[i]);
    }

    free(adj);

    MPI_Finalize();

    return 0;
}