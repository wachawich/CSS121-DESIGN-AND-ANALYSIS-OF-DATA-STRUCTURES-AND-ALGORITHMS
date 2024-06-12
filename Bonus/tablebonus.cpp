#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

template <typename T>
class node {
public:
    T data;
    string name;  // เพิ่ม member variable สำหรับเก็บชื่อ
    node* next;
    node* prev;

    node(T val, const string& n) : data(val), name(n) {
        next = NULL;
        prev = NULL;
    }
};

template <typename T>
void deleteLinkedList(node<T>* &head) {
    while (head != NULL) {
        node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void deleteFromIndex11Onward(node<T>* &head) {
    int currentIndex = 0;

    node<T>* temp = head;
    node<T>* prev = NULL;

    // หาโหนดที่ 10
    while (temp != NULL && currentIndex < 10) {
        prev = temp;
        temp = temp->next;
        currentIndex++;
    }
    // ลบโหนดที่เกิน 10 อันดับหลังจากอันดับที่ 10
    if (temp != NULL) {
        // prev ชี้ไปที่อันดับที่ 10
        prev->next = NULL;
        deleteLinkedList(temp);
    }
    display(head);
}


template <typename T>
void insert(node<T>* &head, T val, const string& name) {
    
    node<T>* newNode = new node<T>(val, name);

    node<T>* temp = head;
    node<T>* prev = NULL;

    // Find the correct position to insert the new node
    while (temp != NULL && val < temp->data) {
        prev = temp;
        temp = temp->next;
    }

    // Insert the new node at the correct position
    newNode->next = temp;
    newNode->prev = prev;
    if (temp != NULL) {
        temp->prev = newNode;
    }
    if (prev != NULL) {
        prev->next = newNode;
    } else {
        // If prev is NULL, it means the new node is the new head
        head = newNode;
    }
}

template <typename T>
void display(node<T>* head) {
    int i = 1;
    node<T>* temp = head;
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << setw(6) << left << "No." << setw(10) << right << "NAME" << setw(15) << right << "SCORE" << endl;
    cout << "---------------------------------" << endl;
    while (temp != NULL) {
        cout << setw(6) << left << i << setw(20) << left << temp->name << setw(5) << right << temp->data << endl;
        cout << "---------------------------------" << endl;
        temp = temp->next;
        i++;
    }
    cout << endl;
}

int main() {
    int score;
    string name, i;
    node<int>* head = NULL;

    insert(head, 1, "xenosz");
    insert(head, 95, "Nathinan");
    insert(head, 10, "Janthima");
    insert(head, 80, "OHM");
    insert(head, 25, "KHAWFANG");
    insert(head, 6, "Napadech");
    insert(head, 16, "Kanyawee");
    insert(head, 26, "WACHIRAWIT");
    insert(head, 36, "Thiraaphat");
    insert(head, 78, "Nathapon");
    display(head);

    cout << "Input '*' for stop input. " << endl;
    while(true){
        cout << "Input name : ";
        cin >> name;

        if (name == "*") break;

        cout << "Input score of " << name << " : ";
        cin >> score;

        insert(head, score, name);
        
        deleteFromIndex11Onward(head);
        cout << "Add data typing '@' stop program typing '*' : ";
        cin >> i;
        if(i == "*") break;
    }

    return 0;
}
