#include <iostream>

class AVLTree {
private:
    struct Node {
        int key;
        Node *left;
        Node *right;
        int height;
    };

    Node* root;

    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* newNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T1 = y->left;
        y->left = x;
        x->right = T1;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }
    
    Node* insert(Node* node, int key) {
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

        // Caso LL
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Caso RR
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Caso LR
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Caso RL
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    
    bool search(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        if (key < node->key) {
            return search(node->left, key);
        }
        return search(node->right, key);
    }
    
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }


public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        deleteTree(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }
    bool search(int key) {
        return search(root, key);
    }
};