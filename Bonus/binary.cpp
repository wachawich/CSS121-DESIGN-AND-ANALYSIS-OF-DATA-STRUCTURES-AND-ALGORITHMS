#include <iostream>

using namespace std;

// กำหนดโครงสร้างของโหนดใน Binary Search Tree
struct Node {
    int data;
    Node* left;
    Node* right;
};

// สร้างโหนดใหม่
Node* createNode(int value) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Error: Memory could not be allocated." << endl;
        return NULL;
    }
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// เพิ่มโหนดใหม่เข้าไปใน Binary Search Tree
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

// ค้นหาโหนดใน Binary Search Tree
Node* search(Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (root->data < value) {
        return search(root->right, value);
    }
    return search(root->left, value);
}

// ฟังก์ชันสำหรับการท่องไปใน Binary Search Tree แบบ Pre-order
void preOrderTraversal(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}
void postOrderTraversal(Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->data << " ";
    }
}
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;
    root = insert(root, 10);
    insert(root, 8);
    insert(root, 2);
    insert(root, 4);
    insert(root, 3);
    insert(root, 15);
    insert(root, 26);
    insert(root, 30);
    insert(root, 17);
    insert(root, 6);

    cout << "Pre-order traversal: ";
    preOrderTraversal(root);
    cout << endl;
    cout << "Post-order traversal: ";
    postOrderTraversal(root);
    cout << endl;
    cout << "In-order traversal: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}
