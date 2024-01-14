#include <iostream>
#include <fstream>
#include <algorithm>

int maxSumOfTwoElements(int arr[], int size) {
    if (size < 2) {
        return 0;
    }

    std::sort(arr, arr + size, std::greater<int>());

    return arr[0] + arr[1];
}

int main() {
    // Input file
    std::ifstream inputFile("input1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    int size;
    inputFile >> size;

    int* input = new int[size];

    for (int i = 0; i < size; ++i) {
        inputFile >> input[i];
    }

    inputFile.close();

    int result = maxSumOfTwoElements(input, size);

    // Output file
    std::ofstream outputFile("output1.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    outputFile << result << std::endl;

    outputFile.close();

    delete[] input;

    return 0;
}
