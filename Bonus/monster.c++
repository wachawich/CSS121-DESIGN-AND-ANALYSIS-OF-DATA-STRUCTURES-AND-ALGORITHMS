#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

void add_Tree(int map[10][10]);
void print_map(int map[10][10]);

int main() {
    int i, j, x, y, monsterX;
    int map[10][10] = {0};
    int X1, X2, Y1, Y2;

    int dayOfWeek, lastId, TwoLastId;
    string studentId;

    int taxicab, chebyshev;
    float euclidean;

    // input student ID and Your birthday
    cout << "Input your student ID: ";
    cin >> studentId;
    cout << "Input your birthday in the week (1-7): ";
    cin >> dayOfWeek; 
    cout << endl;
    

    // นำรหัสมาดึงค่าตัวท้าย และก่อนท้าย แล้วเปลี่ยนเป็น int
    lastId = studentId[10] - 48;
    TwoLastId = studentId[9] - 48;
    
    //กำหนดตัวแหน่งของฮีโร่มอนเตอร์ จากค่าที่ได้รับมา
    monsterX = 10 - dayOfWeek;
    map[9 - lastId][dayOfWeek] = 2;
    map[9 - TwoLastId][monsterX] = 3;
    
    add_Tree(map); // เพิ่มต้นไม้
    print_map(map); // display MAP
    

    X1 = dayOfWeek;
    X2 = monsterX;

    Y1 = lastId;
    Y2 = TwoLastId;
    
    taxicab = abs(X1 - X2) + abs(Y1 - Y2);
    euclidean = sqrt(pow(X1 - X2, 2) + pow(Y1 - Y2, 2));
    
    if (abs(X1 - X2) > abs(Y1 - Y2)) {
        chebyshev = abs(X1 - X2);
    } else {
        chebyshev = abs(Y1 - Y2);
    }
    
    cout << "Taxicab: " << taxicab << endl;
    cout << "Euclidean: " << euclidean << endl;
    cout << "Chebyshev: " << chebyshev << endl;

    return 0;
}

void add_Tree(int map[10][10]) {
    int x, y;
    //random tree
    srand((unsigned)time(NULL));
    x = rand() % 10;
    y = rand() % 10;
    //เช็คว่าตำแหน่งที่จะใส่ต้นไม้ = 0 หรือไม่ ก็คือไม่ทับกับตำแหน่งฮีโร่และมอนเตอร์
    if (map[x][9 - y] != 0) {
        x = rand() % 10;
        y = rand() % 10;
    } else {
        map[x][9 - y] = 1;
    }
}
void print_map(int map[10][10]) {
    int i, j;
    for (i = 0; i <= 9; i++) {
        for(j = 0; j <= 9; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}
