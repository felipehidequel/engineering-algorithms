#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

struct BenchmarkResult {
  double insert_sorted_array;
  double insert_linked_list;
  double insert_avl;
  double search_sorted_array;
  double search_linked_list;
  double search_avl;
};

//=========================================================================
// ESTRUTURA 1: Array Ordenado
//=========================================================================
class SortedArray {
private:
  std::vector<int> arr;

  int lower_bound_manual(int value) {
    int left = 0;
    int right = arr.size();
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] < value)
        left = mid + 1;
      else
        right = mid;
    }
    return left;
  }

public:
  void insert(int value) {
    int pos = lower_bound_manual(value);
    arr.insert(arr.begin() + pos, value);
  }

  bool search(int key) {
    int pos = lower_bound_manual(key);
    return (pos < arr.size() && arr[pos] == key);
  }

  void print() const {
    for (int val : arr) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
};

//=========================================================================
// ESTRUTURA 2: Lista Encadeada Não Ordenada
//=========================================================================
class UnorderedLinkedList {
private:
  struct Node {
    int key;
    Node *next;
    Node(int k, Node *n = nullptr) : key(k), next(n) {}
  };
  Node *head;

public:
  UnorderedLinkedList() : head(nullptr) {}

  ~UnorderedLinkedList() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void insert(int new_key) { head = new Node(new_key, head); }

  bool search(int key) {
    Node *atual = head;
    while (atual != nullptr) {
      if (atual->key == key) {
        return true;
      }
      atual = atual->next;
    }
    return false;
  }

  void print() const {
    Node *atual = head;
    while (atual != nullptr) {
      std::cout << atual->key << " ";
      atual = atual->next;
    }
    std::cout << std::endl;
  }
};

//=========================================================================
// ESTRUTURA 3: Árvore de Busca Binária Balanceada (AVL)
//=========================================================================
class AVLTree {
private:
  struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
  };
  Node *root;

  int height(Node *N) {
    if (N == nullptr)
      return 0;
    return N->height;
  }
  int max(int a, int b) { return (a > b) ? a : b; }
  Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
  }
  Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
  }
  Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T1 = y->left;
    y->left = x;
    x->right = T1;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
  }
  int getBalance(Node *N) {
    if (N == nullptr)
      return 0;
    return height(N->left) - height(N->right);
  }
  Node *insert(Node *node, int key) {
    if (node == nullptr)
      return newNode(key);
    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
    else
      return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
      return rightRotate(node);
    if (balance < -1 && key > node->right->key)
      return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
    return node;
  }
  bool search(Node *node, int key) {
    if (node == nullptr)
      return false;
    if (key == node->key)
      return true;
    if (key < node->key)
      return search(node->left, key);
    return search(node->right, key);
  }
  void deleteTree(Node *node) {
    if (node != nullptr) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }
  void printInOrder(Node *node) const {
    if (node != nullptr) {
      printInOrder(node->left);
      std::cout << node->key << " ";
      printInOrder(node->right);
    }
  }

public:
  AVLTree() : root(nullptr) {}
  ~AVLTree() { deleteTree(root); }
  void insert(int key) { root = insert(root, key); }
  bool search(int key) { return search(root, key); }
  void print() const {
    printInOrder(root);
    std::cout << std::endl;
  }
};

BenchmarkResult run_benchmark(int n, std::mt19937 &gen) {
  std::uniform_int_distribution<int> distrib(1, n * 10);

  std::vector<int> data;
  data.reserve(n);
  for (int i = 0; i < n; ++i)
    data.push_back(distrib(gen));

  BenchmarkResult result{};

  // ---- INSERÇÃO ----
  {
    SortedArray sorted_arr;
    auto start = std::chrono::high_resolution_clock::now();
    for (int val : data)
      sorted_arr.insert(val);
    result.insert_sorted_array =
        std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - start)
            .count();

    UnorderedLinkedList linked_list;
    start = std::chrono::high_resolution_clock::now();
    for (int val : data)
      linked_list.insert(val);
    result.insert_linked_list =
        std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - start)
            .count();

    AVLTree avl_tree;
    start = std::chrono::high_resolution_clock::now();
    for (int val : data)
      avl_tree.insert(val);
    result.insert_avl = std::chrono::duration<double>(
                            std::chrono::high_resolution_clock::now() - start)
                            .count();
  }

  // ---- BUSCA ----
  {
    shuffle(data.begin(), data.end(), gen);

    SortedArray sorted_arr;
    for (int val : data)
      sorted_arr.insert(val);

    UnorderedLinkedList linked_list;
    for (int val : data)
      linked_list.insert(val);

    AVLTree avl_tree;
    for (int val : data)
      avl_tree.insert(val);

    auto start = std::chrono::high_resolution_clock::now();
    for (int val : data)
      sorted_arr.search(val);
    result.search_sorted_array =
        std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - start)
            .count();

    start = std::chrono::high_resolution_clock::now();
    for (int val : data)
      linked_list.search(val);
    result.search_linked_list =
        std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - start)
            .count();

    start = std::chrono::high_resolution_clock::now();
    for (int val : data)
      avl_tree.search(val);
    result.search_avl = std::chrono::duration<double>(
                            std::chrono::high_resolution_clock::now() - start)
                            .count();
  }

  return result;
}

void print_results(int n, const BenchmarkResult &r) {
  std::cout << "---------------------------------------------------------\n";
  std::cout << ">> TESTE PARA N = " << n << " ELEMENTOS\n";
  std::cout << "---------------------------------------------------------\n";

  std::cout << "[TEMPOS DE INSERCAO (s)]\n";
  std::cout << "Array Ordenado:    " << r.insert_sorted_array << "\n";
  std::cout << "Lista Desordenada: " << r.insert_linked_list << "\n";
  std::cout << "Arvore AVL:        " << r.insert_avl << "\n\n";

  std::cout << "[TEMPOS DE BUSCA (s)]\n";
  std::cout << "Array Ordenado:    " << r.search_sorted_array << "\n";
  std::cout << "Lista Desordenada: " << r.search_linked_list << "\n";
  std::cout << "Arvore AVL:        " << r.search_avl << "\n\n";
}

int main() {
  std::vector<int> n_values = {1000, 5000, 10000, 25000, 50000};
  std::random_device rd;
  std::mt19937 gen(rd());

  std::cout << std::fixed << std::setprecision(6);
  
  for (int n : n_values) {
    BenchmarkResult result = run_benchmark(n, gen);
    print_results(n, result);
  }

  return 0;
}