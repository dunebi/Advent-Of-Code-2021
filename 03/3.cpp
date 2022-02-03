#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> v;

int solveOxygen(vector<int> index, int loc, int len) {
    if(loc == len) return 0;
    int ans, bit;
    if(index.size() == 1) { // 하나만 남겨졌을때
        ans = 0;
        for(int i = loc; i < len; i++) {
            bit = v[index[0]][i] - '0';
            ans += (bit << (len - i - 1));
        }
        return ans;
    }

    vector<int> idx[2];

    for(int i = 0; i < index.size(); i++) {
        bit = v[index[i]][loc] - '0';
        if(bit == 0) idx[0].push_back(index[i]);
        else idx[1].push_back(index[i]);
    }

    if(idx[0].size() > idx[1].size()) {
        ans = solveOxygen(idx[0], loc + 1, len);
        ans += (0 << (len - loc - 1));
        return ans;
    }
    else {
        ans = solveOxygen(idx[1], loc + 1, len);
        ans += (1 << (len - loc - 1));
        return ans;
    }
}

int solveCo2(vector<int> index, int loc, int len) {
    if(loc == len) return 0;
    
    int ans, bit;
    if(index.size() == 1) { // 하나만 남겨졌을때
        ans = 0;
        for(int i = loc; i < len; i++) {
            bit = v[index[0]][i] - '0';
            ans += (bit << (len - i - 1));
        }
        return ans;
    }

    vector<int> idx[2];

    for(int i = 0; i < index.size(); i++) {
        bit = v[index[i]][loc] - '0';
        if(bit == 0) idx[0].push_back(index[i]);
        else idx[1].push_back(index[i]);
    }

    if(idx[0].size() <= idx[1].size()) {
        ans = solveCo2(idx[0], loc + 1, len);
        ans += (0 << (len - loc - 1));
        return ans;
    }
    else {
        ans = solveCo2(idx[1], loc + 1, len);
        ans += (1 << (len - loc - 1));
        return ans;
    }
}

int main() {
    ifstream readFile;
    string temp;
    vector<int> idx;
    int len, i;

    readFile.open("3_input.txt");
    if(readFile.is_open()) {
        i = 0;
        while(!readFile.eof()) {
            getline(readFile, temp);
            v.push_back(temp);
            idx.push_back(i);
            i++;
        }
        len = v[0].size();
    }

    int ox = solveOxygen(idx, 0, len);
    int co2 = solveCo2(idx, 0, len);

    cout << ox << ' ' << co2 << '\n';
    cout << ox * co2 << '\n';
       
    return 0;
}