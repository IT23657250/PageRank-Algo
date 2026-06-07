=========================================================
SE3082 – Parallel Computing
Assignment 03
Parallel PageRank Algorithm
=========================================================

Student Name : M.A.A.Shafie
Student ID   : IT23657250

=========================================================
PROJECT DESCRIPTION
=========================================================

This project implements the PageRank algorithm using four
different approaches:

1. Serial Implementation
2. OpenMP Parallel Implementation
3. MPI Parallel Implementation
4. CUDA Parallel Implementation

The objective is to compare the performance of different
parallel programming paradigms and evaluate their speedup
relative to the serial implementation.

=========================================================
FOLDER STRUCTURE
=========================================================

CodeBase/
│
├── Serial/
│   └── pagerank_serial.c
│
├── OpenMP/
│   └── pagerank_openmp.c
│
├── MPI/
│   └── pagerank_mpi.c
│
├── CUDA/
│   └── pagerank_cuda.cu
│
└── README.txt

=========================================================
SYSTEM REQUIREMENTS
=========================================================

<<<<<<< HEAD
Operating System:
    - Linux (Ubuntu 22.04 recommended)
    - Windows with WSL2 (optional)

Compiler:
    - GCC 11 or newer

Libraries:
    - OpenMP
    - MPI (MPICH or OpenMPI)
    - NVIDIA CUDA Toolkit 12.x (for CUDA version)

Hardware:
    - Multi-core CPU
    - NVIDIA GPU (CUDA implementation only)

=========================================================
SERIAL IMPLEMENTATION
=========================================================

Source File:
    Serial/pagerank_serial.c

Compilation:

    gcc pagerank_serial.c -o pagerank_serial

Execution:

    ./pagerank_serial

Expected Output:

    - Number of nodes
    - Number of iterations
    - Execution time
    - Sample PageRank values

=========================================================
OPENMP IMPLEMENTATION
=========================================================

Source File:
    OpenMP/pagerank_openmp.c

Compilation:

    gcc -fopenmp pagerank_openmp.c -o pagerank_openmp

Execution:

1 Thread

    export OMP_NUM_THREADS=1
    ./pagerank_openmp

2 Threads

    export OMP_NUM_THREADS=2
    ./pagerank_openmp

4 Threads

    export OMP_NUM_THREADS=4
    ./pagerank_openmp

8 Threads

    export OMP_NUM_THREADS=8
    ./pagerank_openmp

16 Threads

    export OMP_NUM_THREADS=16
    ./pagerank_openmp

Output:

    - Thread count
    - Execution time
    - Sample PageRank values

=========================================================
MPI IMPLEMENTATION
=========================================================

Source File:
    MPI/pagerank_mpi.c

Compilation:

    mpicc pagerank_mpi.c -o pagerank_mpi

Execution:

1 Process

    mpirun -np 1 ./pagerank_mpi

2 Processes

    mpirun -np 2 ./pagerank_mpi

4 Processes

    mpirun -np 4 ./pagerank_mpi

8 Processes

    mpirun -np 8 ./pagerank_mpi

16 Processes

    mpirun -np 16 ./pagerank_mpi

Output:

    - Number of MPI processes
    - Execution time
    - Sample PageRank values

=========================================================
CUDA IMPLEMENTATION
=========================================================

Source File:
    CUDA/pagerank_cuda.cu

Compilation:

    nvcc pagerank_cuda.cu -o pagerank_cuda

Execution:

    ./pagerank_cuda

Testing Different CUDA Configurations:

Modify the following line inside the source code:

    int threadsPerBlock = 256;

Test with:

    32
    64
    128
    256
    512

Recompile after each change:

    nvcc pagerank_cuda.cu -o pagerank_cuda

Run:

    ./pagerank_cuda

Output:

    - Threads per block
    - Execution time
    - Sample PageRank values

=========================================================
PERFORMANCE EVALUATION
=========================================================

The following metrics were collected:

OpenMP:
    - Threads vs Execution Time
    - Threads vs Speedup

MPI:
    - Processes vs Execution Time
    - Processes vs Speedup

CUDA:
    - Threads per Block vs Execution Time
    - Threads per Block vs Speedup

Comparative Analysis:
    - Serial vs OpenMP vs MPI vs CUDA
    - Execution Time Comparison
    - Speedup Comparison

Speedup Formula:

    Speedup = Serial Time / Parallel Time

=========================================================
REFERENCES
=========================================================

[1] L. Page, S. Brin, R. Motwani, and T. Winograd,
    "The PageRank Citation Ranking: Bringing Order to
    the Web," Stanford InfoLab, 1999.

[2] B. Chapman, G. Jost, and R. van der Pas,
    Using OpenMP: Portable Shared Memory Parallel
    Programming, MIT Press, 2008.

[3] W. Gropp, E. Lusk, and A. Skjellum,
    Using MPI: Portable Parallel Programming with the
    Message Passing Interface, MIT Press, 2014.

[4] NVIDIA Corporation,
    CUDA C Programming Guide, 2024.

=========================================================
