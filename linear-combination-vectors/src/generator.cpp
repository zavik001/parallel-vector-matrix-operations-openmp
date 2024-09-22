#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 1000;

void writeVector(const string &filePath)
{
    ofstream file(filePath);
    for (int i = 0; i < n; ++i)
        file << (i % 1000) / 1000.0 << " ";
    file.close();
}

int main()
{
    writeVector("../data/x.txt");
    writeVector("../data/y.txt");
    return 0;
}
