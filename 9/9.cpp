#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int getPoint(vector<string> v, int line, int off, int max) {
    int now = v[line][off] - '0';
    bool flag = true;

    int comp;
    for(int i = 0; i < 4; i++) {
        int x = off + dx[i], y = line + dy[i];
        if(x < 0 || y < 0 || x >= max || y >= v.size()) continue;

        comp = v[y][x] - '0';
        if(now >= comp) {
            flag = false;
            break;
        }
    }

    return ((now + 1) * flag);
}

void part1() {
    ifstream file("9_input.txt");
    vector<string> v;
    string temp;
    int ans = 0;
    
    while(getline(file, temp)) {
        v.push_back(temp);
    }

    file.close();

    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[i].size(); j++) {
            ans += getPoint(v, i, j, v[i].size());
        }
    }
    cout << ans << '\n';
}

int dfs(vector<string> &v, int line, int off, int offMax) {
    int now = v[line][off] - '0';
    v[line][off] = 'V'; // Visited mark
    int ans = 1; // 자기자신

    for(int i = 0; i < 4; i++) {
        int nextLine = line + dy[i];
        int nextOff = off + dx[i];
        if(nextOff < 0 || nextLine < 0 || nextOff >= offMax || nextLine >= v.size()) continue;

        int comp = v[nextLine][nextOff] - '0';
        if(comp == 9) continue;
        if(comp > now && v[nextLine][nextOff] != 'V') {
            ans += dfs(v, nextLine, nextOff, offMax);
        }
    }

    return ans;
}

int getBasinSize(vector<string> v, int line, int off, int max) {
    int now = v[line][off] - '0';
    bool flag = true;

    int comp;
    for(int i = 0; i < 4; i++) {
        int x = off + dx[i], y = line + dy[i];
        if(x < 0 || y < 0 || x >= max || y >= v.size()) continue;

        comp = v[y][x] - '0';
        if(now >= comp) {
            flag = false;
            break;
        }
    }

    if (flag == true) { // low point일때
        vector<string> copy = v;
        return dfs(copy, line, off, max);
    }
    else return 0;
}

void part2() { // dfs
    ifstream file("9_input.txt");
    vector<string> v;
    priority_queue<int> pq;
    string temp;
    int ans = 1;
    
    while(getline(file, temp)) {
        v.push_back(temp);
    }

    file.close();

    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[i].size(); j++) {
            pq.push(getBasinSize(v, i, j, v[i].size()));
        }
    }

    for(int i = 0; i < 3; i++) {
        ans *= pq.top();
        pq.pop();
    }
    cout << ans << '\n';
}

int main() {
    //part1();
    part2();

    return 0;
}