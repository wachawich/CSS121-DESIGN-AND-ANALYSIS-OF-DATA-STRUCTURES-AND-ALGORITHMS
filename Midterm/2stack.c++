#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> inbox;   // Stack for enqueue operation
    stack<int> outbox;  // Stack for dequeue operation
public:
    void enqueue(int x) {
        inbox.push(x);
    }
    int dequeue() {
        if (outbox.empty()) {
            while (!inbox.empty()) {
                outbox.push(inbox.top());
                inbox.pop();
            }
        }
        if (outbox.empty()) {
            cout << "Queue is empty." << endl;
            return -1; // Or throw an exception
        }
        int frontElement = outbox.top();
        outbox.pop();
        return frontElement;
    }
};
int main() {
    MyQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    q.enqueue(4);
    q.enqueue(5);
    while (true) {
        int result = q.dequeue();
        if (result == -1) break;
        cout << result << endl;
    }

    return 0;
}
