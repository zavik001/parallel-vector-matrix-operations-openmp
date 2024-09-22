#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 10;

void writeMatrix(const string &filePath)
{
    ofstream file(filePath);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j >= i)
                file << 1 + (i + j) % 10 / 5.0 << " ";
            else
                file << 0 << " ";
        }
    }
}

void writeVector(const string &filePath)
{
    ofstream file(filePath);
    for (int i = 0; i < n; ++i)
        file << (i % 1000) / 1000.0 + 1 << " ";
    file.close();
}

int main()
{
    writeMatrix("../data/U.txt");
    writeVector("../data/x_true.txt");
    return 0;
}
