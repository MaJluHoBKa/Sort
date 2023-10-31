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

int binarySearch(std::vector<int> &a, int item, int low, int high)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (item == a[mid])
            return mid + 1;
        else if (item > a[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}

void insertionSort(std::vector<int> &a, int n)
{
    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = a[i];

        loc = binarySearch(a, selected, 0, j);

        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
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

        insertionSort(banks, count);

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
