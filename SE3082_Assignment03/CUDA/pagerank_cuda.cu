#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N 1000
#define MAX_ITER 100
#define DAMPING 0.85

// CUDA kernel
__global__ void pagerank_kernel(
    int *adj,
    int *out_degree,
    double *rank,
    double *new_rank
) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N) {

        double sum = 0.0;

        for (int j = 0; j < N; j++) {

            if (adj[j * N + i] == 1) {
                sum += rank[j] / out_degree[j];
            }
        }

        new_rank[i] =
            (1.0 - DAMPING) / N +
            DAMPING * sum;
    }
}

int main() {

    int i, j, iter;

    // Host memory
    int *h_adj;
    int *h_out_degree;

    double *h_rank;
    double *h_new_rank;

    h_adj = (int *)malloc(N * N * sizeof(int));
    h_out_degree = (int *)malloc(N * sizeof(int));

    h_rank = (double *)malloc(N * sizeof(double));
    h_new_rank = (double *)malloc(N * sizeof(double));

    srand(42);

    // Generate random graph
    for (i = 0; i < N; i++) {

        h_out_degree[i] = 0;

        for (j = 0; j < N; j++) {

            h_adj[i * N + j] =
                (rand() % 100 < 5) ? 1 : 0;

            if (h_adj[i * N + j] == 1)
                h_out_degree[i]++;
        }

        if (h_out_degree[i] == 0)
            h_out_degree[i] = 1;
    }

    // Initialize ranks
    for (i = 0; i < N; i++) {
        h_rank[i] = 1.0 / N;
    }

    // Device memory
    int *d_adj;
    int *d_out_degree;

    double *d_rank;
    double *d_new_rank;

    cudaMalloc((void**)&d_adj,
               N * N * sizeof(int));

    cudaMalloc((void**)&d_out_degree,
               N * sizeof(int));

    cudaMalloc((void**)&d_rank,
               N * sizeof(double));

    cudaMalloc((void**)&d_new_rank,
               N * sizeof(double));

    // Copy data to GPU
    cudaMemcpy(d_adj,
               h_adj,
               N * N * sizeof(int),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_out_degree,
               h_out_degree,
               N * sizeof(int),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_rank,
               h_rank,
               N * sizeof(double),
               cudaMemcpyHostToDevice);

    // CUDA timing
    cudaEvent_t start, stop;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    // CUDA configuration
    int threadsPerBlock = 256;
    int blocksPerGrid =
        (N + threadsPerBlock - 1) / threadsPerBlock;

    // PageRank iterations
    for (iter = 0; iter < MAX_ITER; iter++) {

        pagerank_kernel<<<blocksPerGrid,
                          threadsPerBlock>>>(
            d_adj,
            d_out_degree,
            d_rank,
            d_new_rank
        );

        cudaDeviceSynchronize();

        // Swap pointers
        double *temp = d_rank;
        d_rank = d_new_rank;
        d_new_rank = temp;
    }

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds,
                         start,
                         stop);

    // Copy results back
    cudaMemcpy(h_rank,
               d_rank,
               N * sizeof(double),
               cudaMemcpyDeviceToHost);

    printf("\n===== CUDA PAGERANK =====\n");
    printf("Nodes              : %d\n", N);
    printf("Iterations         : %d\n", MAX_ITER);
    printf("Threads Per Block  : %d\n",
           threadsPerBlock);

    printf("Execution Time     : %f ms\n",
           milliseconds);

    printf("\nSample PageRank Values:\n");

    for (i = 0; i < 10; i++) {
        printf("Node %d : %.6f\n",
               i,
               h_rank[i]);
    }

    // Free GPU memory
    cudaFree(d_adj);
    cudaFree(d_out_degree);
    cudaFree(d_rank);
    cudaFree(d_new_rank);

    // Free host memory
    free(h_adj);
    free(h_out_degree);
    free(h_rank);
    free(h_new_rank);

    return 0;
}