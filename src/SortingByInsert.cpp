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

        for (int i = 1; i < banks.size(); i++) {
            if (banks[i] > banks[i - 1]) {
                int j = i;
                while (banks[j] > banks[j - 1]) {
                    std::swap(banks[j], banks[j - 1]);
                    j--;
                    if (j == 0)
                    {
                       break;
                    }
                }
            }
        }

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
