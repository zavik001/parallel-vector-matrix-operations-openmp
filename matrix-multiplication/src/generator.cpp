#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

constexpr int n = 250;

void writeVector(const string &filePath)
{
    ofstream file(filePath);
    for (int i = 0; i < n * n; ++i)
        file << (i % 1000) / 1000.0 << " ";
    file.close();
}

int main()
{
    writeVector("../data/A.txt");
    writeVector("../data/B.txt");
    return 0;
}
