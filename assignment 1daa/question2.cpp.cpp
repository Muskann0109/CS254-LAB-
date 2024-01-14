#include <iostream>
#include <fstream>
#include <algorithm>

int knapsackMaxValue(int weights[], int values[], int n, int maxWeight) {
    int dp[n + 1][maxWeight + 1];

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= maxWeight; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][maxWeight];
}

int main() {
    // Input file
    std::ifstream inputFile("input2.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    int n, maxWeight;
    inputFile >> n >> maxWeight;

    int* weights = new int[n];
    int* values = new int[n];

    for (int i = 0; i < n; ++i) {
        inputFile >> weights[i];
    }

    for (int i = 0; i < n; ++i) {
        inputFile >> values[i];
    }

    inputFile.close();

    int result = knapsackMaxValue(weights, values, n, maxWeight);

    // Output file
    std::ofstream outputFile("output2.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    outputFile << result << std::endl;

    outputFile.close();

    delete[] weights;
    delete[] values;

    return 0;
}
