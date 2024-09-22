#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 10;

void readMatrix(double *matrix, const string &filePath)
{
    ifstream file(filePath);
    for (int i = 0; i < n * n && file >> matrix[i]; ++i)
        ;
    file.close();
}

void readVector(double *vec, const string &filePath)
{
    ifstream file(filePath);
    for (int i = 0; i < n && file >> vec[i]; ++i);
    file.close();
}

void matrixVectorMultiply(double *U, double *x, double *b)
{
#pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        b[i] = 0;
        for (int j = 0; j < n; ++j)
            b[i] += U[i * n + j] * x[j];
    }
}

void solveUpperTriangular(double *U, double *b, double *x)
{
    for (int i = n - 1; i >= 0; --i)
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= U[i * n + j] * x[j];
        x[i] /= U[i * n + i];
    }
}

double vectorNorm(double *vec)
{
    double norm = 0;
#pragma omp parallel for reduction(+ : norm)
    for (int i = 0; i < n; i++)
        norm += vec[i] * vec[i];
    return sqrt(norm);
}

void SolverAndMultiplication(double *U, double *x_true, double *b, double *x_result, int num_threads)
{
    omp_set_num_threads(num_threads);

    matrixVectorMultiply(U, x_true, b);

    solveUpperTriangular(U, b, x_result);
}

// Последовательная версия
void mainSeq()
{
    double *U = new double[n * n];
    double *x_true = new double[n];
    double *b = new double[n];
    double *x_seq = new double[n];

    readMatrix(U, "../data/U.txt");
    readVector(x_true, "../data/x_true.txt");

    double start = omp_get_wtime();
    SolverAndMultiplication(U, x_true, b, x_seq, 1);
    double elapsed_seq = omp_get_wtime() - start;
    double norm_seq = vectorNorm(x_seq);

    cout << "Sequential time (1 thread): " << elapsed_seq << "s\n";
    cout << "Sequential norm: " << norm_seq << "\n";

    delete[] U;
    delete[] x_true;
    delete[] b;
    delete[] x_seq;
}

// Параллельная версия с 2 потоками
void mainPar2()
{
    double *U = new double[n * n];
    double *x_true = new double[n];
    double *b = new double[n];
    double *x_par2 = new double[n];

    readMatrix(U, "../data/U.txt");
    readVector(x_true, "../data/x_true.txt");

    double start = omp_get_wtime();
    SolverAndMultiplication(U, x_true, b, x_par2, 2);
    double elapsed_par_2 = omp_get_wtime() - start;
    double norm_par_2 = vectorNorm(x_par2);

    cout << "Parallel time (2 threads): " << elapsed_par_2 << "s\n";
    cout << "Parallel norm (2 threads): " << norm_par_2 << "\n";

    delete[] U;
    delete[] x_true;
    delete[] b;
    delete[] x_par2;
}

// Параллельная версия с максимальным количеством потоков
void mainParMax()
{
    double *U = new double[n * n];
    double *x_true = new double[n];
    double *b = new double[n];
    double *x_par_max = new double[n];

    readMatrix(U, "../data/U.txt");
    readVector(x_true, "../data/x_true.txt");

    int max_threads = omp_get_max_threads();
    double start = omp_get_wtime();
    SolverAndMultiplication(U, x_true, b, x_par_max, max_threads);
    double elapsed_par_max = omp_get_wtime() - start;
    double norm_par_max = vectorNorm(x_par_max);

    cout << "Parallel time (" << max_threads << " threads): " << elapsed_par_max << "s\n";
    cout << "Parallel norm (" << max_threads << " threads): " << norm_par_max << "\n";

    delete[] U;
    delete[] x_true;
    delete[] b;
    delete[] x_par_max;
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
