#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

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

int findMode(Node* root, std::unordered_map<int, int>& freqMap) {
    if (root == nullptr) return 0;

    findMode(root->left, freqMap);
    freqMap[root->data]++;
    findMode(root->right, freqMap);

    return 0;
}
void inorderTraversalPrint(Node* root) {
    if (root != nullptr) {
        inorderTraversalPrint(root->left);
        std::cout << root->data << " ";
        inorderTraversalPrint(root->right);
    }
}


int main() {
    // เริ่มต้นด้วยการสร้างต้นไม้เปล่า
    Node* root = nullptr;

    // สุ่มเลข 100 ตัวเลขในช่วง 1-99 และเพิ่มลงในต้นไม้ BST
    srand(time(nullptr)); // กำหนด seed ของการสุ่มด้วยเวลาปัจจุบัน
    std::cout << "Random Numbers: ";
    for (int i = 0; i < 100; ++i) {
        int randomNumber = rand() % 99 + 1; // สุ่มเลขในช่วง 1-99
        std::cout << randomNumber << " ";
        root = insert(root, randomNumber); // เพิ่มเลขลงในต้นไม้ BST
    }
    std::cout << std::endl;

    // แสดงต้นไม้ BST ที่เรียงลำดับแล้ว
    std::cout << "Binary Search Tree (Inorder Traversal): ";
    inorderTraversalPrint(root);
    std::cout << std::endl;

    // หาฐานนิยมในต้นไม้ BST
    std::unordered_map<int, int> freqMap;
    findMode(root, freqMap);

    // หาค่าที่มีจำนวนการปรากฏมากที่สุด (ฐานนิยม)
    int maxFreq = 0;
    int mode = -1;
    for (const auto& pair : freqMap) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            mode = pair.first;
        }
    }

    // แสดงฐานนิยม
    std::cout << "Mode: ";
    for (const auto& pair : freqMap) {
        if (pair.second == maxFreq) {
            std::cout << pair.first << " ";
        }
    }
    std::cout << "(Frequency: " << maxFreq << ")" << std::endl;

    return 0;
}
