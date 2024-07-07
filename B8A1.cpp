#include <iostream>
#include <cassert>
#include <algorithm> // for std::max


class B8A1
{
    /**********************************************************/
    /**** Longaufgabe 8.1: ****/
    int value;
    B8A1* left;
    B8A1* right;
    int height = 0;
    B8A1(int v) : value(v), height(0), left(nullptr), right(nullptr) {}
    /**********************************************************/

public:
    // Constructor to build tree from array
    B8A1(int *array, int size): left(nullptr), right(nullptr), height(1)
    {
        /**********************************************************/
        /**** Longaufgabe 8.1: ****/
        assert(size > 0);
        value = array[0];
        for (int i = 1; i < size; ++i)
            add(array[i]);
        /**********************************************************/
    }

    // Add value to the tree
    void add(int v)
    {
        /**********************************************************/
        /**** Longaufgabe 8.1: ****/
        // Wenn der einzufügende Wert kleiner als der Wert des aktuellen Knotens ist...
        if (v < value) {
            // ...und wenn der linke Kindknoten des aktuellen Knotens nicht existiert...
            if (left == nullptr) left = new B8A1(v);
            // ...wird die Methode rekursiv auf den linken Kindknoten angewendet.
            else left->add(v);
        } else {
            // Wenn der einzufügende Wert größer oder gleich dem Wert des aktuellen Knotens ist...
            if (right == nullptr) right = new B8A1(v);
            // ...wird die Methode rekursiv auf den rechten Kindknoten angewendet.
            else right->add(v);
        }
        // Aktualisiert die Höhe des Baums
        height = 1 + std::max(left ? left->height : 0, right ? right->height : 0);
        /**********************************************************/
    }

    // In-Order Traversal: left child -> root -> right child
    void inOrder() const
    {
        /**********************************************************/
        /**** Longaufgabe 8.1: ****/
        if (left != nullptr) left->inOrder();
        std::cout << value << " ";
        if (right != nullptr) right->inOrder();
        /**********************************************************/
    }

    // Pre-Order Traversal: root -> left child -> right child
    void preOrder() const
    {
        /**********************************************************/
        /**** Longaufgabe 8.1: ****/
        std::cout << value << " ";
        if (left != nullptr) left->preOrder();
        if (right != nullptr) right->preOrder();
        /**********************************************************/
    }

    // Post-Order Traversal: left child -> right child -> root
    void postOrder() const
    {
        /**********************************************************/
        /**** Longaufgabe 8.1: ****/
        if (left != nullptr) left->postOrder();
        if (right != nullptr) right->postOrder();
        std::cout << value << " ";
        /**********************************************************/
    }

    // Returns the height of the tree
    int getHeight() const
    {
        /**********************************************************/
        /**** Longaufgabe 8.1: ****/
        /**********************************************************/
        return height;
    }
};

int main()
{
    int n;
    std::cin >> n;
    assert(n > 0 && "Error: length of the Input Array < 1");

    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    std::cout << "Input Array: ";
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    B8A1 bst(arr, n);
    delete[] arr; // free the array after it is no longer needed

    std::cout << "Hoehe des Baums: " << bst.getHeight() << std::endl;

    std::cout << "In-Order Traversierung:" << std::endl;
    bst.inOrder();
    std::cout << std::endl;

    std::cout << "Pre-Order Traversierung:" << std::endl;
    bst.preOrder();
    std::cout << std::endl;

    std::cout << "Post-Order Traversierung:" << std::endl;
    bst.postOrder();
    std::cout << std::endl;

    return 0;
}
