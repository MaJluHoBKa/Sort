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

int N, n;
std::vector<int> arr;

void logic_merge(int left, int middle, int right)
{
    std::vector<int> left_part;
    std::vector<int> right_part;
    int subSeqLeft = middle - left + 1;
    int subSeqRight = right - middle;
    int index_subSeqLeft = 0, index_subSeqRight = 0, index_divisionSeq = 0;



    for (int i = 0; i < subSeqLeft; i++)
    {
        left_part.push_back(arr[left + i]);
    }
    for (int i = 0; i < subSeqRight; i++)
    {
        right_part.push_back(arr[middle + i + 1]);
    }
    index_divisionSeq = left;

    while (index_subSeqLeft < subSeqLeft && index_subSeqRight < subSeqRight) {
        if (left_part[index_subSeqLeft] >= right_part[index_subSeqRight]) {
            arr[index_divisionSeq] = left_part[index_subSeqLeft];
            index_subSeqLeft++;
        }
        else {
            arr[index_divisionSeq] = right_part[index_subSeqRight];
            index_subSeqRight++;
        }
        index_divisionSeq++;
    }
    while (index_subSeqLeft < subSeqLeft) {
        arr[index_divisionSeq] = left_part[index_subSeqLeft];
        index_divisionSeq++;
        index_subSeqLeft++;
    }
    while (index_subSeqRight < subSeqRight) {
        arr[index_divisionSeq] = right_part[index_subSeqRight];
        index_divisionSeq++;
        index_subSeqRight++;
    }
}

void sequence_division(int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int middle = left + (right - left) / 2;
    sequence_division(left, middle);
    sequence_division(middle + 1, right);
    logic_merge(left, middle, right);
}

int main()
{
    std::vector<double> res;
    int count, x;
    std::cin >> count;

    for (int j = 0; j < 100; j++)
    {
        for (int i = count; i >= 1; i--) {
            arr.push_back(random(1, count));
        }

        auto start = std::chrono::steady_clock::now();

        sequence_division(0, count - 1);

        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        res.push_back(std::chrono::duration <double, std::micro>(diff).count());
        arr.clear();
    }
    double time = 0.0;
    for (int i = 0; i < res.size(); i++)
    {
        time += res[i];
    }
    std::cout << time / 100.0;
    return 0;
}
