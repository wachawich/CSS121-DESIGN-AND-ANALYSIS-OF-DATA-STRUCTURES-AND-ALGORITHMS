#include <iostream>
using namespace std;

struct Node {
    int coefficient;
    int power;
    Node* next;
};

class PolynomialLinkedList {
private:
    Node* head;
public:
    PolynomialLinkedList() {
        head = nullptr;
    }

    void insert(int coefficient, int power) {
        Node* new_node = new Node;
        new_node->coefficient = coefficient;
        new_node->power = power;
        new_node->next = nullptr;

        if (head == nullptr) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            if (current->power == 0) {
                cout << current->coefficient;
            } else {
                cout << current->coefficient << "x";
                if (current->power != 1) {
                    cout << "^" << current->power;
                }
            }
            if (current->next != nullptr) {
                cout << " + ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void multiply(int scalar) {
        Node* current = head;
        while (current != nullptr) {
            current->coefficient *= scalar;
            current = current->next;
        }
    }

    PolynomialLinkedList multiplyPolynomial(PolynomialLinkedList& other) {
        PolynomialLinkedList result;

        Node* current1 = head;
        while (current1 != nullptr) {
            Node* current2 = other.head;
            while (current2 != nullptr) {
                int newCoefficient = current1->coefficient * current2->coefficient;
                int newPower = current1->power + current2->power;

                Node* resultCurrent = result.head;
                bool foundPower = false;
                while (resultCurrent != nullptr) {
                    if (resultCurrent->power == newPower) {
                        resultCurrent->coefficient += newCoefficient;
                        foundPower = true;
                        break;
                    }
                    resultCurrent = resultCurrent->next;
                }

                if (!foundPower) {
                    result.insert(newCoefficient, newPower);
                }

                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return result;
    }

    PolynomialLinkedList addPolynomial(PolynomialLinkedList& other) {
        PolynomialLinkedList result;

        Node* current1 = head;
        Node* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            if (current1->power == current2->power) {
                int sumCoefficients = current1->coefficient + current2->coefficient;
                result.insert(sumCoefficients, current1->power);
                current1 = current1->next;
                current2 = current2->next;
            } else if (current1->power > current2->power) {
                result.insert(current1->coefficient, current1->power);
                current1 = current1->next;
            } else {
                result.insert(current2->coefficient, current2->power);
                current2 = current2->next;
            }
        }

        // ถ้ายังมีตัวหนึ่งใน polynomial ที่ยังไม่ถูกเทียบในลูป while ด้านบน
        // เพิ่ม polynomial ที่เหลือเข้าไปใน result
        while (current1 != nullptr) {
            result.insert(current1->coefficient, current1->power);
            current1 = current1->next;
        }

        while (current2 != nullptr) {
            result.insert(current2->coefficient, current2->power);
            current2 = current2->next;
        }

        return result;
    }
};

int main() {
    PolynomialLinkedList poly1, poly2, result;
    int choice;

    // เพิ่มข้อมูลลงใน polynomial แรก
    poly1.insert(3, 2);
    poly1.insert(2, 1);
    poly1.insert(1, 0);

    // เพิ่มข้อมูลลงใน polynomial ที่สอง
    poly2.insert(5, 1);
    poly2.insert(4, 0);

    cout << "Choose operation:\n1. Multiply\n2. Add\n";
    cin >> choice;

    if (choice == 1) {
        // แสดงผลลัพธ์ polynomial ที่คูณกันแล้ว
        cout << "Polynomial 1: ";
        poly1.display();
        cout << "Polynomial 2: ";
        poly2.display();

        result = poly1.multiplyPolynomial(poly2);
        cout << "Result of multiplication: ";
        result.display();
    } else if (choice == 2) {
        // แสดงผลลัพธ์ polynomial ที่บวกกันแล้ว
        cout << "Polynomial 1: ";
        poly1.display();
        cout << "Polynomial 2: ";
        poly2.display();

        result = poly1.addPolynomial(poly2);
        cout << "Result of addition: ";
        result.display();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}

// สรุป time complexity 
// โดยรวมของโค้ดนี้ใช้เวลาทั้งหมด O(n^2)
// แต่ถ้าหาก เราเลือกที่จะใช้ method add time complexity จะมีแค่ O(n)
// เพราะว่า method multiple นั้น มี time complexity O(n^2) 