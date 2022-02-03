#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

using namespace std;

typedef pair<int,int> pii;

int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int loop(int** board) {
    queue<pii> q;
    map<pii, int> m;
    int ans = 0;

    // increase 1
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j]++;
            if(board[i][j] > 9) q.push(make_pair(i, j));
        }
    }

    int cnt = 0;
    while(!q.empty()) { // flash
        cnt++;
        pii now = q.front();
        q.pop();
        if(m[now] > 0) continue;
        m[now]++;

        for(int i = 0; i < 8; i++) {
            int nexti = now.first + dx[i];
            int nextj = now.second + dy[i];
            pii next = make_pair(nexti, nextj);

            if(nexti < 0 || nextj < 0 || nexti >= 10 || nextj >= 10) continue;

            board[nexti][nextj]++; // increase adjecent level
            if(board[nexti][nextj] > 9) {
                q.push(next);
            }
        }
    }

    // flashed to 0
    for(auto it = m.begin(); it != m.end(); it++) {
        board[it->first.first][it->first.second] = 0;
        ans++;
    }
    return ans;
}

void part1() {
    ifstream file("11_input.txt");
    string temp;
    int** board = new int*[10];
    for(int i = 0; i < 10; i++) {
        board[i] = new int[10];
    }
    
    if(!file.is_open()) {
        cout << "err" << '\n';
        exit(1);
    }

    int line = 0;
    while(getline(file, temp)) {
        for(int i = 0; i < temp.size(); i++)
            board[line][i] = temp[i] - '0';
        line++;
    }

    int ans = 0;
    for(int i = 0; i < 100; i++)
        ans += loop(board);
    cout << ans << '\n';
    
    /*
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++)
            cout << board[i][j] << ' ';
        cout << '\n';
    }
    */    
}

void part2() {
    ifstream file("11_input.txt");
    string temp;
    int** board = new int*[10];
    for(int i = 0; i < 10; i++) {
        board[i] = new int[10];
    }
    
    if(!file.is_open()) {
        cout << "err" << '\n';
        exit(1);
    }

    int line = 0;
    while(getline(file, temp)) {
        for(int i = 0; i < temp.size(); i++)
            board[line][i] = temp[i] - '0';
        line++;
    }

    int ans = 1;
    while(loop(board) != 100) {
        ans++;
    }
    cout << ans << '\n';
}

int main() {
    //part1();
    part2();

    return 0;
}