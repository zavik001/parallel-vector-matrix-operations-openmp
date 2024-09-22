#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 1000;
constexpr double a = 2.5;

void readVector(double *vec, const string &filePath)
{
    ifstream file(filePath);
    for (int i = 0; i < n && file >> vec[i]; ++i);
    file.close();
}

void linearCombination(double *x, double *y, double a)
{
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        y[i] += a * x[i];
}

double vectorNorm(double *vec)
{
    double norm = 0;
#pragma omp parallel for reduction(+ : norm)
    for (int i = 0; i < n; i++)
        norm += vec[i] * vec[i];
    return sqrt(norm);
}

// Последовательная версия
void mainSeq()
{
    double *x = new double[n];
    double *y = new double[n];

    readVector(x, "../data/x.txt");
    readVector(y, "../data/y.txt");

    omp_set_num_threads(1);
    double start = omp_get_wtime();
    linearCombination(x, y, a);
    double elapsed_seq = omp_get_wtime() - start;
    double norm_seq = vectorNorm(y);

    cout << "Sequential time (1 thread): " << elapsed_seq << "s\n";
    cout << "Sequential norm: " << norm_seq << "\n";

    delete[] x;
    delete[] y;
}

// Параллельная версия с 2 потоками
void mainPar2()
{
    double *x = new double[n];
    double *y = new double[n];

    readVector(x, "../data/x.txt");
    readVector(y, "../data/y.txt");

    omp_set_num_threads(2);
    double start = omp_get_wtime();
    linearCombination(x, y, a);
    double elapsed_par_2 = omp_get_wtime() - start;
    double norm_par_2 = vectorNorm(y);

    cout << "Parallel time (2 threads): " << elapsed_par_2 << "s\n";
    cout << "Parallel norm (2 threads): " << norm_par_2 << "\n";

    delete[] x;
    delete[] y;
}

// Параллельная версия с максимальным количеством потоков
void mainParMax()
{
    double *x = new double[n];
    double *y = new double[n];

    readVector(x, "../data/x.txt");
    readVector(y, "../data/y.txt");

    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);
    double start = omp_get_wtime();
    linearCombination(x, y, a);
    double elapsed_par_max = omp_get_wtime() - start;
    double norm_par_max = vectorNorm(y);

    cout << "Parallel time (" << max_threads << " threads): " << elapsed_par_max << "s\n";
    cout << "Parallel norm (" << max_threads << " threads): " << norm_par_max << "\n";

    delete[] x;
    delete[] y;
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
