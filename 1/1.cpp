#include <iostream>
#include <fstream>
#include <string>

#define INT_MAX 2147483647

using namespace std;

int main() {
    ifstream readFile;
    int num[3];
    int cnt = 0;

    readFile.open("1_input.txt");
    if(readFile.is_open()) {
        string temp;
        int i = 0, flag = 0, prev = INT_MAX;
        int now, sum;
        while(!readFile.eof()) {
            getline(readFile, temp);
            if (temp.empty()) break;

            now = stoi(temp);
            num[i] = now;
            if (i == 2) flag = 1;
            i = (i + 1) % 3;
            if (flag == 1) {
                sum = num[0] + num[1] + num[2];
                if(sum > prev) cnt++;
                prev = sum;
            }
            
        }
    }
    cout << cnt << '\n';

    return 0;
}