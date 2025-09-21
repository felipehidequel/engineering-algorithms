#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

struct Node
{
    int key;
    int id;

    Node(int k, int i) : key(k), id(i) {}
};

class Heap
{
private:
    std::vector<Node> v;
    size_t size_heap;
    std::unordered_map<int, int> pos; // id -> índice no vetor

    void swapElements(int i, int j)
    {
        std::swap(v[i], v[j]);
        pos[v[i].id] = i;
        pos[v[j].id] = j;
    }

    void maxHeapify(int i)
    {
        int largest = i;
        int left = i << 1;
        int right = (i << 1) + 1;

        if (left <= (int)size_heap && v[left].key > v[largest].key)
            largest = left;
        if (right <= (int)size_heap && v[right].key > v[largest].key)
            largest = right;

        if (largest != i)
        {
            swapElements(i, largest);
            maxHeapify(largest);
        }
    }

public:
    Heap()
    {
        v.emplace_back(Node(-1, -1));
        size_heap = 0;
    }

    bool isEmpty() const { return size_heap == 0; }
    int getSizeHeap() const { return size_heap; }

    void insert(int key, int id)
    {
        if (pos.find(id) != pos.end())
        {
            throw std::invalid_argument("ID já existe no heap");
        }
        v.push_back(Node(key, id));
        ++size_heap;
        pos[id] = size_heap;

        int i = size_heap;
        while (i > 1 && v[i >> 1].key < v[i].key)
        {
            swapElements(i, i >> 1);
            i = i >> 1;
        }
    }

    Node extractMax()
    {
        if (isEmpty())
            throw std::runtime_error("Heap vazio");
        Node maxNode = v[1];

        swapElements(1, size_heap);
        pos.erase(maxNode.id);
        v.pop_back();
        --size_heap;

        if (size_heap > 0)
        {
            maxHeapify(1);
        }

        return maxNode;
    }

    void aumentarChave(int id, int novaChave)
    {
        if (pos.find(id) == pos.end())
            throw std::runtime_error("ID não encontrado");

        int i = pos[id];
        if (novaChave < v[i].key)
            throw std::invalid_argument("Nova chave é menor que a atual");

        v[i].key = novaChave;

        while (i > 1 && v[i >> 1].key < v[i].key)
        {
            swapElements(i, i >> 1);
            i = i >> 1;
        }
    }

    void printHeap() const
    {
        for (int i = 1; i <= (int)size_heap; ++i)
        {
            std::cout << "(id:" << v[i].id << ", key:" << v[i].key << ") ";
        }
        std::cout << "\n";
    }
};
