#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

class TicTacToe {
public:
    char board[3][3];
    int turn;

    TicTacToe() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = '_';
        turn = 0;
    }

    void update(int x, int y, char player) {
        board[x][y] = player;
        turn++;
    }

    int endGameCheck() {
        char p = (turn % 2 == 0) ? 'x' : 'o';

        if ((board[0][0] == p && board[1][1] == p && board[2][2] == p) ||
            (board[0][2] == p && board[1][1] == p && board[2][0] == p) ||
            (board[0][0] == p && board[0][1] == p && board[0][2] == p) ||
            (board[1][0] == p && board[1][1] == p && board[1][2] == p) ||
            (board[2][0] == p && board[2][1] == p && board[2][2] == p) ||
            (board[0][0] == p && board[1][0] == p && board[2][0] == p) ||
            (board[0][1] == p && board[1][1] == p && board[2][1] == p) ||
            (board[0][2] == p && board[1][2] == p && board[2][2] == p))
            return 1;
        else
            return 0;
    }

    int availableMove(int x, int y) {
        if (board[x][y] == '_')
            return 1;
        else
            return 0;
    }

    void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
};

class Node {
public:
    int parent;
    TicTacToe *board;

    Node() {
        parent = -1;
        board = new TicTacToe();
    }
};

class Uptree {
public:
    int maxSize;
    int root;
    int nextLeaf;
    Node *listArray;

    Uptree(int size) {
        maxSize = size + 1;
        root = 0;
        nextLeaf = 1;
        listArray = new Node[maxSize];
        listArray[0].board->printBoard();
        listArray[0].parent = -1;
    }

    void span(int current, queue<int> *Que) {
        int spanTime = 0;

        if (listArray[current].board->endGameCheck() == 0) {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    if (listArray[current].board->availableMove(i, j) == 1) {
                        listArray[nextLeaf].board = new TicTacToe();
                        *listArray[nextLeaf].board = *listArray[current].board;
                        listArray[nextLeaf].parent = current;
                        if (listArray[nextLeaf].board->turn % 2 == 0)
                            listArray[nextLeaf].board->update(i, j, 'x');
                        else
                            listArray[nextLeaf].board->update(i, j, 'o');
                        Que->push(nextLeaf);
                        nextLeaf++;
                        spanTime++;
                    }
                }
        } else {
            cout << "node number " << current << ":";
            if (listArray[current].board->turn % 2 == 0)
                cout << " o wins" << endl;
            else
                cout << " x wins" << endl;
            printUptree(current);
        }
    }

    void printUptree(int pos) {
        if (listArray[pos].parent != -1)
            printUptree(listArray[pos].parent);
        listArray[pos].board->printBoard();
        cout << endl;
    }
};

int main() {
    Uptree Tree(549945);
    queue<int> Que;
    Que.push(0);

    while (!Que.empty()) {
        Tree.span(Que.front(), &Que);
        Que.pop();
    }

    return 0;
}