#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int random(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int partition(std::vector<int>& arr, int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(std::vector<int> &arr, int start, int end)
{
    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}

int main()
{
    std::vector<int> banks;
    std::vector<double> res;
    int count, x;
    std::cin >> count;

    for (int j = 0; j < 100; j++)
    {
        for (int i = count; i >= 1; i--) {
            banks.push_back(random(1, count));
        }

        auto start = std::chrono::steady_clock::now();

        quickSort(banks, 0, count - 1);

        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        res.push_back(std::chrono::duration <double, std::micro>(diff).count());
        banks.clear();
    }
    double time = 0.0;
    for (int i = 0; i < res.size(); i++)
    {
        time += res[i];
    }
    std::cout << time / 100.0;
    return 0;
}
