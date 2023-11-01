#include <iostream> 
#include <vector> 
#include <random> 
#include <chrono>

int random(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

class SkipNode {
public:
    int key;
    int value;
    std::vector<SkipNode*> forward;

    SkipNode(int k, int v, int level) : key(k), value(v), forward(level + 1, nullptr) {}
};

class SkipList 
{
public:
    SkipList(int max_level = 16) : max_level(max_level), level(0) 
    {
        header = new SkipNode(-1, -1, max_level);
    }

    ~SkipList() 
    {
        delete header;
    }

    void insert(int key, int value) 
    {
        std::vector<SkipNode*> update(max_level + 1, nullptr);
        SkipNode* current = header;

        for (int i = level; i >= 0; --i) 
        {
            while (current->forward[i] && current->forward[i]->key <= key) 
            {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->key != key) 
        {
            int new_level = random_level();
            if (new_level > level) 
            {
                for (int i = level + 1; i <= new_level; ++i) 
                {
                    update[i] = header;
                }
                level = new_level;
            }

            SkipNode* new_node = new SkipNode(key, value, new_level);

            for (int i = 0; i <= new_level; ++i) 
            {
                new_node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = new_node;
            }
        }
    }

    void display() 
    {
        for (int i = level; i >= 0; --i) 
        {
            SkipNode* current = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (current) {
                std::cout << "(" << current->key << "," << current->value << ") ";
                current = current->forward[i];
            }
            std::cout << std::endl;
        }
    }

private:
    int random_level() {
        int new_level = 0;
        while (new_level < max_level && (rand() % 2) == 0) {
            new_level++;
        }
        return new_level;
    }

    int max_level;
    int level;
    SkipNode* header;
};

int main() {
    std::vector<double> res;
    int count;
    std::cin >> count;
    for (int j = 0; j < 100; j++)
    {
        SkipList skip_list;
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < count; i++) 
        {
            skip_list.insert(random(1, count), 0);
        }
        /*skip_list.display();*/
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        res.push_back(std::chrono::duration <double, std::micro>(diff).count());
    }
    double time = 0.0;
    for (int i = 0; i < res.size(); i++)
    {
        time += res[i];
    }
    std::cout << time / 100.0;
    return 0;
}
