#include <iostream>
#include <cassert>
#include <algorithm>

class B8A2 {
private:
    static const bool RED = true;
    static const bool BLACK = false;

    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;
        bool color;

        Node(int value) : value(value), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };

    Node* root;
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void insert(Node* root, Node* newNode) {
    /**********************************************************/
    /**** Longaufgabe 8.2: ****/
        // Wenn der Wert des neuen Knotens kleiner als der Wert des aktuellen Knotens ist...
        if (newNode->value < root->value) {
            // ...und wenn der linke Kindknoten des aktuellen Knotens nicht existiert...
            if (root->left == nullptr) {
                // ...wird der neue Knoten als linker Kindknoten eingefügt.
                root->left = newNode;
                newNode->parent = root;
            // ...ansonsten wird die Methode rekursiv auf den linken Kindknoten angewendet.
            } else insert(root->left, newNode);
        } else {
            // Wenn der Wert des neuen Knotens größer oder gleich dem Wert des aktuellen Knotens ist...
            if (root->right == nullptr) {
                // ...und wenn der rechte Kindknoten des aktuellen Knotens nicht existiert...
                // ...wird der neue Knoten als rechter Kindknoten eingefügt.
                root->right = newNode;
                newNode->parent = root;
            // ...ansonsten wird die Methode rekursiv auf den rechten Kindknoten angewendet.
            } else  insert(root->right, newNode);
        }
    /**********************************************************/
    }

    void fixInsert(Node* node) {
    /**********************************************************/
    /**** Longaufgabe 8.2: ****/
        Node* parent = nullptr;
        Node* grandparent = nullptr;
        // Solange der Knoten nicht die Wurzel ist und sowohl der Knoten als auch sein Elternknoten rot sind...
        while ((node != root) && (node->color == RED) && (node->parent->color == RED)) {
            parent = node->parent;
            grandparent = node->parent->parent;
            // Wenn der Elternknoten des Knotens ein linker Kindknoten ist...
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                // Wenn der Onkelknoten existiert und rot ist...
                if (uncle != nullptr && uncle->color == RED) {
                    // ...werden die Farben des Großelternteils, des Elternteils und des Onkels geändert...
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    // ...und der Knoten wird zum Großelternteil.
                    node = grandparent;
                } else {
                    // Wenn der Knoten ein rechter Kindknoten ist...
                    if (node == parent->right) {
                        // ...wird eine Linksrotation auf den Elternknoten angewendet.
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    // Eine Rechtsrotation wird auf den Großelternteil angewendet.
                    rotateRight(grandparent);
                    // Die Farben des Elternteils und des Großelternteils werden getauscht.
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                // Wenn der Elternknoten des Knotens ein rechter Kindknoten ist...
                Node* uncle = grandparent->left;
                // Wenn der Onkelknoten existiert und rot ist...
                if (uncle != nullptr && uncle->color == RED) {
                    // ...werden die Farben des Großelternteils, des Elternteils und des Onkels geändert...
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    // ...und der Knoten wird zum Großelternteil.
                    node = grandparent;
                } else {
                    // Wenn der Knoten ein linker Kindknoten ist...
                    if (node == parent->left) {
                        // ...wird eine Rechtsrotation auf den Elternknoten angewendet.
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    // Eine Linksrotation wird auf den Großelternteil angewendet.
                    rotateLeft(grandparent);
                    // Die Farben des Elternteils und des Großelternteils werden getauscht.
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
    // Die Wurzel des Baums ist immer schwarz.
    root->color = BLACK;
    /**********************************************************/
    }

    void rotateLeft(Node* node) {
    /**********************************************************/
    /**** Longaufgabe 8.2: ****/
        Node* rightChild = node->right;
        // Der rechte Kindknoten des Knotens wird zum linken Kindknoten des rechten Kindknotens.
        node->right = rightChild->left;
        // Wenn der rechte Kindknoten des Knotens existiert, wird sein Elternteil auf den Knoten gesetzt.
        if (node->right != nullptr) node->right->parent = node;
        // Der Elternteil des rechten Kindknotens wird zum Elternteil des Knotens.
        rightChild->parent = node->parent;
        // Wenn der Knoten die Wurzel ist, wird das rechte Kind zur neuen Wurzel.
        if (node->parent == nullptr) root = rightChild;
        // Wenn der Knoten ein linker Kindknoten ist, wird das rechte Kind zum linken Kindknoten des Elternteils.
        else if (node == node->parent->left)  node->parent->left = rightChild;
        // Wenn der Knoten ein rechter Kindknoten ist, wird das rechte Kind zum rechten Kindknoten des Elternteils.
        else node->parent->right = rightChild;

        // Der Knoten wird zum linken Kindknoten des rechten Kindknotens.
        rightChild->left = node;
        node->parent = rightChild;
        std::cout << "Fuehre Links-Rotation durch bei Knoten: " << node->value << std::endl;
    /**********************************************************/
    }

    void rotateRight(Node* node) {
    /**********************************************************/
    /**** Longaufgabe 8.2: ****/
        Node* leftChild = node->left;
        // Der linke Kindknoten des Knotens wird zum rechten Kindknoten des linken Kindknotens.
        node->left = leftChild->right;
        // Wenn der linke Kindknoten des Knotens existiert, wird sein Elternteil auf den Knoten gesetzt.
        if (node->left != nullptr) node->left->parent = node;
        // Der Elternteil des linken Kindknotens wird zum Elternteil des Knotens.
        leftChild->parent = node->parent;
        // Wenn der Knoten die Wurzel ist, wird das linke Kind zur neuen Wurzel.
        if (node->parent == nullptr) root = leftChild;
        // Wenn der Knoten ein linker Kindknoten ist, wird das linke Kind zum linken Kindknoten des Elternteils.
        else if (node == node->parent->left) node->parent->left = leftChild;
        // Wenn der Knoten ein rechter Kindknoten ist, wird das linke Kind zum rechten Kindknoten des Elternteils.
        else node->parent->right = leftChild;

        // Der Knoten wird zum rechten Kindknoten des linken Kindknotens.
        leftChild->right = node;
        node->parent = leftChild;
        std::cout << "Fuehre Rechts-Rotation durch bei Knoten: " << node->value << std::endl;
    /**********************************************************/

    }

	// In-Order Traversierung mit Ausgabe der Farben
    void inOrderTraversal(Node* node) {
		/**********************************************************/
		/**** Longaufgabe 8.2: ****/
        // Wenn der Knoten existiert...
        if (node != nullptr) {
            // ...wird die Methode rekursiv auf den linken Kindknoten angewendet...
            inOrderTraversal(node->left);
            // ...der Wert und die Farbe des Knotens werden ausgegeben...
            std::cout << "(" << node->value << ", " << (node->color == RED ? "rot" : "schwarz") << ") ";
            // ...und die Methode wird rekursiv auf den rechten Kindknoten angewendet.
            inOrderTraversal(node->right);
        }
		/**********************************************************/
    }

    // Gibt die Höhe des Baums zurück
    int height(Node* node) {
		/**********************************************************/
		/**** Longaufgabe 8.2: ****/
        // Wenn der Knoten nicht existiert, ist die Höhe -1.
        if (node == nullptr) return -1;
        // Die Höhe des Baums ist das Maximum der Höhen des linken und rechten Kindknotens plus 1.
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
		/**********************************************************/
        return std::max(leftHeight, rightHeight) + 1;
    }

public:
    B8A2(int arr[], int n) : root(nullptr) {
        for (int i = 0; i < n; i++) {
            this->add(arr[i]);
        }
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
        } else {
            insert(root, newNode);
            fixInsert(newNode);
        }
        std::cout << "Fuege " << value << " in den Rot-Schwarz-Baum ein." << std::endl;
    }

    void traverseInOrder() {
        std::cout << "In-Order Traversierung: ";
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    int treeHeight() {
        return height(root);
    }
    ~B8A2() {
        destroyTree(root);
    }
};

int main() {
    int n;
    std::cin >> n;
    assert(n > 0);
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cout << "Input Array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    B8A2 tree(arr, n);

    std::cout << "Hoehe: " << tree.treeHeight() << std::endl;
    tree.traverseInOrder();

    delete[] arr; // Free allocated memory
    return 0;
}
