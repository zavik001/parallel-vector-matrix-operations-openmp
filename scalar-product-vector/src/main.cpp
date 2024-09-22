#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 100;

void readVector(double *a, const string &filePath)
{
    ifstream file(filePath);
    for (int i = 0; i < n && file >> a[i]; ++i);
    file.close();
}

double scalarProduct(double *x, double *y)
{
    double s = 0;
#pragma omp parallel for reduction(+ : s)
    for (int i = 0; i < n; i++)
        s += x[i] * y[i];
    return s;
}

// Последовательная версия
void mainSeq()
{
    double *x = new double[n], *y = new double[n];
    readVector(x, "../data/x.txt");
    readVector(y, "../data/y.txt");

    double start = omp_get_wtime();
    double s_seq = scalarProduct(x, y);
    double elapsed_seq = omp_get_wtime() - start;

    cout << fixed << setprecision(10);
    cout << "Sequential result: " << s_seq << "\nTime (1 thread): " << elapsed_seq << "s\n";

    delete[] x;
    delete[] y;
}

// Параллельная версия с 2 потоками
void mainPar2()
{
    double *x = new double[n], *y = new double[n];
    readVector(x, "../data/x.txt");
    readVector(y, "../data/y.txt");

    omp_set_num_threads(2);
    double start = omp_get_wtime();
    double s_par_2 = scalarProduct(x, y);
    double elapsed_par_2 = omp_get_wtime() - start;

    cout << fixed << setprecision(10);
    cout << "Parallel result (2 threads): " << s_par_2 << "\nTime: " << elapsed_par_2 << "s\n";

    delete[] x;
    delete[] y;
}

// Параллельная версия с максимальным количеством потоков
void mainParMax()
{
    double *x = new double[n], *y = new double[n];
    readVector(x, "../data/x.txt");
    readVector(y, "../data/y.txt");

    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);
    double start = omp_get_wtime();
    double s_par_max = scalarProduct(x, y);
    double elapsed_par_max = omp_get_wtime() - start;

    cout << fixed << setprecision(10);
    cout << "Parallel result (" << max_threads << " threads): " << s_par_max << "\nTime: " << elapsed_par_max << "s\n";
    cout << "Max threads available: " << max_threads << endl;

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
