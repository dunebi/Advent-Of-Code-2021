#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

void part1() {
    FILE* pFile = fopen("8_input.txt", "r");
    char c;
    bool isOutput = false;
    int cnt = 0, ans = 0;

    while(true) {
        c = fgetc(pFile);
        if (c == EOF) break;

        if(c == '|') {
            isOutput = true;
            cnt = 0;
        } else if (c == '\n')  {
            if(cnt == 2 || cnt == 4 || cnt == 3 || cnt == 7) ans += isOutput;
            isOutput = false;
            cnt = 0;
        } else if (c == ' ') {
            if(cnt == 2 || cnt == 4 || cnt == 3 || cnt == 7) ans += isOutput;
            cnt = 0;
        } else cnt++;
    }
    fclose(pFile);
    cout << ans << '\n';
}

void sepSize5(vector<string> v, string* number) {
    string now;
    for(int i = 0; i < v.size(); i++) {
        now = v[i];

        if(now.find(number[1][0]) != string::npos && now.find(number[1][1]) != string::npos) {
            number[3] = now;
            v.erase(v.begin() + i);
            break;
        }
    }

    // 2,3,5(길이 5) 분류 2: 남은 2,5를 4와 비교해서 분류
    now = v[0];
    int cnt = 0;
    for(int i = 0; i < number[4].size(); i++) {
        if(now.find(number[4][i]) != string::npos) cnt++;
    }
    if(cnt == 3) {
        number[5] = now;
        number[2] = v[1];
    } else {
        number[2] = now;
        number[5] = v[1];
    }
}

void sepSize6(vector<string> v, string* number) {
    string now;
    for(int i = 0; i < v.size(); i++) {
        now = v[i];

        // 1의 문자열 2개가 모두 있으면 0 또는 9
        // 둘중 하나만 있으면 6
        if(now.find(number[1][0]) != string::npos && now.find(number[1][1]) != string::npos) continue;
        else {
            number[6] = now;
            v.erase(v.begin() + i);
            break;
        }
    }

    // 남은 2개를 4하고 비교해서 4개 겹치면 9, 3개 겹치면 0
    now = v[0];
    int cnt = 0;
    for(int i = 0; i < number[4].size(); i++) {
        if(now.find(number[4][i]) != string::npos) cnt++;
    }

    if(cnt == 3) {
        number[0] = now;
        number[9] = v[1];
    } else { // cnt = 4
        number[9] = now;
        number[0] = v[1];
    }
}

map<string, int> getMap(vector<string> v[]) { // 문자열 알파벳순 정렬
    string number[10];
    number[1] = v[2][0];
    number[4] = v[4][0];
    number[7] = v[3][0];
    number[8] = v[7][0];

    // get: 1,4,7,8
    // unknown: 0,2,3,5,6,9
    sepSize5(v[5], number);

    // get: 1,2,3,5,7,8
    // unknown: 0,6,9
    sepSize6(v[6], number);

    map<string, int> m;
    for(int i = 0; i < 10; i++){
        sort(number[i].begin(), number[i].end());
        m[number[i]] = i;
    }
    return m;
}

void part2() {
    FILE* pFile = fopen("8_input.txt", "r");
    vector<string> v[10];
    string temp;
    char c;
    bool isOutput = false;
    int ans = 0;

    while(true) { 
        c = fgetc(pFile);
        if (c == EOF) break;

        if (c == '|') isOutput = true;

        if(isOutput) { // 숫자로 분류
            int num = 0;
            map<string, int> numbers = getMap(v);

            temp.clear();
            while(true) {
                c = fgetc(pFile);
                if(c == EOF || c == '\n') {
                    isOutput = false;
                    sort(temp.begin(), temp.end());
                    num = num * 10 + numbers[temp];
                    for(int i = 0; i < 10; i++) v[i].clear();
                    temp.clear();
                    break;
                }

                if(!isalpha(c) && temp.size() > 0) {
                    sort(temp.begin(), temp.end());
                    num = num * 10 + numbers[temp];
                    temp.clear();
                    continue;
                } else if (c == ' ') continue;
                temp.push_back(c);
            }
            ans += num;
            continue;
        }

        // 문자열 분류
        if(!isalpha(c) && temp.size() > 0) { 
            v[temp.size()].push_back(temp);
            temp.clear();
            continue;
        } else if(c == ' ') continue;
        temp.push_back(c);
    }

    cout << ans << '\n';
}
int main() {
    //part1();
    part2();

    return 0;
}