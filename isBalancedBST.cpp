#include <iostream>
using namespace std;

struct Node {
    int value;
    struct Node * left;
    struct Node * right;

    Node(int val) {
        value = val;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node * node) {
    if (node == nullptr) return 0;

    return max(getHeight(node->left), getHeight(node->right)) + 1;
}

int findMax(Node * node) {
    if (node == NULL) return INT_MIN;

    int root = node->value;
    int left = findMax(node->left);
    int right = findMax(node->right);
    if (left > root)
        root = left;
    if (right > root)
        root = right;
    return root;
}

int findMin(Node * node){
    if (node == nullptr) return INT_MAX;
  
    int root = node->value;
    int left = findMin(node->left);
    int right = findMin(node->right);
  
    if (left < right)
        root = left;
    if (right < root)
        root = right;
    return root;
}

bool isValidBST(Node * node, int min, int max) {
    if (node == NULL) return true;
             
    if (node->value < min || node->value > max) return false;

    return isValidBST(node->left, min, node->value-1) && isValidBST(node->right, node->value+1, max);
}

bool isBalancedBST(Node * root) {
    if (root == nullptr) return true;

    int min = findMin(root);
    int max = findMax(root);

    int heightDiff = abs(getHeight(root->left) - getHeight(root->right));

    if (heightDiff > 1) {
        return false;
    } else {
        return isBalancedBST(root->left) && isBalancedBST(root->right) && isValidBST(root, min, max);
    }

    return true;
}

int main() {
    struct Node * root = new Node(11);
    
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(3);
    root->left->right = new Node(6);
    root->right->left = new Node(12);
    root->right->right = new Node(17);
    root->right->right->right = new Node(22);
    root->right->right->right->right = new Node(45);

    bool isTreeBalanced = isBalancedBST(root);

    if (isTreeBalanced) {
        cout << "Tree is balanced" << endl;
    } else {
        cout << "Tree is NOT balanced" << endl;
    }
}