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

void heapify(std::vector<int> &banks, int count, int i)
{
    int large = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < count && banks[l] > banks[large])   large = l;
    if (r < count && banks[r] > banks[large])   large = r;
    if (large != i) 
    {
        std::swap(banks[i], banks[large]);
        heapify(banks, count, large);
    }
}

void heapSort(std::vector<int> &banks, int count)
{
    for (int i = count / 2 - 1; i >= 0; i--)
    {
        heapify(banks, count, i);
    }
    for (int i = count - 1; i > 0; i--) 
    {
        std::swap(banks[0], banks[i]);
        heapify(banks, i, 0);
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

        heapSort(banks, count);

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
