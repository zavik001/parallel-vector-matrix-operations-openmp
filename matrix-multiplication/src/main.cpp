#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 250;

void readMatrix(double *matrix, const string &filePath)
{
    ifstream file(filePath);
    for (int i = 0; i < n * n && file >> matrix[i]; ++i);
    file.close();
}

void matrixMultiply(double *A, double *B, double *C)
{
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++)
                C[i * n + j] += A[i * n + k] * B[k * n + j];
        }
    }
}

double matrixNorm(double *matrix)
{
    double norm = 0;
    for (int i = 0; i < n * n; i++)
        norm += matrix[i] * matrix[i];
    return sqrt(norm);
}

// Последовательная версия
void mainSeq()
{
    double *A = new double[n * n];
    double *B = new double[n * n];
    double *C = new double[n * n];

    readMatrix(A, "../data/A.txt");
    readMatrix(B, "../data/B.txt");

    omp_set_num_threads(1);
    double start = omp_get_wtime();
    matrixMultiply(A, B, C);
    double elapsed_seq = omp_get_wtime() - start;
    double norm_seq = matrixNorm(C);

    cout << "Sequential time (1 thread): " << elapsed_seq << "s\n";
    cout << "Sequential norm: " << norm_seq << "\n";

    delete[] A;
    delete[] B;
    delete[] C;
}

// Параллельная версия с 2 потоками
void mainPar2()
{
    double *A = new double[n * n];
    double *B = new double[n * n];
    double *C = new double[n * n];

    readMatrix(A, "../data/A.txt");
    readMatrix(B, "../data/B.txt");

    omp_set_num_threads(2);
    double start = omp_get_wtime();
    matrixMultiply(A, B, C);
    double elapsed_par_2 = omp_get_wtime() - start;
    double norm_par_2 = matrixNorm(C);

    cout << "Parallel time (2 threads): " << elapsed_par_2 << "s\n";
    cout << "Parallel norm (2 threads): " << norm_par_2 << "\n";

    delete[] A;
    delete[] B;
    delete[] C;
}

// Параллельная версия с максимальным количеством потоков
void mainParMax()
{
    double *A = new double[n * n];
    double *B = new double[n * n];
    double *C = new double[n * n];

    readMatrix(A, "../data/A.txt");
    readMatrix(B, "../data/B.txt");

    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);
    double start = omp_get_wtime();
    matrixMultiply(A, B, C);
    double elapsed_par_max = omp_get_wtime() - start;
    double norm_par_max = matrixNorm(C);

    cout << "Parallel time (" << max_threads << " threads): " << elapsed_par_max << "s\n";
    cout << "Parallel norm (" << max_threads << " threads): " << norm_par_max << "\n";

    delete[] A;
    delete[] B;
    delete[] C;
}

int main()
{
#ifdef SEQ
    mainSeq();
#endif

#ifdef PAR2
    mainPar2();
#endif

#ifdef PARMAX
    mainParMax();
#endif

    return 0;
}
