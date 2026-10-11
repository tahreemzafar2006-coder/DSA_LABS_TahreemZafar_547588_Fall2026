#include <vector>
#include <iostream>
#include<queue>
using namespace std;
struct Node {
    int data;
    Node* parent;
    vector<Node*> child;
};
//Task 2 
int getDegree(Node* node) {// get degree function 
    if (node == nullptr) {
        return 0;
    }
    return node->child.size(); // The number of children is the degree
}
// task 2 
bool isRoot(Node* node) {
    if (node == nullptr) return false;
    return (node->parent == nullptr); // A root has no parent
}

bool isLeaf(Node* node) {
    if (node == nullptr) return false;
    return (node->child.empty()); // A leaf has no children
}
//Task 1 
Node* createNode(int data) {
    Node* newNode = new Node(); // allocated memory dynamically for the node
    newNode->data = data;
    newNode->parent = nullptr; // initially new node has no parent
    return newNode;
}
void addChild(Node* parentNode, int data) {
    if (parentNode == nullptr) {
        return; 
    }
    Node* newChild = createNode(data);
    newChild->parent = parentNode; // specifies the parent of child
    parentNode->child.push_back(newChild); // Core logic to add new child for vector child node 
}
void displayTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    cout << "Node: " << root->data;
    // Check and label the node type
    if (isRoot(root)) {
        cout << " [ROOT]";
    } else if (isLeaf(root)) {
        cout << " [LEAF]";
    } else {
        cout << " [BRANCH]";
    }
    // Added Degree using vector's size() method
    cout << " | Degree: " << getDegree(root);
    if (root->parent != nullptr) {
        cout << " | Parent: " << root->parent->data;
    } else {
        cout << " | Parent: None";
    }
    cout << " | Children: ";
    if (root->child.empty()) {
        cout << "None";
    } else {
        for (Node* child : root->child) {
            cout << child->data << " ";
        }
    }
    cout << endl;
    for (Node* child : root->child) {
        displayTree(child);
    }
}
//Task 2 
int countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int total = 1; // Count the current node
    // Recursively count nodes in all child subtrees
    for (Node* child : root->child) {
        total += countNodes(child);
    }
    return total;
}
//task 3 
int getTreeHeight(Node* root) {
    if (root == nullptr) {
        return -1; // Empty-tree height = -1
    }
    if (root->child.empty()) {
        return 0; // Leaf height = 0
    }
    int maxHeight = -1;
    for (Node* child : root->child) {// loops through tree
        int childHeight = getTreeHeight(child);
        if (childHeight > maxHeight) {
            maxHeight = childHeight;
        }
    }
    return maxHeight + 1;
}
//task 3 
int getNodeDepth(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    // Base case: Root depth is 0 (since root->parent is nullptr)
    if (node->parent == nullptr) {
        return 0;
    }
    // 1 + depth of parent
    return 1 + getNodeDepth(node->parent);
}
//Task 4 
void breadthFirstTraversal(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->data << " ";
        for (Node* child : current->child) {
            q.push(child);
        }
    }
}
void preOrderTraversal(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    for (Node* child : root->child) {
        preOrderTraversal(child);
    }
}

void postOrderTraversal(Node* root) {
    if (root == nullptr) return;
    for (Node* child : root->child) {
        postOrderTraversal(child);
    }
    cout << root->data << " ";
}
//Task 5 
void deleteSubtree(Node* node) {
    if (node == nullptr) return;
    for (Node* child : node->child) {
        deleteSubtree(child);
    }
    delete node;
}
void deleteNode(Node*& root, Node* target) {// Function to delete a node and its descendants, updating the parent's child list
    if (target == nullptr) return;
    // Case 1: Target is the root (delete entire tree)
    if (target->parent == nullptr) {
        deleteSubtree(root);
        root = nullptr;
        return;
    }
    // Case 2: Target has a parent, remove pointer from parent's vector
    Node* parentNode = target->parent;
    for (auto it = parentNode->child.begin(); it != parentNode->child.end(); ++it) {
        if (*it == target) {
            parentNode->child.erase(it);
            break;
        }
    } // Recursively free all nodes in the target's subtree
    deleteSubtree(target);
}

int main() {
    //task 1
    // Level 0
    Node* root = createNode(1);
    // Level 1
    addChild(root, 2);
    addChild(root, 3);
    addChild(root, 4);
    // Level 2
    addChild(root->child[0], 5);
    addChild(root->child[0], 6);
    addChild(root->child[1], 7);
    addChild(root->child[1], 8);
    addChild(root->child[2], 9);
    addChild(root->child[2], 10);
    cout << "General Tree Node Details\n";
    displayTree(root);
    //task 2 
    int totalNodes = countNodes(root);
        cout << "\nTotal number of nodes in the tree: " << totalNodes << endl;
//task 3 
    cout << "\nTree Height: " << getTreeHeight(root) << endl;
    Node* fixedNode = root->child[1];
    cout << "Selected Node Value: " << fixedNode->data << endl;
    cout << "Depth of Selected Node: " << getNodeDepth(fixedNode) << endl;
    //task 4 
    cout << "\n Traversals\n";
    cout << "Breadth-First Traversal (BFS): ";
    breadthFirstTraversal(root);
    cout << endl;
    cout << "Pre-Order Traversal: ";
    preOrderTraversal(root);
    cout << endl;
    cout << "Post-Order Traversal: ";
    postOrderTraversal(root);
    cout << endl;
    //Task 5
    cout << "TREE BEFORE DELETION\n";
    displayTree(root);
    cout << "Total Nodes before deletion: " << countNodes(root) << endl;// Let's select a specific node to delete (e.g., Node 3, which is root->child[1])
    Node* nodeToDelete = root->child[1]; 
    cout << "\nDeleting Node " << nodeToDelete->data << " and all its descendants...\n";
    deleteNode(root, nodeToDelete);
    cout << "\n TREE AFTER DELETION \n";
    displayTree(root);
    cout << "Total Nodes after deletion: " << countNodes(root) << endl;
    return 0;
}