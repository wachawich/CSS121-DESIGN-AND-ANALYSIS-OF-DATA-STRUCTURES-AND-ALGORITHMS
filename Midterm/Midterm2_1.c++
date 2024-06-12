#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        root = createNode(data);
    } else if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

void inorderTraversal(Node* root, vector<int>& values) {
    if (root != nullptr) {
        inorderTraversal(root->left, values);
        values.push_back(root->data);
        inorderTraversal(root->right, values);
    }
}

int findMedian(const vector<int>& values) {
    int n = values.size();
    if (n % 2 == 0) {
        // กรณี n เป็นเลขคู่
        return (values[n / 2 - 1] + values[n / 2]) / 2;
    } else {
        // กรณี n เป็นเลขคี่
        return values[n / 2];
    }
}

int main() {
    Node* root = nullptr;

    srand(time(nullptr));
    cout << "Random Numbers: ";
    for (int i = 0; i < 100; ++i) {
        int randomNumber = rand() % 99 + 1;
        cout << randomNumber << " ";
        root = insert(root, randomNumber); 
    }
    cout << endl;

    cout << "Binary Search Tree (Inorder Traversal): ";
    vector<int> values;
    inorderTraversal(root, values);
    for (int value : values) {
        cout << value << " ";
    }
    cout << endl;

    // หาค่ามัธยฐาน
    int median = findMedian(values);
    cout << "Median: " << median << endl;

    return 0;
}
