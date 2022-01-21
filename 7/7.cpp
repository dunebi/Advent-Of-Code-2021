#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

vector<int> v;

int getSum(int num) {
    int sum = 0;
    for(int i = 0; i < v.size(); i++) {
        int n = abs(num - v[i]);
        sum += (n* (n + 1)) / 2;
    }

    return sum;
}

int main() {
    FILE* pFile = fopen("7_input.txt", "r");
    char c = 'c';
    int num = 0, max = -1;

    while(true) {
        if(c == EOF) break;
        c = fgetc(pFile);

        if(isdigit(c)) {
            num = num * 10 + (int)(c - '0');
        }
        else {
            v.push_back(num);
            num = 0;
        }
    }
    fclose(pFile);

    // sort(v.begin(), v.end());
    int exp = accumulate(v.begin(), v.end(), 0) / (v.size());
    int ans = INT32_MAX;
    for(int dx = -10; dx <= 10; dx++) {
        if(exp - dx <= 0) continue;
        ans = min(ans, getSum(exp + dx));
    }

    cout << ans << '\n';


    return 0;
}