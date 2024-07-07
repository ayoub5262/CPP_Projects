#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

class B9A1 {
struct Node{
    int value;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

private:
    Node* root;

    int height(Node* node) const { return node ? node->height : 0; }

    int balanceFactor(Node* node) const { return node ? height(node->left) - height(node->right) : 0; }

    void updateHeight(Node* node) {
        if (node)  node->height = 1 + std::max(height(node->left), height(node->right));
    }

    void rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        if (newRoot->left) newRoot->left->parent = node;
        newRoot->parent = node->parent;
        if (!node->parent) root = newRoot;
        else if (node == node->parent->left) node->parent->left = newRoot;
        else node->parent->right = newRoot;
        newRoot->left = node;
        node->parent = newRoot;
        updateHeight(node);
        updateHeight(newRoot);
    }

    void rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        if (newRoot->right) newRoot->right->parent = node;
        newRoot->parent = node->parent;
        if (!node->parent) root = newRoot;
        else if (node == node->parent->left) node->parent->left = newRoot;
        else node->parent->right = newRoot;
        newRoot->right = node;
        node->parent = newRoot;
        updateHeight(node);
        updateHeight(newRoot);
    }

    void balance(Node* node) {
        while (node) {
            updateHeight(node);
            int bf = balanceFactor(node);

            if (bf > 1) {
                if (balanceFactor(node->left) < 0) rotateLeft(node->left); 
                cout << "Linker Teilbaum von \""<< node->value << "\" hat Hoehe "<< height(node->left)
                <<". Rechter Teilbaum hat Hoehe "<< height(node->right)<<"."<< endl;
                cout << "Fuehre Rechts-Rotation durch" << endl;
                rotateRight(node);
            } else if (bf < -1) {
                if (balanceFactor(node->right) > 0) rotateRight(node->right);
                cout << "Rechter Teilbaum von \""<< node->value << "\" hat Hoehe "<< height(node->right)
                <<". Linker Teilbaum hat Hoehe "<< height(node->left)<<"."<< endl;
                cout << "Fuehre Links-Rotation durch" <<endl;
                rotateLeft(node);
            }
            node = node->parent;
        }
    }

    void inOrderTraversal(Node* node) const {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << node->value << " ";
            inOrderTraversal(node->right);
        }
    }

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);

        if (value < node->value) {
            node->left = insert(node->left, value);
            node->left->parent = node;
        } else {
            node->right = insert(node->right, value);
            node->right->parent = node;
        }
        updateHeight(node);
        return node;
    }

public:
    B9A1(int* array, int size) : root(nullptr) {
        for (int i = 0; i < size; ++i) 
            add(array[i]);
    }

    bool isEmpty() { return root == nullptr; }

    void add(int value) {
        std::cout << "Fuege " << value << " in AVL-Baum ein." << std::endl;
        if (!root) root = new Node(value);
        else {
            Node* insertedNode = insert(root, value);
            balance(insertedNode);
        }
    }
    void inOrder() const { inOrderTraversal(root); }
    
    int getHeight() const { return height(root); }

    bool isBalanced() const { return std::abs(balanceFactor(root)) <= 1; }
};

int main() {
    int n;
    std::cin >> n;
    assert(n > 0 && "Error: length of the Input Array < 1");

    int* arr = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    std::cout << "Input Array: [";
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << (i < n - 1 ? ", " : "]\n");
    std::cout << std::endl;

    B9A1 bst(arr, n);
    delete[] arr;

    std::cout << "Hoehe: " << bst.getHeight() << std::endl;

    std::cout << "In-Order Traversierung:" << std::endl;
    bst.inOrder();
    std::cout << std::endl;

    return 0;
}
