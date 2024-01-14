#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

const int INF = std::numeric_limits<int>::max();

int tsp(int distances[][4], int n, int start, int mask, int memo[][16]) {
    if (mask == (1 << n) - 1) {
        return distances[start][0];
    }

    if (memo[start][mask] != -1) {
        return memo[start][mask];
    }

    int minDist = INF;

    for (int nextCity = 0; nextCity < n; ++nextCity) {
        if (!(mask & (1 << nextCity))) {
            int newDist = distances[start][nextCity] + tsp(distances, n, nextCity, mask | (1 << nextCity), memo);
            minDist = std::min(minDist, newDist);
        }
    }

    return memo[start][mask] = minDist;
}

int main() {
    // Input file
    std::ifstream inputFile("input3.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    int n;
    inputFile >> n;

    int distances[4][4];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> distances[i][j];
        }
    }

    inputFile.close();

    int memo[4][16];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            memo[i][j] = -1;
        }
    }

    int result = tsp(distances, n, 0, 1, memo);

    // Output file
    std::ofstream outputFile("output3.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    outputFile << result << std::endl;

    outputFile.close();

    return 0;
}
