#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

class B9A2 {
struct Interval {
    int start, end;
    Interval(int l, int r) : start(l), end(r) {}
};
struct Node {
    Interval interval;
    int maxEnd;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node(Interval i) : interval(i), maxEnd(i.end), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};
private:
    Node* root;

    int height(Node* node) const { return node ? node->height : 0; }

    int balanceFactor(Node* node) const { return node ? height(node->left) - height(node->right) : 0; }

    void updateHeight(Node* node) {
        if (node) node->height = 1 + std::max(height(node->left), height(node->right));
    }

    void updateMaxEnd(Node* node) {
        if (node) node->maxEnd = std::max({node->interval.end, maxEnd(node->left), maxEnd(node->right)});
    }

    int maxEnd(Node* node) const { return node ? node->maxEnd : 0; }

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
        updateMaxEnd(node);
        updateMaxEnd(newRoot);
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
        updateMaxEnd(node);
        updateMaxEnd(newRoot);
    }

    void balance(Node* node) {
        while (node) {
            updateHeight(node);
            updateMaxEnd(node);
            int bf = balanceFactor(node);

            if (bf > 1) {
                if (balanceFactor(node->left) < 0) rotateLeft(node->left);
                rotateRight(node);
            } else if (bf < -1) {
                if (balanceFactor(node->right) > 0) rotateRight(node->right);
                rotateLeft(node);
            }
            node = node->parent;
        }
    }

    void inOrderTraversal(Node* node) const {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << "(" << node->interval.start << ", " << node->interval.end << ") ";
            inOrderTraversal(node->right);
        }
    }

    Node* insert(Node* node, Interval interval) {
        if (!node) return new Node(interval);

        if (interval.start < node->interval.start) {
            node->left = insert(node->left, interval);
            node->left->parent = node;
        } else {
            node->right = insert(node->right, interval);
            node->right->parent = node;
        }
        updateHeight(node);
        updateMaxEnd(node);
        return node;
    }

    Node* search(Node* node, Interval interval) const {
        if (!node || (interval.start <= node->interval.end && interval.end >= node->interval.start))
            return node;

        if (node->left && node->left->maxEnd >= interval.start)
            return search(node->left, interval);

        return search(node->right, interval);
    }

public:
    B9A2() : root(nullptr) {}

    void add(int l, int r) {
        Interval interval(l, r);
        if (!root) root = new Node(interval);
        else {
            Node* insertedNode = insert(root, interval);
            balance(insertedNode);
        }
    }

    void inOrder() const { inOrderTraversal(root); }

    bool search(int l, int r) const {
        Interval interval(l, r);
        Node* result = search(root, interval);
        if (result) {
            cout << "Intersects with: (" << result->interval.start << ", " << result->interval.end << ")" << endl;
            return true;
        } else return false;
    }
};

int main() {
    int n;
    std::cin >> n;
    assert(n > 0 && "Error: length of the Input Array < 1");

    int* arr = new int[2 * n];
    for (int i = 0; i < 2 * n; ++i)
        std::cin >> arr[i];

    std::cout << "Input Array: [";
    for (int i = 0; i < 2 * n; i += 2)
        std::cout << arr[i] << ", " << arr[i + 1] << (i < 2 * n - 2 ? ", " : "]\n");

    B9A2 tree;
    for (int i = 0; i < 2 * n; i += 2)
        tree.add(arr[i], arr[i + 1]);

    delete[] arr;

    std::cout << "In-Order Traversierung:" << std::endl;
    tree.inOrder();
    std::cout << std::endl;

    std::string command;
    while (true) {
        std::cout << "Enter command (s to search, q to quit): ";
        std::cin >> command;

        if (command == "s") {
            int l, r;
            std::cin >> l >> r;

            if (!tree.search(l, r))
                std::cout << "No interval overlaps!" << std::endl;
        } else if (command == "q")
            break;
        else std::cout << "Invalid command. Please try again." << std::endl;
    }

    return 0;
}
