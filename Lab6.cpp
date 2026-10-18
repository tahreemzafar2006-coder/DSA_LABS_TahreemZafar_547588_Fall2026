#include <iostream>
#include <algorithm>
using namespace std;
//struct for node , 
struct Node {
    int data;       // value stored in the node
    Node* left;     // pointer to left child
    Node* right;    // pointer to right child
    int height;     // height of the subtree root is this node
 //constructor for node creation 
    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};
// Returns the height of a node
int getHeight(Node* node) {
    return (node == nullptr) ? 0 //Null if the tree DNE
    : node->height;
}
// Returns the balance factor of a node
int getBalanceFactor(Node* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}// Udpades a node height from the heights of its children 
 
Node* rotateRight(Node* y) {
    Node* x = y->left;      // x becomes the new root of this subtree
    Node* B = x->right;     // subtree B moves from x to yi
    x->right = y;    // Perform rotation
    y->left  = B;
    // Update heights: y first (it is now lower), then x
    updateHeight(y);
    updateHeight(x);
    return x;  // return value of new root
}
Node* rotateLeft(Node* x) {
    Node* y = x->right;     // y becomes the new root of this subtree
    Node* B = y->left;      // subtree B moves from y to x
    y->left  = x; // Perform rotation
    x->right = B;
    // Update heights: x first (it is now lower), then y
    updateHeight(x);
    updateHeight(y);
 
    return y;               //returns value of new root
}
//Imbalance check
Node* insert(Node* node, int value) {
    // Step 1: Normal BST insertion
    if (node == nullptr)
        return new Node(value);
    if (value < node->data)
        node->left = insert(node->left, value);// recursion 
    else if (value > node->data)
        node->right = insert(node->right, value);
    updateHeight(node); // Step 2: Update this ancestor's height
    int balance = getBalanceFactor(node);  // Step 3: Check whether this node became unbalanced
    // Case LL: left-heavy, and new key went into the left child's left subtree
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        cout << "  Imbalance at node " << node->data << " -> LL case, right rotation\n";
        return rotateRight(node);
    }
    // Case LR: left-heavy, and new key went into the left child's right subtree
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        cout << "  Imbalance at node " << node->data
             << " -> LR case, left rotation on " << node->left->data
             << " then right rotation on " << node->data << "\n";
        node->left = rotateLeft(node->left);   // first rotation converts to LL
        return rotateRight(node);              // second rotation fixes LL
    }
    // Case RR: right-heavy, and new key went into the right child's right subtree
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        cout << "  Imbalance at node " << node->data << " -> RR case, left rotation\n";
        return rotateLeft(node);
    }
    // Case RL: right-heavy, and new key went into the right child's left subtree
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        cout << "  Imbalance at node " << node->data
             << " -> RL case, right rotation on " << node->right->data
             << " then left rotation on " << node->data << "\n";
        node->right = rotateRight(node->right); // first rotation converts to RR
        return rotateLeft(node);                // second rotation fixes RR
    }
    return node;//if node is balanced then return the node 
}
// In-order traversal (Left, Root, Right): prints values in sorted order.
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
// Pre-order traversal , root ->left->right
void displayNodeInfo(Node* root) {
    if (root == nullptr) return;
    cout << " | Node Value: " << root->data
         << " | Height: " << getHeight(root)
         << " | Balance Factor: " << getBalanceFactor(root) << "\n";
    displayNodeInfo(root->left);
    displayNodeInfo(root->right);
}
void destroyTree(Node* root) {// to avoid memory leaks
    if (root == nullptr) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}
int main() {
    Node* root = nullptr;   // root of AVL tree is a null pointer 
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    if (n <= 0) {
        cout << "N must be a positive integer.\n";
        return 1;
    }
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        cout << "\nInserting " << value<<endl;
        root = insert(root, value);   // insert + rebalance if needed
 
        // Task 1: show the updated tree after each insertion
        cout << "  InOrder traversal: ";
        inorder(root);
        cout << "\n";
    }
    // Task 2: display height and balance factor of every node
    cout << "\n Final tree: Height and Balance Factor of each node\n";
    displayNodeInfo(root);
    destroyTree(root); // Release memory
    return 0;
}