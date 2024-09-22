# Practical Task 2 on Algorithms Design and Analysis Methods NETI 5th Semester

This project contains solutions to tasks involving parallel operations with vectors and matrices using OpenMP directives.

## Tasks:
1. Parallel computation of the scalar product of vectors.
2. Parallel matrix multiplication.
3. Parallel solution of a system of linear equations with an upper triangular matrix.
4. Parallel program for the linear combination of vectors.

For each task, both sequential and parallel versions are implemented.

## Project Structure:
- `src/`: Contains the source code of the programs.
- `data/`: Contains input data files (e.g., matrix and vector data) used for computation.

## Compilation and Execution:
To compile and run different versions (sequential or parallel with varying numbers of threads), use the following flags during compilation:

- **Sequential version:**
    ```bash
    g++ -fopenmp -DSEQ src/main.cpp -o main_seq
    ./main_seq
    ```
- **Parallel version with 2 threads:**
    ```bash
    g++ -fopenmp -DPAR2 src/main.cpp -o main_par2
    ./main_par2
    ```
- **Parallel version with the maximum number of threads:**
    ```bash
    g++ -fopenmp -DPARMAX src/main.cpp -o main_parmax
    ./main_parmax
    ```
